#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
#include"Queue.h"
#include"MinHeap.h"
#include"Procs.h"

#define clearbuffer memset(buffer,0,10)

using namespace std;

void initializeRR();
void initializeFCFS();
void initializeSJF();
void initializeSRTF();

void sendProcs();

int new_ready_fd[2];
int n_r_status_fd[2];
int n_e_status_fd[2];
int e_n_status_fd[2];
int n_b_status_fd[2];
int n_run_status_fd[2];

Queue<Procs> Storage;

int main( int argc, char *argv[] )
{
    int choice;

    cout << "I AM NEW PROCESS\n" ;

    sleep(2);

    new_ready_fd[0] = atoi(argv[1]) ;
    new_ready_fd[1] = atoi(argv[2]) ;

    n_r_status_fd[0] = atoi(argv[3]) ;
    n_r_status_fd[1] = atoi(argv[4]) ;

    n_e_status_fd[0] = atoi(argv[5]) ;
    n_e_status_fd[1] = atoi(argv[6]) ;

    e_n_status_fd[0] = atoi(argv[7]) ;
    e_n_status_fd[1] = atoi(argv[8]) ;

    n_b_status_fd[0] = atoi(argv[9]) ;
    n_b_status_fd[1] = atoi(argv[10]) ;

    n_run_status_fd[0] = atoi(argv[11]) ;
    n_run_status_fd[1] = atoi(argv[12]) ;

    cout << endl << "YOU CAN IMPLEMENT ONE OF THE FOLLOWING ALGORITHMS :- \n";
    cout << "1. RR" << endl;
    cout << "2. FCFS" << endl;
    cout << "3. SJF" << endl;
    cout << "4. SRTF" << endl;
    cout << "WHATS IT GONNA BE :- " ;
    cin >> choice;
    cout << endl;

    while(1)
    {
        if(choice != 1 && choice != 2 && choice != 3 && choice != 4)
        {
            cout << "WRONG CHOICE TRY AGAIN :- ";
            cin >> choice;
            cout << endl;
        }

        else
            break;       
    }

    switch(choice)
    {
        case 1: initializeRR();
                sendProcs();
                break;
        case 2: initializeFCFS();
                sendProcs();
                break;
        case 3: initializeSJF();
                sendProcs();
                break;
        case 4: initializeSRTF();
                sendProcs();
                break;
    }

    bool exitstatus = true;

    //waiting for exit status from exit
    read(e_n_status_fd[0],&exitstatus,sizeof(bool));

    //telling other processes to exit
    write(n_b_status_fd[1],&exitstatus,sizeof(bool));
    write(n_r_status_fd[1],&exitstatus,sizeof(bool));
    write(n_run_status_fd[1],&exitstatus,sizeof(bool));

    cout << endl << "//////////////////////////////////////////////////////////////////////////////" << endl ;
    cout << "NEW PROCESS IS EXITING" << endl;
    cout << "//////////////////////////////////////////////////////////////////////////////" << endl << endl ;

    exit(0);
}

