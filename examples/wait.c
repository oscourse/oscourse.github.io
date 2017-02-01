#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int ret = 0;
    int status = 0;
    if ((pid = fork()) == 0) {
         /* in the child  exec another program image */
         ret = execlp("ls", "ls", NULL);
         if( ret == -1 )
         {   
           fprintf(stderr, "exec failed\n"); 
         }   
     }   
   else {
   /* in the parent -you can  do some other stuff */ 
   //code for some other stuff
   /* now check for completion of child */
   waitpid(pid, &status, 0); 
   /* Alternative ==> while (wait(&status) != pid); */
    }   
}

