#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<sys/types.h>
#include<string.h>
#include<fcntl.h>
#include<pthread.h>
#include"Procs.h"

using namespace std;

//random no generator
#define random (rand() % 2)
//send signal to ready process to send me new process
#define sendmenewproc write(r_r_status_fd[1],"STAT",4)

int ready_run_fd[2] ;
int run_ready_fd[2] ;
int run_block_fd[2] ;
int run_exit_fd[2] ;
int r_r_status_fd[2] ;
int n_run_status_fd[2] ;
int r_run_status2_fd[2] ;

int remaining = 0;
int temp;

void * readremaining(void * arg);

int main( int argc, char *argv[] )
{
    srand(time(0));

    ready_run_fd[0] = atoi(argv[1]) ;    
    ready_run_fd[1] = atoi(argv[2]) ;

    run_ready_fd[0] = atoi(argv[3]) ;
    run_ready_fd[1] = atoi(argv[4]) ;

    run_block_fd[0] = atoi(argv[5]) ;
    run_block_fd[1] = atoi(argv[6]) ;

    run_exit_fd[0] = atoi(argv[7]) ;
    run_exit_fd[1] = atoi(argv[8]) ;

    r_r_status_fd[0] = atoi(argv[9]) ;
    r_r_status_fd[1] = atoi(argv[10]) ;

    n_run_status_fd[0] = atoi(argv[11]) ;
    n_run_status_fd[1] = atoi(argv[12]) ;

    r_run_status2_fd[0] = atoi(argv[13]) ;
    r_run_status2_fd[1] = atoi(argv[14]) ;

    //making pipe ubblocking
    fcntl(ready_run_fd[0], F_SETFL, O_NONBLOCK);
    fcntl(n_run_status_fd[0], F_SETFL, O_NONBLOCK);
    //fcntl(r_run_status2_fd[0], F_SETFL, O_NONBLOCK);

    Procs current;
    bool new_proc = false;
    int end;
    int random_no;
    int ticks = 0;

    bool NONPRIM=false;
    bool RR=false;
    bool SRTF=false;
    int quantum;

    cout << "I AM RUNNING PROCESS\n";
    
    pthread_t thread1;

    sleep(1);

    bool exitstatus = false;
    bool swap = false;
    bool once = false;

    while(1)
    {
        ticks++;

        read(n_run_status_fd[0],&exitstatus,sizeof(bool));

        if(exitstatus)
            break;

        end = read(ready_run_fd[0],&current,sizeof(current));

        if (end > 0)
        {
            NONPRIM=false;
            RR=false;
            SRTF=false;

            new_proc = true;
            cout << current.name << " IS IN RUNNING STATE NOW" << endl;

            if(strcmp(current.algorithm,"FCFS") == 0 || strcmp(current.algorithm,"SJF") == 0)
            {
                NONPRIM = true;
            }

            else if(strcmp(current.algorithm,"RR") == 0)
            {
                RR = true;
                quantum = current.quantum;
                current.own_quantum = 0;
            }

            else if(strcmp(current.algorithm,"SRTF") == 0)
            {
                SRTF = true;
                once = true;
                remaining = 0;
            }
        }

        else if(end == -1 and new_proc == false)
        {
            sleep(1);
            continue;
        }

        //for srtf
        if(once)
        {
            once = false;
            pthread_create(&thread1,NULL,readremaining,NULL);
        }

        sleep(1);

        if(current.given_time == current.burst_time and new_proc == true)
        {
            new_proc = false;

            //sending it to exit process
            write(run_exit_fd[1],&current,sizeof(current)) ;

            sendmenewproc;
        }


        else if (current.given_time != current.burst_time and new_proc == true)
        {
            //generating rand no to check whether to send him to block state
            if(ticks % 5 == 0)
            {           
                random_no = random;

                //send him to blocked state
                if(random_no == 0)
                {
                    write(run_block_fd[1],&current,sizeof(current));
                    new_proc = false;
                    sendmenewproc;
                    continue;
                }
            }

            if(NONPRIM)
                current.given_time++ ;//giving him its time

            else if(RR)
            {
                //send to ready queue
                if(current.own_quantum == current.quantum)
                {
                    write(run_ready_fd[1],&current,sizeof(current));
                    new_proc = false;
                    sendmenewproc;
                    continue;
                }

                else
                {
                    current.given_time++;
                    current.own_quantum++;
                }
                
            }

            else if(SRTF)
            {
                //send to ready queue
                if(remaining != 0)
                {
                    if( remaining < (current.burst_time-current.given_time) )
                    {
                        write(run_ready_fd[1],&current,sizeof(current));
                        new_proc = false;
                        sendmenewproc;
                        remaining = 0;
                        continue;
                    }

                    else
                        current.given_time++;                                        
                }

                else
                {
                    current.given_time++;
                }
                
            }
        }
    }

    cout << endl << "//////////////////////////////////////////////////////////////////////////////" << endl ;
    cout << "RUNNING PROCESS EXITING" << endl ;
    cout << "//////////////////////////////////////////////////////////////////////////////" << endl << endl ;

    exit(0);
}

void * readremaining(void * arg)
{
    //blocked reading the remaining time
    while(1)
    {
        read(r_run_status2_fd[0],&temp,sizeof(temp));
        remaining = temp;
    }
}
