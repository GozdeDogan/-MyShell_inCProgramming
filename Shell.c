/*************************************************************************************************/
/*	Gozde DOGAN 
/*	131044019
/*	CSE344 - Homework 3
/*	Shell.c
/*	29 Nisan 2018
/*************************************************************************************************/

#include "Shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <dirent.h>     //ls fonksiyonu icin
#include <errno.h>   
#include <sys/stat.h>
# include <unistd.h>

/**************************** FUNCTION DEFINITIONS ****************************/

// 131044019_main.c de execvp ile calistirilir.
// Arguman beklemez.
int main(int argc, char *argv[]){
	int n = 10;
	char command[MAX_PATH_LEN];
	char file[MAX_PATH_LEN];

	FILE *fp = fopen(COMMANDS, "r");
	if(fp != NULL){
		fclose(fp);
		readFromFile();
	}

	/*for (int i = 0; i <= indexCom; ++i)
	{
		fprintf(stderr, "commands[%d]: %s\n", i, commands[i]);
	}*/

	sprintf(root, "%s", getcwd(cwd, sizeof(cwd)));

	/**************************** SINYAL HAZIRLIGI ****************************/
	sa.sa_handler = signalHandler;
    sa.sa_flags = SA_RESTART;
    

    if (sigemptyset(&sa.sa_mask) == -1){
		perror("\tFailed to initialize the signal mask");
		exit(EXIT_FAILURE);
	}

	// SIGINT ve SIGTERM sinyalleri eklendi.
	if(sigaddset(&sa.sa_mask, SIGINT) == -1){
		perror("\tFailed to initialize the signal mask");
		exit(EXIT_FAILURE);
	}

    if(sigaddset(&sa.sa_mask, SIGTERM) == -1){
		perror("\tFailed to initialize the signal mask");
		exit(EXIT_FAILURE);
	}
	/***************************************************************************/

	welcome();

	while(1){
		/**************************** SIGNAL HANDLER ***************************/
		if(sigaction(SIGINT, &sa, NULL) == -1){
   			perror("\tCan't SIGINT");
   			//exit(EXIT_FAILURE);
   		}

   		if(sigaction(SIGTERM, &sa, NULL) == -1){
   			perror("\tCan't SIGTERM");
   			//exit(EXIT_FAILURE);
   		}
   		/***********************************************************************/


		printf("\tmyshell@myshell:~%s$ ", getcwd(cwd, sizeof(cwd)));

		fgets(command, MAX_PATH_LEN, stdin); // girilen command okundu 

		if(command[strlen(command) - 1] == '\n')
			command[strlen(command) - 1] = '\0';
		//fprintf(stderr, "command: %s\n", command);

		doOperation(command); // command'in gerektirdigi islem yapilmak uzere doOperation fonksiyonuna yollandi

		/**************************** SIGNAL HANDLER ***************************/
		if(sigaction(SIGINT, &sa, NULL) == -1){
   			perror("\tCan't SIGINT");
   			//exit(EXIT_FAILURE);
   		}

   		if(sigaction(SIGTERM, &sa, NULL) == -1){
   			perror("\tCan't SIGTERM");
   			//exit(EXIT_FAILURE);
   		}
   		/***********************************************************************/
	}

	_exit(EXIT_SUCCESS);
	// shell'de fork yapilarak cagrildigi icin child olacaktir. Bu nedenle de exit ile cikis yapidi.
	// child oldugu icinde derste belirtildigi sekilde _exit kullanildi.
}

// baslangic ekrani
void welcome(){
	fprintf(stderr, "\n\t###################################################\n");
	fprintf(stderr, "\t               GOZDE DOGAN - 131044019 \n");
	fprintf(stderr, "\t               CSE344 - HOMEWORK 3 \n");
    fprintf(stderr, "\t               WELCOME MY SHELL\n");
    fprintf(stderr, "\t###################################################\n");
    fprintf(stderr, "\n\n");
}