void initializeRR()
{
    int fd1 = open("RR.txt",O_RDONLY) ;

    char buffer[10] ;
    Procs temp ;
    int quantum;

    read(fd1,buffer,4);
    clearbuffer;

    //reading quantum
    read(fd1,buffer,3) ;

    //setting quantum
    quantum = atoi(buffer) ;

    clearbuffer;

    //reading details about proc

    //////////////////////////proc1

    read(fd1,buffer,7) ;
    buffer[5] = '\0';

    for (int i=0 ; ; i++)
    {
        temp.name[i] = buffer[i];

        if(buffer[i] == '\0')
            break;
    }

    clearbuffer;

    read(fd1,buffer,3);

    temp.arrival_time = atoi(buffer) ;

    clearbuffer;

    read(fd1,buffer,3);

    temp.burst_time = atoi(buffer) ;

    clearbuffer;

    temp.quantum = quantum;

    temp.algorithm[0] = 'R';
    temp.algorithm[1] = 'R';
    temp.algorithm[2] = '\0';

    Storage.enqueue(temp);

    ///////////////////////////////////////proc2

    read(fd1,buffer,7) ;
    buffer[5] = '\0';

    for (int i=0 ; ; i++)
    {
        temp.name[i] = buffer[i];

        if(buffer[i] == '\0')
            break;
    }

    clearbuffer;

    read(fd1,buffer,3);

    temp.arrival_time = atoi(buffer) ;

    clearbuffer;

    read(fd1,buffer,3);

    temp.burst_time = atoi(buffer) ;

    clearbuffer;

    temp.quantum = quantum;

    temp.algorithm[0] = 'R';
    temp.algorithm[1] = 'R';
    temp.algorithm[2] = '\0';

    Storage.enqueue(temp);

    //////////////////////////////////////proc3

    read(fd1,buffer,7) ;
    buffer[5] = '\0';

    for (int i=0 ; ; i++)
    {
        temp.name[i] = buffer[i];

        if(buffer[i] == '\0')
            break;
    }

    clearbuffer;

    read(fd1,buffer,3);

    temp.arrival_time = atoi(buffer) ;

    clearbuffer;

    read(fd1,buffer,3);

    temp.burst_time = atoi(buffer) ;

    clearbuffer;

    temp.quantum = quantum;

    temp.algorithm[0] = 'R';
    temp.algorithm[1] = 'R';
    temp.algorithm[2] = '\0';

    Storage.enqueue(temp);

    ////////////////////////////////////////proc4

    read(fd1,buffer,7) ;
    buffer[5] = '\0';

    for (int i=0 ; ; i++)
    {
        temp.name[i] = buffer[i];

        if(buffer[i] == '\0')
            break;
    }

    clearbuffer;

    read(fd1,buffer,3);

    temp.arrival_time = atoi(buffer) ;

    clearbuffer;

    read(fd1,buffer,3);

    temp.burst_time = atoi(buffer) ;

    clearbuffer;

    temp.quantum = quantum;

    temp.algorithm[0] = 'R';
    temp.algorithm[1] = 'R';
    temp.algorithm[2] = '\0';

    Storage.enqueue(temp);

    //////////////////////////////////////////proc5

    read(fd1,buffer,7) ;
    buffer[5] = '\0';

    for (int i=0 ; ; i++)
    {
        temp.name[i] = buffer[i];

        if(buffer[i] == '\0')
            break;
    }

    clearbuffer;

    read(fd1,buffer,3);

    temp.arrival_time = atoi(buffer) ;

    clearbuffer;

    read(fd1,buffer,3);

    temp.burst_time = atoi(buffer) ;

    clearbuffer;

    temp.quantum = quantum;

    temp.algorithm[0] = 'R';
    temp.algorithm[1] = 'R';
    temp.algorithm[2] = '\0';

    Storage.enqueue(temp);     

    ///////////////////////////////////////proc6

    read(fd1,buffer,7) ;
    buffer[5] = '\0';

    for (int i=0 ; ; i++)
    {
        temp.name[i] = buffer[i];

        if(buffer[i] == '\0')
            break;
    }

    clearbuffer;

    read(fd1,buffer,3);

    temp.arrival_time = atoi(buffer) ;

    clearbuffer;

    read(fd1,buffer,4);

    temp.burst_time = atoi(buffer) ;

    clearbuffer;

    temp.quantum = quantum;

    temp.algorithm[0] = 'R';
    temp.algorithm[1] = 'R';
    temp.algorithm[2] = '\0';

    Storage.enqueue(temp);
}

