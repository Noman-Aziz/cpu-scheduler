#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<fcntl.h>
#include<pthread.h>
#include"Queue.h"
#include"MinHeap.h"
#include"Procs.h"

using namespace std;

Queue<Procs> RR;
Queue<Procs> FCFS;
MinHeap<Procs> SJF;
MinHeap<Procs> SRTF;

int new_ready_fd[2];
int ready_run_fd[2] ;
int run_ready_fd[2] ;
int block_ready_fd[2] ;
int n_r_status_fd[2];
int r_r_status_fd[2];
int r_run_status2_fd[2];

//srtf variables
bool srtf = false;

void * readfromnew(void *arg);
void * readfromblock(void *arg);
void * readfromrun(void *arg);

int main( int argc, char *argv[] )
{
    new_ready_fd[0] = atoi(argv[1]) ;
    new_ready_fd[1] = atoi(argv[2]) ;

    ready_run_fd[0] = atoi(argv[3]) ;
    ready_run_fd[1] = atoi(argv[4]) ;

    run_ready_fd[0] = atoi(argv[5]) ;
    run_ready_fd[1] = atoi(argv[6]) ;

    block_ready_fd[0] = atoi(argv[7]) ;
    block_ready_fd[1] = atoi(argv[8]) ;

    n_r_status_fd[0] = atoi(argv[9]) ;
    n_r_status_fd[1] = atoi(argv[10]) ;

    r_r_status_fd[0] = atoi(argv[11]) ;
    r_r_status_fd[1] = atoi(argv[12]) ;

    r_run_status2_fd[0] = atoi(argv[13]) ;
    r_run_status2_fd[1] = atoi(argv[14]) ;

    //making pipes unblocking
    fcntl(n_r_status_fd[0], F_SETFL, O_NONBLOCK);
    fcntl(r_r_status_fd[0], F_SETFL, O_NONBLOCK) ;

    //fcntl(new_ready_fd[0], F_SETFL, O_NONBLOCK);
    //fcntl(block_ready_fd[0], F_SETFL, O_NONBLOCK) ;
    //fcntl(run_ready_fd[0], F_SETFL, O_NONBLOCK) ;

    cout << "I AM READY PROCESS\n" ;

    Procs temp ;
    int end  ;
    char message[10] = "CONTINUE" ;
    char message2[5] = "STAT" ;
    bool srtf=false;
    int remaining ;
    
    pthread_t thread1, thread2, thread3;

    sleep(1);

    //reading from new state
    pthread_create(&thread1,NULL,readfromnew,NULL);

    //reading from blocked state
    pthread_create(&thread2,NULL,readfromblock,NULL);

    //reading from run state
    pthread_create(&thread3,NULL,readfromrun,NULL) ;

    bool exitstatus = false;

    while (1)
    {
        //reading that whether to exit
        read(n_r_status_fd[0],&exitstatus,sizeof(bool));
        
        if(exitstatus)
            break;

        //reading what whether running process wants me to send a process to it
        read(r_r_status_fd[0],&message2,4);

        if (strcmp(message2,"STAT") == 0)
        {
            if(!FCFS.IsEmpty())
            {
                temp = FCFS.dequeue();
            }

            else if (!RR.IsEmpty())
            {
                temp = RR.dequeue();
            }

            else if (!SJF.IsEmpty())
            {
                temp = SJF.remove();
            }

            else if (!SRTF.IsEmpty())
            {
                temp = SRTF.remove();
                srtf=true;
            }

            else if(FCFS.IsEmpty() and RR.IsEmpty() and SJF.IsEmpty() and SRTF.IsEmpty())
                continue;

            //sending the proc to running proc
            write(ready_run_fd[1],&temp,sizeof(temp));

            //change mode to stop sending to running proc
            message2[0] = 'S' ;
            message2[1] = 'T' ;
            message2[2] = 'O' ;
            message2[3] = 'P' ;
        }

        //sending the shortest remaining time in case of srtf
        if(srtf)
        {
            if(!SRTF.IsEmpty())
                remaining = SRTF.head->Data.burst_time - SRTF.head->Data.given_time ; 
            
            else
                remaining = 0;
            
            write(r_run_status2_fd[1], &remaining, sizeof(remaining));
        }

        sleep(1);
    
        for(Node<Procs> *f = FCFS.head ; f != NULL ; f = f->next )
            f->Data.waiting_time++;
    
        for(Node<Procs> *f = RR.head ; f != NULL ; f = f->next )
            f->Data.waiting_time++;

        for(Node1<Procs> *f = SJF.head ; f != NULL ; f = f->next )
            f->Data.waiting_time++;

        for(Node1<Procs> *f = SRTF.head ; f != NULL ; f = f->next )
            f->Data.waiting_time++;
    }

    sleep(1) ;

    cout << endl << "//////////////////////////////////////////////////////////////////////////////" << endl ;
    cout << "READY PROCESS EXITING" << endl ;
    cout << "//////////////////////////////////////////////////////////////////////////////" << endl << endl ;
    exit(0);
}

void * readfromnew(void *arg)
{
    Procs temp;

    while(1)
    {
        read(new_ready_fd[0],&temp,sizeof(temp));        
        
        if(strcmp(temp.algorithm,"FCFS") == 0)
            FCFS.enqueue(temp);

        else if(strcmp(temp.algorithm,"RR") == 0)
            RR.enqueue(temp);

        else if(strcmp(temp.algorithm,"SJF") == 0)
            SJF.insert(temp);

        else if(strcmp(temp.algorithm,"SRTF") == 0)
            SRTF.insert(temp);

        cout << temp.name << " CAME FROM ADMIT STATE" << endl;
    }

    pthread_exit(NULL);
}

void * readfromblock(void *arg)
{
    Procs temp;
    int end;

    while(1)
    {
        end = read(block_ready_fd[0],&temp,sizeof(temp));        
                
        if(strcmp(temp.algorithm,"FCFS") == 0)
            FCFS.enqueue(temp);

        else if(strcmp(temp.algorithm,"RR") == 0)
            RR.enqueue(temp);

        else if(strcmp(temp.algorithm,"SJF") == 0)
            SJF.insert(temp);

        else if(strcmp(temp.algorithm,"SRTF") == 0)
            SRTF.insert(temp);

        cout << temp.name << " IS BACK FROM BLOCKED STATE" << endl;
    }

    pthread_exit(NULL);
}

void * readfromrun(void *arg)
{
    Procs temp;

    while(1)
    {
        read(run_ready_fd[0],&temp,sizeof(temp));        
                
        if(strcmp(temp.algorithm,"FCFS") == 0)
            FCFS.enqueue(temp);

        else if(strcmp(temp.algorithm,"RR") == 0)
        {
            RR.enqueue(temp);
            cout << temp.name << " IS BACK FROM RUNNING STATE AFTER COMPLETING ITS TIME QUANTUM" << endl;
        }

        else if(strcmp(temp.algorithm,"SJF") == 0)
            SJF.insert(temp);
    
        else if(strcmp(temp.algorithm,"SRTF") == 0)
        {
            SRTF.insert(temp);
            cout << temp.name << " CAME FROM FROM RUNNING STATE CAUSE OF PREAMTION" << endl;
        }
    }

    pthread_exit(NULL);
}