// islem yapan fonsiyon
void doOperation(char command[MAX_PATH_LEN]){
	char commandTemp[MAX_PATH_LEN];
	sprintf(commandTemp, "%s", command);


	indexCom++;
	sprintf(commands[indexCom], "%s", commandTemp);

	char *token = strtok(command, " ");
	char tokenCmd[MAX_PATH_LEN];
	sprintf(tokenCmd, "%s", token);


	if(strcmp(tokenCmd, "ls") == 0){
		ls();
	}	
	else if(strcmp(tokenCmd, "pwd") == 0){
		pwd();
		fprintf(stderr, "\t%s\n", cwd);
	}
	else if(strcmp(tokenCmd, "cd") == 0){
		cd(&commandTemp[3]);
	}
	else if(strcmp(tokenCmd, "help") == 0){
		help();
	}
	else if(strcmp(tokenCmd, "cat") == 0){
		cat(&commandTemp[4]);
	}
	else if(strcmp(tokenCmd, "wc") == 0){
		wc(&commandTemp[3]);
	}
	else if(strcmp(tokenCmd, "history") == 0){
		getCommand(&commandTemp[8]);
	}
	else if(strcmp(tokenCmd, "exit") == 0){
		myExit();
	}
	else{ 
		//input-output redirection & pipe
		int status = 0; // 1 ise >, 2 ise <
		int index = -1;
		char last[MAX_PATH_LEN];

		for(int i = 0; i < strlen(commandTemp); i++){
		    if(commandTemp[i] == '>'){ //output
		    	index = i;
		        status = 1;
		    }
		}

		for(int i = 0; i < strlen(commandTemp); i++){
		    if(commandTemp[i] == '<'){ //input
		    	index = i;
		        status = 2;
		    }
		}

		for(int i = 0; i < strlen(commandTemp); i++){
		    if(commandTemp[i] == '|') //pipe
		        status = 3;
		}

		/*indexCom++;
		sprintf(commands[indexCom], "%s", command);*/

	    if(status == 2){ //input
	    	sprintf(last, "%s", &commandTemp[index]);
	    	inputRedirection(last);
	    }
		else if (status == 1){ //output
	    	sprintf(last, "%s", &commandTemp[index]);
			outputRedirection(last);
		}
		else if (status == 3){ //pipe
			Pipe(commandTemp);
		}
		else
			fprintf(stderr, "\tINVALID COMMAND\n");

	}
}

// "ls" geldiginde fork yapar ve execve ile ls.c calistirilir.
void ls(){
	/*indexCom++;
	sprintf(commands[indexCom], "ls");*/

	char command[MAX_PATH_LEN] = "./ls";

	pid_t pid = fork();
	if(pid == -1)
		fprintf(stderr, "\tfork: ERROR\n");
	if(pid == 0){
		getcwd(cwd, sizeof(cwd));
		arg_execve[0] = "./ls";
		arg_execve[1] = cwd;
		//fprintf(stderr, "arg_execve[1]: %s\n", arg_execve[1]);
		execvp(command, arg_execve);
		_exit(EXIT_SUCCESS);
	}
	else{
		wait(NULL);
	}
}

// current directory'i bulur
void  pwd(){
	/*indexCom++;
	sprintf(commands[indexCom], "pwd");*/
	getcwd(cwd, sizeof(cwd));
}

// gelen directory'e gider
void cd(char directory[MAX_PATH_LEN]){
	//if(strlen(directory) > 0){
		/*indexCom++;
		sprintf(commands[indexCom], "cd %s", directory);*/

		if(strcmp(directory, "..") == 0){
			chdir(root);
		}
		else if(strcmp(directory, ".") == 0){
			getcwd(cwd, sizeof(cwd));

			if(strlen(cwd) > strlen(root)){
				char last[MAX_PATH_LEN];
				char *token;

	  			token = strrchr (cwd, '/');
	  			sprintf(last, "%s", token);

	  			cwd[strlen(cwd) - strlen(last)] = '\0';
	  			//fprintf(stderr, "new cwd: %s\n", cwd);

				chdir(cwd);
			}
		}
		else{
			struct stat fileStat;
			if(stat(directory,&fileStat) < 0) 
				fprintf(stderr, "\tERROROR\n");

			if(S_ISDIR(fileStat.st_mode)){
				char newdir[MAX_PATH_LEN];
				sprintf(newdir, "%s/%s", getcwd(cwd, sizeof(cwd)), directory);
				//fprintf(stderr, "newdir: %s\n", newdir);
				chdir(newdir);
			}
			else{
				fprintf(stderr, "\t%s is not a directory\n", directory);
			}
		}
	/*}
	else{
		fprintf(stderr, "\t Usage cd: cd 'directoryname'\n");
		fprintf(stderr, "\t Usage cd: cd .\n");
		fprintf(stderr, "\t Usage cd: cd ..\n");
	}*/
}

// kullanilabilecek komutlari yazar
void help(){

	/*indexCom++;
	sprintf(commands[indexCom], "help");*/

	fprintf(stderr, "\tSupported Commands:\n");
	fprintf(stderr, "\t  ls\n");
	fprintf(stderr, "\t  pwd\n");
	fprintf(stderr, "\t  cd\n");
	fprintf(stderr, "\t  help\n");
	fprintf(stderr, "\t  cat\n");
	fprintf(stderr, "\t  wc\n");
	fprintf(stderr, "\t  exit\n");
	fprintf(stderr, "\t  CTRL-C\n");
	fprintf(stderr, "\t  SIGTERM\n");
	fprintf(stderr, "\t  Input Redirection \"<\"\n");
	fprintf(stderr, "\t  Output Redirection \">\"\n");
	fprintf(stderr, "\t  Pipe \"|\"\n");
	fprintf(stderr, "\t  command Num (Up Arrow Key)\n");
}


