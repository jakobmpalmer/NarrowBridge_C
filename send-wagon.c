#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Prototypes */
void SendWagon(int dir, int time);
int RandomRange(int lowBound, int upBound);

struct Wagon 
{ 
    int dir;
    int time;
};


int main() 
{
    srand(time(0));
    SendWagon(RandomRange(0,1), RandomRange(3,6));

return 0;

}


void SendWagon(int dir, int time)
{    
    struct Wagon wagon = {dir, time};

    if (dir == 1)
    {    /* Going North */
        
        printf("Wagon going North . . .\n\tThe travel time is, %d minutes\n", time);


    } else {  /* Going South */
        printf("Wagon going South . . .\n\tThe travel time is, %d minutes\n", time);
    }

}



int RandomRange(int lowBound, int upBound) 
{       int lower = lowBound;
        int upper = upBound;

        int rNum = (rand() % (upper - lower + 1)) + lower; 
        //printf("%d ", rNum); 
        return rNum;
} 