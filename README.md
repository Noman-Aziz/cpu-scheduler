# cpu-scheduler
LINUX CPU SCHEDULING SIMULATOR (5 STATE MODEL)

I have created a 5 State Cpu Scheduling program in C++

I have make use of Linux system calls such as fork, exec, pipes (named/unnamed pipes depending on the requirement of communication), dup/dup2 as well as pthread library.

For Further Details, see the PDF attached for Project Description.

To Compile and Use the Program see compile_instructions.txt File.

Known Issues:-
- Mutex or Semaphores are Not Implemented so Multitheading may give false values due to preemption (Very Little Chance).
- The MinHeap Class is made with LinkedLists and Not Binary Tree.