// gelen file dolu ise islem yapar.
// fork yaparak execve ile "cat.c" i calistirir.
void cat(char file[MAX_PATH_LEN]){
	if(strlen(file) > 0){
		/*indexCom++;
		sprintf(commands[indexCom], "cat %s", file);*/

		char command[MAX_PATH_LEN] = "./cat";

		pid_t pid = fork();
		if(pid == -1)
			fprintf(stderr, "\tfork: ERROR\n");
		if(pid == 0){

			arg_execve[0] = "./cat";
			arg_execve[1] = file;

			execvp(command, arg_execve);
			_exit(EXIT_SUCCESS);
		}
		else{
			wait(NULL);
		}	
	}else{
		fprintf(stderr, "\tUsage cat: cat 'filename'\n");
	}
}

// gelen file dolu ise islem yapar.
// fork yaparak execve ile "cat.c" i calistirir.
void wc(char file[MAX_PATH_LEN]){
	if(strlen(file) > 0){
		char command[MAX_PATH_LEN] = "./wc";

		/*indexCom++;
		sprintf(commands[indexCom], "wc %s", file);*/

		pid_t pid = fork();
		if(pid == -1)
			fprintf(stderr, "\tfork: ERROR\n");
		if(pid == 0){
			arg_execve[0] = "./wc";
			arg_execve[1] = file;

			execvp(command, arg_execve);
			_exit(EXIT_SUCCESS);
		}
		else{
			wait(NULL);
		}
	}else{
		fprintf(stderr, "\t Usage wc: wc 'filename'\n");
	}
}

// shell'den cikar.
// cikarken commands string arrayini "commands.txt" dosyasina yazar.
void myExit(){
	/*indexCom++;
	sprintf(commands[indexCom], "exit");*/
	printArrayToFile(commands, indexCom);
	exit(EXIT_SUCCESS);
}

// inputu girilen dosya olarak degistirir.
void inputRedirection(char command[MAX_PATH_LEN]){
	int fd = open(command, O_RDONLY);
    dup2(fd, STDIN_FILENO);
    close(fd);
}

// output'u girilen dosya oalrak degistirir.
void outputRedirection(char command[MAX_PATH_LEN]){

    int fd = open(command, O_RDONLY | O_WRONLY | O_CREAT,S_IRWXU);
    dup2(fd, STDOUT_FILENO);
    close(fd);
}

// gelen command'i '|' a gore parcalar ve args arrayinde tutar.
// args arrayinin eleman sayisini da command'i parcalarken bulur.
// args ve numOfCommands ile commandPipe fonksiyonunu calistirir.
void Pipe(char command[MAX_PATH_LEN]){
	char *args[MAX_PATH_LEN];
	int i = 0;
	char *token;
	int numOfCommands = 0;

	token = strtok(command, "|");

	while(token != NULL){
		sprintf(args[i], "%s", token);
		i++;

		token = strtok(NULL, "|");

		if(token != NULL){
			//sprintf(args[i], "|");
			//i++;
			numOfCommands++;
		}
	}

	args[i] = NULL; // args'in sonuna NULL eklenir, bittigi anlasilsin diye

	commandPipe(args, numOfCommands);
}