void initializeFCFS()
{
    int fd2 = open("FCFS.txt",O_RDONLY) ;

    char buffer[10] ;
    Procs temp ;

    read(fd2,buffer,6);
    clearbuffer;

    //reading details about proc

    //////////////////////////proc1

    read(fd2,buffer,7) ;
    buffer[5] = '\0';

    for (int i=0 ; ; i++)
    {
        temp.name[i] = buffer[i];

        if(buffer[i] == '\0')
            break;
    }

    clearbuffer;

    read(fd2,buffer,3);

    temp.arrival_time = atoi(buffer) ;

    clearbuffer;

    read(fd2,buffer,3);

    temp.burst_time = atoi(buffer) ;

    clearbuffer;

    temp.algorithm[0] = 'F';
    temp.algorithm[1] = 'C';
    temp.algorithm[2] = 'F';
    temp.algorithm[3] = 'S';
    temp.algorithm[4] = '\0';

    Storage.enqueue(temp);

    ///////////////////////////////////////proc2

    read(fd2,buffer,7) ;
    buffer[5] = '\0';

    for (int i=0 ; ; i++)
    {
        temp.name[i] = buffer[i];

        if(buffer[i] == '\0')
            break;
    }

    clearbuffer;

    read(fd2,buffer,3);

    temp.arrival_time = atoi(buffer) ;

    clearbuffer;

    read(fd2,buffer,3);

    temp.burst_time = atoi(buffer) ;

    clearbuffer;

    temp.algorithm[0] = 'F';
    temp.algorithm[1] = 'C';
    temp.algorithm[2] = 'F';
    temp.algorithm[3] = 'S';
    temp.algorithm[4] = '\0';

    Storage.enqueue(temp);

    //////////////////////////////////////proc3

    read(fd2,buffer,7) ;
    buffer[5] = '\0';

    for (int i=0 ; ; i++)
    {
        temp.name[i] = buffer[i];

        if(buffer[i] == '\0')
            break;
    }

    clearbuffer;

    read(fd2,buffer,3);

    temp.arrival_time = atoi(buffer) ;

    clearbuffer;

    read(fd2,buffer,3);

    temp.burst_time = atoi(buffer) ;

    clearbuffer;

    temp.algorithm[0] = 'F';
    temp.algorithm[1] = 'C';
    temp.algorithm[2] = 'F';
    temp.algorithm[3] = 'S';
    temp.algorithm[4] = '\0';

    Storage.enqueue(temp);

    ////////////////////////////////////////proc4

    read(fd2,buffer,7) ;
    buffer[5] = '\0';

    for (int i=0 ; ; i++)
    {
        temp.name[i] = buffer[i];

        if(buffer[i] == '\0')
            break;
    }

    clearbuffer;

    read(fd2,buffer,3);

    temp.arrival_time = atoi(buffer) ;

    clearbuffer;

    read(fd2,buffer,3);

    temp.burst_time = atoi(buffer) ;

    clearbuffer;

    temp.algorithm[0] = 'F';
    temp.algorithm[1] = 'C';
    temp.algorithm[2] = 'F';
    temp.algorithm[3] = 'S';
    temp.algorithm[4] = '\0';

    Storage.enqueue(temp);

    //////////////////////////////////////////proc5

    read(fd2,buffer,7) ;
    buffer[5] = '\0';

    for (int i=0 ; ; i++)
    {
        temp.name[i] = buffer[i];

        if(buffer[i] == '\0')
            break;
    }

    clearbuffer;

    read(fd2,buffer,3);

    temp.arrival_time = atoi(buffer) ;

    clearbuffer;

    read(fd2,buffer,4);

    temp.burst_time = atoi(buffer) ;

    clearbuffer;

    temp.algorithm[0] = 'F';
    temp.algorithm[1] = 'C';
    temp.algorithm[2] = 'F';
    temp.algorithm[3] = 'S';
    temp.algorithm[4] = '\0';

    Storage.enqueue(temp);     

    ///////////////////////////////////////proc6

    read(fd2,buffer,7) ;
    buffer[5] = '\0';

    for (int i=0 ; ; i++)
    {
        temp.name[i] = buffer[i];

        if(buffer[i] == '\0')
            break;
    }

    clearbuffer;

    read(fd2,buffer,4);

    temp.arrival_time = atoi(buffer) ;

    clearbuffer;

    read(fd2,buffer,4);

    temp.burst_time = atoi(buffer) ;

    clearbuffer;

    temp.algorithm[0] = 'F';
    temp.algorithm[1] = 'C';
    temp.algorithm[2] = 'F';
    temp.algorithm[3] = 'S';
    temp.algorithm[4] = '\0';

    Storage.enqueue(temp);

    ///////////////////////////////////////proc7

    read(fd2,buffer,7) ;
    buffer[5] = '\0';

    for (int i=0 ; ; i++)
    {
        temp.name[i] = buffer[i];

        if(buffer[i] == '\0')
            break;
    }

    clearbuffer;

    read(fd2,buffer,4);

    temp.arrival_time = atoi(buffer) ;

    clearbuffer;

    read(fd2,buffer,3);

    temp.burst_time = atoi(buffer) ;

    clearbuffer;

    temp.algorithm[0] = 'F';
    temp.algorithm[1] = 'C';
    temp.algorithm[2] = 'F';
    temp.algorithm[3] = 'S';
    temp.algorithm[4] = '\0';

    Storage.enqueue(temp);
}

