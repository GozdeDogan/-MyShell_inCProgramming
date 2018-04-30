/*************************************************************************************************/
/*	Gozde DOGAN 
/*	131044019
/*	CSE344 - Homework 3
/*	Shell.h
/*	29 Nisan 2018
/*************************************************************************************************/

#ifndef H_SHELL
#define H_SHELL


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <dirent.h>     //ls fonksiyonu icin
#include <errno.h>   
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define MAX_PATH_LEN 1024
#define DEBUG
#define COMMANDS "commands.txt"
#define SIZE_COMMANDS 1024

char commands[SIZE_COMMANDS][MAX_PATH_LEN];
int indexCom = -1;

char cwd[MAX_PATH_LEN];
char root[MAX_PATH_LEN];

char *arg_execve[2];
char execCommand[MAX_PATH_LEN];

struct sigaction sa;			/* SIGINT ve SIGTERM sinyali icin tutulan struct */


/**************************** FUNCTION PROTOTYPES ****************************/
void welcome();
void doOperation(char command[MAX_PATH_LEN]);
void ls();
void printFileFeatures(char fileName[MAX_PATH_LEN]);
void pwd();
void cd(char directory[MAX_PATH_LEN]);
void help();
void cat(char file[MAX_PATH_LEN]);
void wc(char file[MAX_PATH_LEN]);
void myExit();
void inputRedirection(char command[MAX_PATH_LEN]);
void outputRedirection(char command[MAX_PATH_LEN]);
void Pipe(char command[MAX_PATH_LEN]);
void commandPipe(char *args[MAX_PATH_LEN], int numOfCommands);
void getCommand(char sIndex[3]);
void signalHandler(int sig);
void printArrayToFile(char arr[MAX_PATH_LEN][MAX_PATH_LEN], int size);
void readFromFile();
/******************************************************************************/

#endif