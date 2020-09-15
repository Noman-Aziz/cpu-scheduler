struct Procs
{
    char name[10];
    int arrival_time;
    int burst_time;
    int priority;
    int waiting_time;
    int given_time;
    int turn_around_time;
    int blocked_time;   //how much blocked time it has passed
    int given_blocked_time; //how much blocked time its given
    char algorithm[10] ;
    int quantum;
    int own_quantum;    //for RR

    Procs()
    {
        priority = 0;
        waiting_time = 0;
        given_time = 0;
        turn_around_time = 0;
        blocked_time = 0;
        given_blocked_time = 0;
        quantum = 0;
        own_quantum=0;
    }

    void operator = (const Procs &temp)
    {
        for ( int i=0 ; ; i++)
        {
            name[i] = temp.name[i] ;
            if(name[i] == '\0')
                break; 
        }

        arrival_time = temp.arrival_time;
        burst_time = temp.burst_time;
        priority = temp.priority;
        waiting_time = temp.waiting_time;    
        given_time = temp.given_time;
        turn_around_time = temp.turn_around_time;
        blocked_time = temp.blocked_time;
        given_blocked_time = temp.given_blocked_time;

        for ( int i=0 ; ; i++)
        {
            algorithm[i] = temp.algorithm[i] ;
            if(algorithm[i] == '\0')
                break; 
        }

        quantum = temp.quantum;
        own_quantum = temp.own_quantum;
    }

    bool operator < (const Procs &temp)
    {
        if( algorithm[0] == 'S' and algorithm[1] == 'J' and algorithm[2] == 'F' )
        {
            if (burst_time < temp.burst_time)
                return true;

            return false;
        }

        else
        {
            if ( (burst_time-given_time) < (temp.burst_time-temp.given_time) )
                return true;

            return false;
        }
    } 
};