void initializeSJF()
{
    int fd3 = open("SJF.txt",O_RDONLY) ;

    char buffer[10] ;
    Procs temp ;

    read(fd3,buffer,5);
    clearbuffer;

    //reading details about proc

    //////////////////////////proc1

    read(fd3,buffer,7) ;
    buffer[5] = '\0';

    for (int i=0 ; ; i++)
    {
        temp.name[i] = buffer[i];

        if(buffer[i] == '\0')
            break;
    }

    clearbuffer;

    read(fd3,buffer,3);

    temp.arrival_time = atoi(buffer) ;

    clearbuffer;

    read(fd3,buffer,3);

    temp.burst_time = atoi(buffer) ;

    clearbuffer;

    temp.algorithm[0] = 'S';
    temp.algorithm[1] = 'J';
    temp.algorithm[2] = 'F';
    temp.algorithm[3] = '\0';

    Storage.enqueue(temp);

    ///////////////////////////////////////proc2

    read(fd3,buffer,7) ;
    buffer[5] = '\0';

    for (int i=0 ; ; i++)
    {
        temp.name[i] = buffer[i];

        if(buffer[i] == '\0')
            break;
    }

    clearbuffer;

    read(fd3,buffer,3);

    temp.arrival_time = atoi(buffer) ;

    clearbuffer;

    read(fd3,buffer,3);

    temp.burst_time = atoi(buffer) ;

    clearbuffer;

    temp.algorithm[0] = 'S';
    temp.algorithm[1] = 'J';
    temp.algorithm[2] = 'F';
    temp.algorithm[3] = '\0';

    Storage.enqueue(temp);

    //////////////////////////////////////proc3

    read(fd3,buffer,7) ;
    buffer[5] = '\0';

    for (int i=0 ; ; i++)
    {
        temp.name[i] = buffer[i];

        if(buffer[i] == '\0')
            break;
    }

    clearbuffer;

    read(fd3,buffer,3);

    temp.arrival_time = atoi(buffer) ;

    clearbuffer;

    read(fd3,buffer,3);

    temp.burst_time = atoi(buffer) ;

    clearbuffer;

    temp.algorithm[0] = 'S';
    temp.algorithm[1] = 'J';
    temp.algorithm[2] = 'F';
    temp.algorithm[3] = '\0';

    Storage.enqueue(temp);

    ////////////////////////////////////////proc4

    read(fd3,buffer,7) ;
    buffer[5] = '\0';

    for (int i=0 ; ; i++)
    {
        temp.name[i] = buffer[i];

        if(buffer[i] == '\0')
            break;
    }

    clearbuffer;

    read(fd3,buffer,3);

    temp.arrival_time = atoi(buffer) ;

    clearbuffer;

    read(fd3,buffer,3);

    temp.burst_time = atoi(buffer) ;

    clearbuffer;

    temp.algorithm[0] = 'S';
    temp.algorithm[1] = 'J';
    temp.algorithm[2] = 'F';
    temp.algorithm[3] = '\0';

    Storage.enqueue(temp);

    //////////////////////////////////////////proc5

    read(fd3,buffer,7) ;
    buffer[5] = '\0';

    for (int i=0 ; ; i++)
    {
        temp.name[i] = buffer[i];

        if(buffer[i] == '\0')
            break;
    }

    clearbuffer;

    read(fd3,buffer,3);

    temp.arrival_time = atoi(buffer) ;

    clearbuffer;

    read(fd3,buffer,3);

    temp.burst_time = atoi(buffer) ;

    clearbuffer;

    temp.algorithm[0] = 'S';
    temp.algorithm[1] = 'J';
    temp.algorithm[2] = 'F';
    temp.algorithm[3] = '\0';

    Storage.enqueue(temp);

    ///////////////////////////////////////proc6

    read(fd3,buffer,7) ;
    buffer[5] = '\0';

    for (int i=0 ; ; i++)
    {
        temp.name[i] = buffer[i];

        if(buffer[i] == '\0')
            break;
    }

    clearbuffer;

    read(fd3,buffer,4);

    temp.arrival_time = atoi(buffer) ;

    clearbuffer;

    read(fd3,buffer,3);

    temp.burst_time = atoi(buffer) ;

    clearbuffer;

    temp.algorithm[0] = 'S';
    temp.algorithm[1] = 'J';
    temp.algorithm[2] = 'F';
    temp.algorithm[3] = '\0';

    Storage.enqueue(temp);
}

