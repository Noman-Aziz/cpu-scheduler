#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
using namespace std;

int main()
{
    cout << endl << "//////////////////////////////////////////////////////////////////////////////" << endl ;
    cout << "I AM THE DISPATCHER AND I AM ABOUT TO CREATE 5 PROCESSES SHOWING 5 STATE MODEL" << endl ;
    cout << "//////////////////////////////////////////////////////////////////////////////" << endl << endl ;

    int new_ready_fd[2] ;
    int ready_run_fd[2] ;
    int run_ready_fd[2] ;
    int run_block_fd[2] ;
    int block_ready_fd[2] ;
    int run_exit_fd[2] ;

    //now some status pipes
    int n_r_status_fd[2];   //for new to send status to ready to exit
    int n_run_status_fd[2]; //for new to send status to run to exit
    int n_b_status_fd[2]; //for new to send status to block to exit
    int e_n_status_fd[2]; //for exit to send status to new to exit
    int n_e_status_fd[2]; //to send the total no of processes to exit
    int r_r_status_fd[2];   //for running to send status to ready to send me more processes
    int r_run_status2_fd[2];    //for srtf to send remaining time to running proc from ready proc

   	if ( pipe(new_ready_fd) < 0 )
	{
		cout << "PIPE 1 NOT CREATED ! EXITING\n" ;
		exit(1) ;
	} 

   	if ( pipe(ready_run_fd) < 0 )
	{
		cout << "PIPE 2 NOT CREATED ! EXITING\n" ;
		exit(1) ;
	} 

   	if ( pipe(run_ready_fd) < 0 )
	{
		cout << "PIPE 3 NOT CREATED ! EXITING\n" ;
		exit(1) ;
	} 

   	if ( pipe(run_block_fd) < 0 )
	{
		cout << "PIPE 4 NOT CREATED ! EXITING\n" ;
		exit(1) ;
	} 

   	if ( pipe(block_ready_fd) < 0 )
	{
		cout << "PIPE 5 NOT CREATED ! EXITING\n" ;
		exit(1) ;
	} 

   	if ( pipe(run_exit_fd) < 0 )
	{
		cout << "PIPE 6 NOT CREATED ! EXITING\n" ;
		exit(1) ;
	} 

   	if ( pipe(n_r_status_fd) < 0 )
	{
		cout << "PIPE 7 NOT CREATED ! EXITING\n" ;
		exit(1) ;
	} 

   	if ( pipe(r_r_status_fd) < 0 )
	{
		cout << "PIPE 8 NOT CREATED ! EXITING\n" ;
		exit(1) ;
	} 

   	if ( pipe(n_e_status_fd) < 0 )
	{
		cout << "PIPE 9 NOT CREATED ! EXITING\n" ;
		exit(1) ;
	} 

   	if ( pipe(e_n_status_fd) < 0 )
	{
		cout << "PIPE 10 NOT CREATED ! EXITING\n" ;
		exit(1) ;
	} 

   	if ( pipe(n_b_status_fd) < 0 )
	{
		cout << "PIPE 11 NOT CREATED ! EXITING\n" ;
		exit(1) ;
	} 

   	if ( pipe(n_run_status_fd) < 0 )
	{
		cout << "PIPE 12 NOT CREATED ! EXITING\n" ;
		exit(1) ;
	} 

   	if ( pipe(r_run_status2_fd) < 0 )
	{
		cout << "PIPE 13 NOT CREATED ! EXITING\n" ;
		exit(1) ;
	} 

    if ( !fork() )
    {
        //Ready State
        execl("Ready","Ready",to_string(new_ready_fd[0]).c_str(),to_string(new_ready_fd[1]).c_str(),
              to_string(ready_run_fd[0]).c_str(),to_string(ready_run_fd[1]).c_str(),
              to_string(run_ready_fd[0]).c_str(),to_string(run_ready_fd[1]).c_str(),
              to_string(block_ready_fd[0]).c_str(),to_string(block_ready_fd[1]).c_str(),
              to_string(n_r_status_fd[0]).c_str(),to_string(n_r_status_fd[1]).c_str(),
              to_string(r_r_status_fd[0]).c_str(),to_string(r_r_status_fd[1]).c_str(),
              to_string(r_run_status2_fd[0]).c_str(),to_string(r_run_status2_fd[1]).c_str(),NULL
             );
    }

    if ( !fork() )
    {
        //Running State
        execl("Running","Running",to_string(ready_run_fd[0]).c_str(),to_string(ready_run_fd[1]).c_str(),
              to_string(run_ready_fd[0]).c_str(),to_string(run_ready_fd[1]).c_str(),
              to_string(run_block_fd[0]).c_str(),to_string(run_block_fd[1]).c_str(),
              to_string(run_exit_fd[0]).c_str(),to_string(run_exit_fd[1]).c_str(),
              to_string(r_r_status_fd[0]).c_str(),to_string(r_r_status_fd[1]).c_str(),
              to_string(n_run_status_fd[0]).c_str(),to_string(n_run_status_fd[1]).c_str(),
              to_string(r_run_status2_fd[0]).c_str(),to_string(r_run_status2_fd[1]).c_str(),NULL
             );
    }

    if ( !fork() )
    {
        //Blocked State
        execl("Blocked","Blocked",to_string(run_block_fd[0]).c_str(),to_string(run_block_fd[1]).c_str(),
              to_string(block_ready_fd[0]).c_str(),to_string(block_ready_fd[1]).c_str(),
              to_string(n_b_status_fd[0]).c_str(),to_string(n_b_status_fd[1]).c_str(),NULL
             );
    }   
    
    if ( !fork() )
    {
        //Exit State
        execl("Exit","Exit",to_string(run_exit_fd[0]).c_str(),to_string(run_exit_fd[1]).c_str(),
              to_string(n_e_status_fd[0]).c_str(),to_string(n_e_status_fd[1]).c_str(),
              to_string(e_n_status_fd[0]).c_str(),to_string(e_n_status_fd[1]).c_str(),NULL
             );
    }

    if ( !fork() )
    {
        //New State
        execl("New","New",to_string(new_ready_fd[0]).c_str(),to_string(new_ready_fd[1]).c_str(),
              to_string(n_r_status_fd[0]).c_str(),to_string(n_r_status_fd[1]).c_str(),
              to_string(n_e_status_fd[0]).c_str(),to_string(n_e_status_fd[1]).c_str(),
              to_string(e_n_status_fd[0]).c_str(),to_string(e_n_status_fd[1]).c_str(),
              to_string(n_b_status_fd[0]).c_str(),to_string(n_b_status_fd[1]).c_str(),
              to_string(n_run_status_fd[0]).c_str(),to_string(n_run_status_fd[1]).c_str(),NULL
             );
        cout << "FAILED" << endl ;
    }

    sleep(2);
    cout << endl;

    //Dispatcher will exit when all 5 processes have exited
    wait(0);
    wait(0);
    wait(0);
    wait(0);
    wait(0);

    cout << endl << "//////////////////////////////////////////////////////////////////////////////" << endl ;
    cout << "DISPATCHER EXITING NOW" << endl ;
    cout << "//////////////////////////////////////////////////////////////////////////////" << endl ;

    return 0 ;
}