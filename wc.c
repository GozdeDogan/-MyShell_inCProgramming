/*************************************************************************************************/
/*	Gozde DOGAN 
/*	131044019
/*	CSE344 - Homework 3
/*	wc.c
/*	29 Nisan 2018
/*************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <dirent.h> 
#include <errno.h>   
#include <sys/stat.h>

#define MAX_PATH_LEN 1024
#define DEBUG


void wc(char file[MAX_PATH_LEN]);

// Shell.c de execvp ile calistirilir.
// Arguman olarak dosya adi gelmesini bekler.
int main(int argc, char *argv[]){
	wc(argv[1]); 
	_exit(EXIT_SUCCESS); 
	// shell'de fork yapilarak cagrildigi icin child olacaktir. Bu nedenle de exit ile cikis yapidi.
}

// Arguman olarak gelen dosyaya girer, okur ve ekrana yazar.
void wc(char file[MAX_PATH_LEN]){
	FILE *fp;
	char ch;
	int linecount, wordcount, charcount;

	linecount = 0;
	wordcount = 0;
	charcount = 0;

	fp = fopen(file,"r");
	if(fp == NULL){
		fprintf(stderr, "\t%s couldn't open!\n", file);
	}
	else {
		if ( fp == NULL ){
			fprintf(stderr, "Failed to open the file\n");
		}
		else
		{
			while ((ch=getc(fp)) != EOF) {
				if (ch != ' ' && ch != '\n')
					++charcount;

				if (ch == ' ' || ch == '\n')
					++wordcount;

				if (ch == '\n')
					++linecount;
			}

			if (charcount > 0) {
				++linecount;
				++wordcount;
			}
		}

		fprintf(stderr, "\tLines : %d \n", linecount);
		//printf("\tWords : %d \n", wordcount);
		//printf("Characters : %d \n", charcount);
	}
}