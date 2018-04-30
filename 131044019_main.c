/*************************************************************************************************/
/*	Gozde DOGAN 
/*	131044019
/*	CSE344 - Homework 3
/*	131044019_main.c
/*	29 Nisan 2018
/*************************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <dirent.h>     //ls fonksiyonu icin
#include <errno.h>   
#include <sys/stat.h>
#include <unistd.h>   //execve

#define MAX_PATH_LEN 1024
#define DEBUG

int main(int argc, char* argv[]){
	if(argc != 1){
		fprintf(stderr, "----------------- USAGE -----------------\n");
		fprintf(stderr, "\t./131044019_main\n");
		return 0;
	}

	pid_t pid = fork();

	if(pid == -1)
		exit(EXIT_FAILURE);

	if (pid == 0){
		execve("./shell", NULL, NULL);  /* './shell' calistirildi. Hicbir input almadi */
		_exit(EXIT_SUCCESS);
	}
	else{
		wait(NULL);
	}
	return 0;
} 
