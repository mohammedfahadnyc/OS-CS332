/*
CSc332 OS Lab
Instructor: Sujoy Debnath
Author: Mohammed Fahad
Lab 2, part 3: Write a program,where a parent process creates 2 child process and computes S1 and S2. And Parent process computes S3. The input argument for program will be the end of series number for S3.Show intermediate steps computed by children and parent
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include <stdio.h>
#include<ctype.h>
  
int main(int argc,char *argv[]){
    
    pid_t n1,n2;
    int fd1[2];                                 // this pipe is used to communicate with child process1 with parent process
    int fd2[2];                                 // this pipe is used to communicate with child process2 with parent process
    char S1_str[100];
    char S2_str[100];
    int S1_Ret,S2_Ret,S3;
    int n,i;
        
    if(argc<2){                                 // if command line argument is not specified
    
        printf("Limit is not specified as argument\n");
        exit(0);
    }
                
    n=atoi(argv[1]);                            // here n is the limit
    if (pipe(fd1)==-1){                         // if pipe1 fails
        fprintf(stderr, "Pipe1 Failed" );
        return 1;
    }
    if (pipe(fd2)==-1){                         // if pipe2 fails
        fprintf(stderr, "Pipe2 Failed" );
        return 1;
    }
    // Creating first child
    n1 = fork();
    if(n1<0){                                        // if first child fails
    
      fprintf(stderr, "child process1 failed");
      exit(-1);
    }
         
    // Creating first child
    n2 = fork();
     if(n2<0){                                       // if second child fails
    
      fprintf(stderr, "child process2 failed");
      exit(-1);
    }
  
    if (n1 > 0 && n2 > 0) {                       // in parent process
        
         close(fd1[1]);                         // Close writing end of first pipe
         close(fd2[1]);                         // Close writing end of second pipe
         wait(NULL);                            // wait parent process until chid process ends
         read(fd1[0], S1_str, 100);             // read result from first child process to S1_str
         read(fd2[0], S2_str, 100);             // read result from second child process to S2_str
         S1_Ret=atoi(S1_str);                   // convert first result to number
         S2_Ret=atoi(S2_str);                   // convert second result to number
         S3=S1_Ret+S2_Ret;                      // calculate result of parent process
         printf("S3=%d\n",S3);                  // print result of parent process
         
        
    }
    else if (n1 == 0 && n2 > 0){             // child process 1
        int S1=0;
        char S1_send[100];
        close(fd1[0]);                          // close the reading end of pipe1
        for(i=1;i<=n;i=i+2){                 // calculate series (1+3+5...+n)
        
                S1=S1+i ;
        }
        printf("S1=%d\n",S1);                   // print child process1 result
        sprintf(S1_send,"%d",S1);
        write(fd1[1], S1_send, strlen(S1_send)+1);// send rthis result to parent process
        sleep(1);
    }
    else if (n1 > 0 && n2 == 0){             // child process 2
    
        int S2=0,j;

        char S2_send[100];
        close(fd2[0]);                          // close the reading end of pipe2
        for(j=2;j<=n;j=j+2){                 // calculate series (2+4+6...+n)
        
                S2=S2+j ;
        }
        printf("S2=%d\n",S2);                   // calculate series (1+3+5...+n)
        sprintf(S2_send,"%d",S2);
        
        write(fd2[1], S2_send, strlen(S2_send)+1);// send rthis result to parent process
    }
    
    return 0;
}