void initializeSRTF()
{
    int fd3 = open("SRTF.txt",O_RDONLY) ;

    char buffer[10] ;
    Procs temp ;

    read(fd3,buffer,6);
    clearbuffer;

    //reading details about proc

    //////////////////////////proc1

    read(fd3,buffer,7) ;
    buffer[5] = '\0';

    for (int i=0 ; ; i++)
    {
        temp.name[i] = buffer[i];

        if(buffer[i] == '\0')
            break;
    }

    clearbuffer;

    read(fd3,buffer,3);

    temp.arrival_time = atoi(buffer) ;

    clearbuffer;

    read(fd3,buffer,4);

    temp.burst_time = atoi(buffer) ;

    clearbuffer;

    temp.algorithm[0] = 'S';
    temp.algorithm[1] = 'R';
    temp.algorithm[2] = 'T';
    temp.algorithm[3] = 'F';
    temp.algorithm[4] = '\0';

    Storage.enqueue(temp);

    ///////////////////////////////////////proc2

    read(fd3,buffer,7) ;
    buffer[5] = '\0';

    for (int i=0 ; ; i++)
    {
        temp.name[i] = buffer[i];

        if(buffer[i] == '\0')
            break;
    }

    clearbuffer;

    read(fd3,buffer,3);

    temp.arrival_time = atoi(buffer) ;

    clearbuffer;

    read(fd3,buffer,3);

    temp.burst_time = atoi(buffer) ;

    clearbuffer;

    temp.algorithm[0] = 'S';
    temp.algorithm[1] = 'R';
    temp.algorithm[2] = 'T';
    temp.algorithm[3] = 'F';
    temp.algorithm[4] = '\0';

    Storage.enqueue(temp);

    //////////////////////////////////////proc3

    read(fd3,buffer,7) ;
    buffer[5] = '\0';

    for (int i=0 ; ; i++)
    {
        temp.name[i] = buffer[i];

        if(buffer[i] == '\0')
            break;
    }

    clearbuffer;

    read(fd3,buffer,3);

    temp.arrival_time = atoi(buffer) ;

    clearbuffer;

    read(fd3,buffer,3);

    temp.burst_time = atoi(buffer) ;

    clearbuffer;

    temp.algorithm[0] = 'S';
    temp.algorithm[1] = 'R';
    temp.algorithm[2] = 'T';
    temp.algorithm[3] = 'F';
    temp.algorithm[4] = '\0';

    Storage.enqueue(temp);

    ////////////////////////////////////////proc4

    read(fd3,buffer,7) ;
    buffer[5] = '\0';

    for (int i=0 ; ; i++)
    {
        temp.name[i] = buffer[i];

        if(buffer[i] == '\0')
            break;
    }

    clearbuffer;

    read(fd3,buffer,3);

    temp.arrival_time = atoi(buffer) ;

    clearbuffer;

    read(fd3,buffer,3);

    temp.burst_time = atoi(buffer) ;

    clearbuffer;

    temp.algorithm[0] = 'S';
    temp.algorithm[1] = 'R';
    temp.algorithm[2] = 'T';
    temp.algorithm[3] = 'F';
    temp.algorithm[4] = '\0';

    Storage.enqueue(temp);

    //////////////////////////////////////////proc5

    read(fd3,buffer,7) ;
    buffer[5] = '\0';

    for (int i=0 ; ; i++)
    {
        temp.name[i] = buffer[i];

        if(buffer[i] == '\0')
            break;
    }

    clearbuffer;

    read(fd3,buffer,3);

    temp.arrival_time = atoi(buffer) ;

    clearbuffer;

    read(fd3,buffer,3);

    temp.burst_time = atoi(buffer) ;

    clearbuffer;

    temp.algorithm[0] = 'S';
    temp.algorithm[1] = 'R';
    temp.algorithm[2] = 'T';
    temp.algorithm[3] = 'F';
    temp.algorithm[4] = '\0';

    Storage.enqueue(temp);

    ///////////////////////////////////////proc6

    read(fd3,buffer,7) ;
    buffer[5] = '\0';

    for (int i=0 ; ; i++)
    {
        temp.name[i] = buffer[i];

        if(buffer[i] == '\0')
            break;
    }

    clearbuffer;

    read(fd3,buffer,3);

    temp.arrival_time = atoi(buffer) ;

    clearbuffer;

    read(fd3,buffer,3);

    temp.burst_time = atoi(buffer) ;

    clearbuffer;

    temp.algorithm[0] = 'S';
    temp.algorithm[1] = 'R';
    temp.algorithm[2] = 'T';
    temp.algorithm[3] = 'F';
    temp.algorithm[4] = '\0';

    Storage.enqueue(temp);

    ///////////////////////////////////////proc7

    read(fd3,buffer,7) ;
    buffer[5] = '\0';

    for (int i=0 ; ; i++)
    {
        temp.name[i] = buffer[i];

        if(buffer[i] == '\0')
            break;
    }

    clearbuffer;

    read(fd3,buffer,3);

    temp.arrival_time = atoi(buffer) ;

    clearbuffer;

    read(fd3,buffer,4);

    temp.burst_time = atoi(buffer) ;

    clearbuffer;

    temp.algorithm[0] = 'S';
    temp.algorithm[1] = 'R';
    temp.algorithm[2] = 'T';
    temp.algorithm[3] = 'F';
    temp.algorithm[4] = '\0';

    Storage.enqueue(temp);

    ///////////////////////////////////////proc8

    read(fd3,buffer,7) ;
    buffer[5] = '\0';

    for (int i=0 ; ; i++)
    {
        temp.name[i] = buffer[i];

        if(buffer[i] == '\0')
            break;
    }

    clearbuffer;

    read(fd3,buffer,3);

    temp.arrival_time = atoi(buffer) ;

    clearbuffer;

    read(fd3,buffer,3);

    temp.burst_time = atoi(buffer) ;

    clearbuffer;

    temp.algorithm[0] = 'S';
    temp.algorithm[1] = 'R';
    temp.algorithm[2] = 'T';
    temp.algorithm[3] = 'F';
    temp.algorithm[4] = '\0';

    Storage.enqueue(temp);

    ///////////////////////////////////////proc9

    read(fd3,buffer,7) ;
    buffer[5] = '\0';

    for (int i=0 ; ; i++)
    {
        temp.name[i] = buffer[i];

        if(buffer[i] == '\0')
            break;
    }

    clearbuffer;

    read(fd3,buffer,4);

    temp.arrival_time = atoi(buffer) ;

    clearbuffer;

    read(fd3,buffer,3);

    temp.burst_time = atoi(buffer) ;

    clearbuffer;

    temp.algorithm[0] = 'S';
    temp.algorithm[1] = 'R';
    temp.algorithm[2] = 'T';
    temp.algorithm[3] = 'F';
    temp.algorithm[4] = '\0';

    Storage.enqueue(temp);
}

void sendProcs()
{
    int ticks = 0;
    int totalprocs = 1;
    bool done = false;
    Procs temp = Storage.dequeue();

    //sending FCFS procs to ready
    while(!Storage.IsEmpty() || !done)
    {        
        while(ticks == temp.arrival_time)
        {
            //send to ready queue
            write(new_ready_fd[1],&temp,sizeof(temp));
            
            if(Storage.IsEmpty())
                break;

            temp = Storage.dequeue();
            totalprocs++;
        }

        if(ticks == temp.arrival_time and Storage.IsEmpty())
            done = true;

        sleep(1);
        ticks++;
    }

    //sending the total no of procs to exit
    write(n_e_status_fd[1],&totalprocs,sizeof(int));
}
