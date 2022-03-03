/*
CSc332 OS Lab
Instructor: Sujoy Debnath
Author: Mohammed Fahad
Lab 2, part 4:Open a file called readme.txt in the child process, read the contents and pass to the parent process. Parent process will write to readme.txt, “Parent is writing:” and write the contents it received from the child to the readme.txt file.
*/


#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/wait.h>
int main()
{
    int pid;
    int pipefd[2];
    FILE *fp;
    pipe(pipefd);           // Creates pipe to read and write contents between parent and child process
    pid=fork();             //creates child process
    if(pid<0)
    {
        printf("fork error");
    }
    //Child process starts here
    if(pid==0)                      //check for Child process
    {
        fp = fopen("readme.txt", "r");   //Opening file in read mode.
        if(fp==NULL)
            printf("Error Occurred while Opening the File!");
        else
        {
            char Line[150];
            close(pipefd[0]);  //Close the read end of the pipe since it is using here for for writing
            while(fgets(Line, sizeof(Line), fp))
            {
                write(pipefd[1], Line, strlen(Line));
            }
        }
        fclose(fp);
        exit(0);
    }
    // Parent process starts here
    else
    {
        wait(NULL);               //parent process waits until all the child process exits.
        char buffer[150];
        fp = fopen("readme.txt","a+");      //Opening file in append mode.
        close(pipefd[1]);              //Close the write end of the pipe since it is used here for reading purpose.
        char Line[150];
        int n;
        fprintf(fp,"%s","Parent is Writing:");
        while((n = read(pipefd[0], buffer, sizeof(buffer)-1)) > 0)
        {
            buffer[n] = '\0';
            fprintf(fp,"%s", buffer);
        }
        close(pipefd[0]);       //close both end of the pipe.
        close(pipefd[1]);
        fclose(fp);             //Close file descriptor.
        exit(0);
    }
}
