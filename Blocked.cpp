#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>
#include<time.h>
#include<pthread.h>
#include"Queue.h"
#include"Procs.h"

using namespace std;

Queue<Procs> Input_Blocked;
Queue<Procs> Output_Blocked;
Queue<Procs> Printer_Blocked;

int run_block_fd[2] ;
int block_ready_fd[2] ;
int n_b_status_fd[2];

void* readfromrun(void *arg);

int main( int argc, char *argv[] )
{
    srand(time(0));
    run_block_fd[0] = atoi(argv[1]) ;
    run_block_fd[1] = atoi(argv[2]) ;

    block_ready_fd[0] = atoi(argv[3]) ;
    block_ready_fd[1] = atoi(argv[4]) ;

    n_b_status_fd[0] = atoi(argv[5]) ;
    n_b_status_fd[1] = atoi(argv[6]) ;

    cout << "I AM BLOCKED PROCESS\n";

    sleep(1);

    //making pipe unblocking
    fcntl(n_b_status_fd[0], F_SETFL, O_NONBLOCK) ;

    pthread_t thread1;
    pthread_create(&thread1,NULL,readfromrun,NULL);

    Procs current;

    bool exitstatus = false;

    while(1)
    {
        sleep(1);

        read(n_b_status_fd[0],&exitstatus,sizeof(bool));

        if(exitstatus)
            break;

        //for input blocked queue
        if(!Input_Blocked.IsEmpty())
        {
            //check whether its time is up or it needs more time
            if(Input_Blocked.head->Data.blocked_time == Input_Blocked.head->Data.given_blocked_time)
            {
                //dequeue it and send it to ready queue
                current = Input_Blocked.dequeue();

                write(block_ready_fd[1],&current,sizeof(current));
            }

            else
            {
                //increment its blocked time
                Input_Blocked.head->Data.blocked_time++;
                
                //increment all waiting time
                for(Node<Procs> *f = Input_Blocked.head ; f != NULL ; f = f->next )
                    f->Data.waiting_time++;


            }
        }

        //for output blocked queue
        if(!Output_Blocked.IsEmpty())
        {
            //check whether its time is up or it needs more time
            if(Output_Blocked.head->Data.blocked_time == Output_Blocked.head->Data.given_blocked_time)
            {
                //dequeue it and send it to ready queue
                current = Output_Blocked.dequeue();

                write(block_ready_fd[1],&current,sizeof(current));
            }

            else
            {
                //increment its blocked time
                Output_Blocked.head->Data.blocked_time++;
            
                //increment all waiting time
                for(Node<Procs> *f = Output_Blocked.head ; f != NULL ; f = f->next )
                    f->Data.waiting_time++;
            }
        }

        //for printer blocked queue
        if(!Printer_Blocked.IsEmpty())
        {
            //check whether its time is up or it needs more time
            if(Printer_Blocked.head->Data.blocked_time == Printer_Blocked.head->Data.given_blocked_time)
            {
                //dequeue it and send it to ready queue
                current = Printer_Blocked.dequeue();

                write(block_ready_fd[1],&current,sizeof(current));
            }

            else
            {
                //increment its blocked time
                Printer_Blocked.head->Data.blocked_time++;
            
                //increment all waiting time
                for(Node<Procs> *f = Printer_Blocked.head ; f != NULL ; f = f->next )
                    f->Data.waiting_time++;
            }
        }
    }
    
    cout << endl << "//////////////////////////////////////////////////////////////////////////////" << endl ;
    cout << "BLOCKED PROCESS EXITING" << endl ;
    cout << "//////////////////////////////////////////////////////////////////////////////" << endl << endl ;

    exit(0);
}

void* readfromrun(void *arg)
{
    Procs current;

    while(1)
    {
        read(run_block_fd[0],&current,sizeof(current));

        //determining its block time;
        current.given_blocked_time = ( rand() % (25-15) ) + 15 ; 
        cout << current.name << " IS BLOCKED NOW FOR " << current.given_blocked_time << " TICKS";

        current.blocked_time = 0;

        //determining its block type
        int type = ( rand() % 3 );

        //enquing it in queue
        switch(type)
        {
            case 0: cout << " IN INPUT QUEUE" << endl;
                    Input_Blocked.enqueue(current);
                    break;
            case 1: cout << " IN OUTPUT QUEUE" << endl;
                    Output_Blocked.enqueue(current);
                    break;
            case 2: cout << " IN PRINTER QUEUE" << endl;
                    Printer_Blocked.enqueue(current);
                    break;
            default:cout << " ERROR" << endl;
        }
    }

    pthread_exit(NULL);
}
