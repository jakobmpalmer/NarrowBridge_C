#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/sem.h>
#include<semaphore.h>


/* Prototypes */
int ReturnRandom();
void SendWagon();
/* -------------------*/



// int sem_create(int num_semaphores)
// { /* procedure to create specified number of semaphores */
//     int semid;
//     /* create new semaphore set of semaphores */
//     if ((semid = semget (IPC_PRIVATE, num_semaphores, IPC_CREAT | 0600)) < 0)
//     { 
//         perror ("error in creating semaphore");/* 0600 = read/alter by user */
//         exit (1);
//     }
//     return semid;
// }

// void sem_init(int semid, int index, int value)
// { /* procedure to initialize specified semaphore to given value */
//     if (semctl (semid, index, SETVAL, value) < 0)
//     { 
//         perror ("error in initializing first semaphore");
//         exit (1);
//     }
// }



int main()
{
    FILE *fpin,*fpout;/* file variables for main process I/O*/
    int fd[2];
    pid_t pid1, pid2;

    sem_t aSem;
    int semid; /* identifier for a semaphore set */

     fpin = popen("/home/jakobmp/Documents/programming/repositories/academic_repo/c_prog/CS451/narrowbridge/send-wagon", "w");
     //fpin = popen("/home/jakobmp/Documents/programming/repositories/academic_repo/c_prog/CS451/narrowbridge/send-wagons 5", "w");
     
     




     for (int i = 0; i < 10; i++) /* For (those wagons) */
     {

            if (pipe(fd)< 0)/* createpipeandcheckforan error*/
            {
                perror("pipeerror");
                exit(1);
            }
            
            if ((pid1= fork())< 0)/* applyforkandcheckforerror*/
            { 
                perror("errorin fork");
                exit(1);
            }


        if (0 == pid1)
            { /* processingforchild*/
            printf("Thefirstchildprocessis active.\n");
            close(fd[1]);/* closeoutputend,leavinginputopen*/
            /* setstandardinputto pipe*/
            
            if (fd[0]!=STDIN_FILENO)
            { 
                
                if (dup2(fd[0],STDIN_FILENO)!= STDIN_FILENO)
                {
                    perror("dup2errorforstandardinput");
                    exit(1);
                }
                
                close(fd[0]);/* notneededafterdup2*/
                
            }
            
            execlp("sort","sort","-n","+5",(char*) 0);
            printf("Firstchildfinished\n");
            }else{ /* processingforparent*/
            
            printf("Theparentprocesscontinues.\n");/* spawnsecondprocess*/
            
            if ((pid2= fork())< 0)/* applyforkagainforsecondchild*/
            { 
                perror("errorin fork");
                exit(1);

            }
            
            if (0 == pid2)
            { /* processingforchild*/
            printf("Thesecondchildprocessis active.\n");
            close(fd[0]);/* closeinputend,leavingoutputopen*/
            /* setstandardoutputto pipe*/
            
            if (fd[1]!=STDOUT_FILENO)
            { 
                if (dup2(fd[1],STDOUT_FILENO)!= STDOUT_FILENO)
                {
                    perror("dup2errorforstandardoutput");
                    exit(1);
                }
                
                close(fd[1]);/* notneededafterdup2*/
            }
            
            execlp("cat","cat","/home/walker/151s/labs/ia-senate",(char*) 0);/* printto thepipe,nowstandardoutput*/
            } else { /* processingcontinuesforparent*/
                printf("Parentclosingitspipeends:parentdoesnotusepipe\n");
                close(fd[0]);
                close(fd[1]);
                printf("Parentwaitsforbothchildrento finish.\n");
                waitpid(pid1,NULL,0);/* waitforfirstchildto finish*/
                waitpid(pid2,NULL,0);/* waitforsecondchildto finish*/
                printf("Parentfinished.\n");
                    }
            

!!!!!!!!!!!!!!!!!!!



         /* code */
     }
     

        
    
    return 0;
} //main







// int ReturnRandom() 
// {       int lower = 0;
//         int upper = 10;

//         int rNum = (rand() % (upper - lower + 1)) + lower; 
//         //printf("%d ", rNum); 
//         return rNum;
// } 

// int RandomRange(int lowBound, int upBound) 
// {       int lower = lowBound;
//         int upper = upBound;

//         int rNum = (rand() % (upper - lower + 1)) + lower; 
//         //printf("%d ", rNum); 
//         return rNum;
// } 