#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
int setenv(const char *name, const char *value, int overwrite);
int unsetenv(const char *name);
#define BUFSIZE 250

char *read_line(void){
	int i = 0;
	char *buffer = malloc(sizeof(char) * BUFSIZE);
	int c;

	if (!buffer) {
		printf("Allocation error\n");
		exit(1);
	}
	printf("\n? ");
	do {
		// Read input character
		c = getchar();
		if (c == '\n' || c==EOF) {
			buffer[i] = '\0';
			return buffer;
		} else {
			buffer[i] = c;
		}
		i++;
    // If we have exceeded the buffer, exit.
		if (i >= BUFSIZE) {
			printf("Exceeded input limit");
			exit(1);
		}	
	} 	while (c!=EOF);
	return buffer;
}
int sh_exec(char *cmds[]){
	pid_t pid;
	int stat;
	char *buff;
	if (strcmp(cmds[0],"cd")==0){ //could also use chdir()
		//pid = fork();
		if (cmds[1]==NULL || strcmp(cmds[1],"~")==0){//go home
			buff = getenv("HOME");
			cmds[1]=buff;
		//	if (pid>0){
		//		printf("New PID: %d\n", pid);
				chdir(buff);			
		//	}
		//	else if(pid<0){
		//		printf("Error at fork() cd");
		//	}
		}
		else {//change dir according to user's input
		//	if (pid>0){
		//		printf("New PID: %d\n", pid);
				chdir(cmds[1]);
			}
		//	else if(pid<0){
		//		printf("Error at fork() cd");
	
		//waitpid(pid, &stat, 0);
		//exit(0);
		return 1;
	}
	
	else if (strcmp(cmds[0],"pwd")==0){
		//pid = fork();
		char *buff;
		char *ptr = getcwd(buff, BUFSIZE);
		printf("%s", ptr);
		
		//cmds[2] = NULL;
		//if (pid>0){
		//	printf("New PID: %d\n", pid);
		//execvp(cmds[0],cmds);
		//}
		//else if(pid<0){
		//		printf("Error at fork() cd");
		//}
		//waitpid(pid, &stat, 0);
		//exit(0); //terminate child
		return 1; //parent return to main()
	}
	
	else if (strcmp(cmds[0],"exit")==0){
		printf("SHELL EXITS\n");
		exit(0);
		exit(0);
		exit(0);
		return 0;
	}
	
	else if (strcmp(cmds[0],"help")==0){
		//pid = fork();
		//waitpid(pid, &stat, 0);
		//if (pid>0){
		//	printf("New PID: %d\n", pid);
		printf("\ncd [dir] - change DIR. If no DIR, go HOME.\n");
		printf("pwd - display current DIR.\n");
		printf("set var [value] - set/change VALUE.\n");
		printf("unset var [value] - unset VALUE.\n");
		printf("exit - exit shell.\n");
		execvp(cmds[0],cmds);
		//}
		//else if(pid<0){
		//		printf("Error at fork() cd");
		//}
		//waitpid(pid, &stat, 0);
		//exit(0);
		return 1;
	}
	
	else if (strcmp(cmds[0],"set")==0){
		//pid = fork();
		//if (pid>0){
		//	printf("New PID: %d\n", pid);
			setenv(cmds[1],cmds[2],1);
		//}
		//else if(pid<0){
		//		printf("Error at fork() cd");
		//}
		//waitpid(pid, &stat, 0);
		//exit(0);
		return 1;
	}
	else if (strcmp(cmds[0],"unset")==0){
		//pid = fork();
		//if (pid>0){
			//printf("New PID: %d\n", pid);
			unsetenv(cmds[2]);
		//}
		//else if(pid<0){
		//		printf("Error at fork() cd");
		//}
		//waitpid(pid, &stat, 0);
		//exit(0);
		return 1;	
	}
	else {
		printf("Not built-in command\n");
		pid = fork();
		if (pid>0){
			printf("New PID: %d\n", pid);
			execvp(cmds[0],cmds);
		}
		printf("Done\n");
		waitpid(pid, &stat, 0);
		return 1;
	}	
	return 1;
}

int main (int argc, char *argv[]){
/*	//read rc file content
	FILE *rc_file = fopen(argv[0],"r");
	int c;
	//char* token;
	int i=0;
	char *buffer = malloc(sizeof(char) * BUFSIZE);
	char* file_line[BUFSIZE];
	int status;
	if(rc_file!=NULL){
		while(c!=EOF && i<BUFSIZE){ //watch end of file, terminate if limit reached
			c=fgetc(rc_file);
			buffer[i] = c;
			//printf("%c",buffer[i]);
			if (i==BUFSIZE){
				printf("Input limit reached");
				exit(1);
			}
			else {
				i++;	
			}
		}
	}
	fclose(rc_file);
	//file_line[i] = strtok(buffer," \n");
	do{
		i=0;
		file_line[i] = strtok(buffer," \n");
		printf("File line: %s\n",file_line[i]);
		while (file_line[i] != NULL) {
			if (i==BUFSIZE){
				printf("Exceeded input limit");
				exit(1);
			}
			file_line[i+1] = strtok(NULL, " \n");
			printf("File line: %s\n",file_line[i]);
			i++;
		}
		file_line[i] = NULL;
		status = sh_exec(file_line);
		
	} while(status!=0 );
	free(buffer);
*/	
	//execute manual user commands
	//char str[2];
	printf("\nEnable manual user input/n");
	//scanf(" %s", str);
	int i;
	int status;
	//if (strcmp(str,"y")==0){
		//printf("Input ON");
		//tokenize user input
		char *line;
		char *cmds[BUFSIZE];//arg vector of user input line
		do {
			line = read_line();
			i = 0;
			cmds[i] = strtok(line, " \n");
			while (cmds[i] != NULL) {
				if (i>=BUFSIZE-1){
					printf("Exceeded input limit");
					exit(1);
				}
			cmds[i+1] = strtok(NULL, " \n");
			i++;
			}
			cmds[i] = NULL;
			status = sh_exec(cmds);
		} while(status);
		free(line);
	//}
	//else {
	//	printf("Input OFF");
	//}
	return 0;
}