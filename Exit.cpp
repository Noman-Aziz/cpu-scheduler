#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
#include"Queue.h"
#include"Procs.h"

using namespace std;

#define newline write(fd,"\n",1)
#define writevalue write(fd,to_string(value).c_str(),strlen(to_string(value).c_str()))
#define writetab write(fd,"\t",1)

int value;

int fd = open("processes_stats.txt",O_TRUNC);

int main( int argc, char *argv[] )
{
    int run_exit_fd[2] ;
    int n_e_status_fd[2];
    int e_n_status_fd[2];

    run_exit_fd[0] = atoi(argv[1]) ;
    run_exit_fd[1] = atoi(argv[2]) ;

    n_e_status_fd[0] = atoi(argv[3]) ;
    n_e_status_fd[1] = atoi(argv[4]) ;

    e_n_status_fd[0] = atoi(argv[5]) ;
    e_n_status_fd[1] = atoi(argv[6]) ;

    Procs current;

    cout << "I AM EXIT PROCESS\n";

    sleep(1);

    close(fd);
    fd = open("processes_stats.txt",O_WRONLY);

    //making pipe unblocking
    fcntl(n_e_status_fd[0], F_SETFL, O_NONBLOCK);

    int totalprocs = 0;
    int receivedprocs = 0;

    //writing to file
    char message[10] ;

    while(1)
    {
        read(run_exit_fd[0],&current,sizeof(current));
        
        receivedprocs++;

        read(n_e_status_fd[0],&totalprocs,sizeof(int));

        current.turn_around_time = current.waiting_time + current.given_time ;        

        cout << current.name << " EXITED" << endl;

        //starting information
        if(receivedprocs == 1)
        {
            char message1[20] = "Algorithm : ";
            write(fd,message1,strlen(message1));

            char message2[20];
            for( int i = 0 ; current.algorithm[i] != '\0' ; i++ )
            {
                message2[i] = current.algorithm[i];

                if(current.algorithm[i+1] == '\0')
                    message2[i+1] = '\0';
            }
            
            write(fd,message2,strlen(message2));
            newline;

            if(strcmp(current.algorithm,"RR")==0)
            {
                char message0[20] = "Quantum : ";
                write(fd,message0,strlen(message0));
                value = current.quantum;
                writevalue;
                newline;                
            }

            char message3[100] = "PROC_NAME\tArrival_Time\tBurst_Time\tTurnaround_Time\tWaiting_Time";
            write(fd,message3,strlen(message3));
            newline;
        }

        //writing other info for gaant chart
        for( int i = 0 ; current.name[i] != '\0' ; i++ )
        {
            message[i] = current.name[i];

            if(current.name[i+1] == '\0')
                message[i+1] = '\0';
        }

        write(fd,message,strlen(message));
        writetab;
        writetab;
        value = current.arrival_time;
        writevalue;
        writetab;
        writetab;        
        value = current.burst_time;
        writevalue;
        writetab;
        writetab;        
        value = current.turn_around_time;
        writevalue;
        writetab;
        writetab;        
        value = current.waiting_time;
        writevalue;
        newline;

        if(receivedprocs == totalprocs)
            break;
    }

    bool exitstatus = true;
    write(e_n_status_fd[1],&exitstatus,sizeof(bool));

    close(fd);

    cout << endl << "//////////////////////////////////////////////////////////////////////////////" << endl ;
    cout << "EXIT PROCESS EXITING" << endl ;
    cout << "//////////////////////////////////////////////////////////////////////////////" << endl << endl ;

    exit(0);
}