void commandPipe(char *args[MAX_PATH_LEN], int numOfCommands){
    // pipe'lar icin
    // '|' ifadesinin sag ve sol kisimlari icin 2 tane pipe var.
    // cift kisimlar icin fd2, tek kisimlar icin fd1 olusturulur.
    // cift kisimlar '|' ifadesinin sol kismi
    // tek kisimlar '|' ifadesinin sag kismi
    int fd1[2]; 
    int fd2[2];

    //char *command[MAX_PATH_LEN];

    pid_t pid;

    int ERROR = -1;
    int endOfArr = 0;

    int i = 0;


    // pipe olsuturuldu
    if (i % 2 != 0){
        pipe(fd1); // i tek ise fd1 pipe'i olusturuldu
    }else{
        pipe(fd2); // i cift ise fd2 pipe'i olusturuldu
    }

    pid=fork();

    if(pid == -1){ // fork olusamadiysa, pipe kapatildi			
        if (i != numOfCommands - 1){
            if (i % 2 != 0){
                close(fd1[1]);
            }else{
                close(fd2[1]); 
            } 
        }			
        fprintf(stderr, "\tPipe couldn't created\n");
        return;
    }
    if(pid == 0){ // child process 
        // ilk command'de ise
        if (i == 0){
            dup2(fd2[1], STDOUT_FILENO);
        }
        else if (i == numOfCommands - 1){ // son command ise ekran'da sonuc gorulur
            if (numOfCommands % 2 != 0){ // odd = tek
                dup2(fd1[0],STDIN_FILENO);
            }else{ // even = cift
                dup2(fd2[0],STDIN_FILENO);
            }
        }else{ // son ve ilk command degilse diger islemler(command'ler) yapilir
            if (i % 2 != 0){ // odd = tek
                dup2(fd2[0],STDIN_FILENO); 
                dup2(fd1[1],STDOUT_FILENO);
            }else{ // even = cift
                dup2(fd1[0],STDIN_FILENO); 
                dup2(fd2[1],STDOUT_FILENO);					
            } 
        }

        // command / icermedigi icin bunu dosya da arar, oyle islem yapar
        // "execvp", 'http://www.belgeler.org/glibc/glibc-Executing-a-File.html' sitesinden arastirildi.
        if (execvp(args[0], args) == ERROR){
            kill(getpid(), SIGTERM);
        }		
    }
    else{
        ///// pipe kapatildi
        if (i == 0){
            close(fd2[1]);
        }
        else if (i == numOfCommands - 1){
            if (numOfCommands % 2 != 0){					
                close(fd1[0]);
            }else{					
                close(fd2[0]);
            }
        }else{
            if (i % 2 != 0){					
                close(fd2[0]);
                close(fd1[1]);
            }else{					
                close(fd1[0]);
                close(fd2[1]);
            }
        }

        waitpid(pid,NULL,0);

        i++;	
	}
}

// "historyn num" komutu gelince calisir.
// girilen num degeri kadar onceki komutu calistirir.
// yani girilen num degerini sondan geriye dogru komut olarak sayar.
void getCommand(char sIndex[2]){
	int index = -1;

	index = atoi(sIndex);
	if(index-1 <= indexCom && indexCom >= 0 && index-1 >= 0){
		getcwd(cwd, sizeof(cwd));
		char command[MAX_PATH_LEN];
		sprintf(command, "%s", commands[indexCom - index + 1]);
		fprintf(stderr, "\t%s %s", cwd, command);

		indexCom++;
		sprintf(commands[indexCom], "%s", command);

		fprintf(stderr, "\n");
		doOperation(command);
	}
	else
		fprintf(stderr, "\tINVALID COMMAND INDEX\n");
}

// comamnds arrayindeki degerleri "commands.txt" dosyasina yazar.
void printArrayToFile(char arr[MAX_PATH_LEN][MAX_PATH_LEN], int size){
	FILE *fp = fopen(COMMANDS, "a+");

	for (int i = 0; i <= size; ++i)
	{
		if(strcmp(commands[i], " ") != 0)
			fprintf(fp, "%s\n", commands[i]);
	}

	fclose(fp);
}

// "commands.txt" dosyasindaki degerleri (son 100 degeri) commands arrayine atar.
void readFromFile(){
	FILE *fp = fopen(COMMANDS, "r");
	indexCom = -1;
	char command[MAX_PATH_LEN];
	int iTemp = 0;
	char ch;
	int startIndex = -1;
	int iNumOfLine = 0;


	// satir sayisini bulur.
	while(!feof(fp)){
		fscanf(fp, "%c", &ch);
		if(ch == '\n'){
			iNumOfLine=iNumOfLine+1;
		}
	}

	rewind(fp);

	while(!feof(fp))
	{
		fgets(command, MAX_PATH_LEN, fp);
		iTemp++;
		if(command[strlen(command) - 1] == '\n')
			command[strlen(command) - 1] = '\0';

		if(strcmp(command, " ") > 0 && iTemp > (iNumOfLine - 50)){
			//fprintf(stderr, "command: %s\n", command);
			indexCom++;
			sprintf(commands[indexCom], "%s", command);
		}
	}

	fclose(fp);
}

void signalHandler(int sig){
	if(sig == SIGINT){
		fprintf(stdout, "\n\n\tCTRL-C SIGNAL CAME\n");
		printArrayToFile(commands, indexCom);
		exit(EXIT_SUCCESS);
	}
	else if(sig == SIGTERM){
		fprintf(stdout, "\n\n\tSIGTERM SIGNAL CAME\n");
		printArrayToFile(commands, indexCom);
		exit(EXIT_SUCCESS);
	}
}

/******************************************************************************/