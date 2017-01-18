#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void myprint(int pid, int space)
{
	int i;
	printf("%d: ", pid);
	for(i=0; i<space; i++)
		printf("   ");

}

int main(int argc, char *argv[])
{
	pid_t pid, ppid;
	int H, C, i, space, status;
	char spacestr[10], heightstr[10];

	pid = getpid();
	ppid = getppid();

	if( argc < 3 ) {
		printf("%d: Usage %s <H> <C>\n", pid, argv[0]);
		exit(1);
	}

	H = atoi(argv[1]);
	C = atoi(argv[2]);
	if( argc == 4 )
		space = atoi(argv[3]);
	else 
		space = 0;

	myprint(pid,space);printf("Process starting\n");
	myprint(pid,space);printf("Parent's ID = %d\n", ppid);
	myprint(pid,space);printf("Height in the tree = %d\n", H);


	if ( H <=1 ) 
		goto out;

	myprint(pid,space);printf("Creating %d children at height %d\n", C, H-1);

	for( i=0; i<C; i++) {
		int cpid;
		if ( (cpid = fork()) < 0) {
			myprint(pid,space);printf("Error forking child %d\n", i);
			exit(3);
		}
		
		if( cpid == 0 ) {
			// put child's code here
			myprint(getpid(),space+1);printf("This is child %d\n", i);

			sprintf(heightstr, "%d", H-1);
			sprintf(spacestr, "%d", space+1);
			execlp(argv[0], argv[0], heightstr, argv[2], spacestr, (char *)NULL);	

			myprint(getpid(),space+1);printf("Error doing exec in child %d\n", i);
			exit(4);
		}

		//myprint(pid,space);printf("Created child %d with pid %d\n", i, cpid);
	}

	for( i=0; i<C; i++) {
		int c = wait(&status);
		myprint(pid,space);printf("Child %d terminated with status %d\n", c, status);
	}

out:
	myprint(pid,space);printf("Terminating at height %d\n", H);

	return 0;
}

