/*************************************************************************************************/
/*	Gozde DOGAN 
/*	131044019
/*	CSE344 - Homework 3
/*	list.c
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

#define MAX_PATH_LEN 1024
#define DEBUG


void ls();   
void printFileFeatures(char fileName[MAX_PATH_LEN]); // gelen dosyanin ozelliklerini ekrana yazar.

// Shell.c de execvp ile calistirilir.
// Arguman beklemez
int main(int argc, char *argv[]){
	ls(argv[1]);
	_exit(EXIT_SUCCESS);
	// shell'de fork yapilarak cagrildigi icin child olacaktir. Bu nedenle de exit ile cikis yapidi.
	// child oldugu icinde derste belirtildigi sekilde _exit kullanildi.
}

// bulunan klasor de yer alan butun klasor ve dosyalari listeler.
void ls(char cwd[MAX_PATH_LEN]){

	fprintf(stderr, "current directory: %s\n", cwd);

	DIR *dir;
	pid_t pid;
    struct dirent *dosya;																	
	struct stat status;  //Degisen fname ile birlikte status durumunu alir ve S_ISDIR fonksiyonunda kullanir

	//Variables
	int index=0, status1=0;
	char fname[MAX_PATH_LEN]; //dosyanin adini tutar
	char name[MAX_PATH_LEN]; //dosyanin adini tutar(/ oncesi dahil degil)
	int iWordCount=0; //toplam string sayisi
	int iWords=0;
   
    //Directory açilabiliyor mu kontrolu yaptim
    if ((dir = opendir(cwd)) == NULL) {
		perror("opendir");
		exit(1);
	}
	while ((dosya = readdir(dir)) != NULL) 
	{	
	    //Dosya adi "." veya ".." olmadiginda islem yapilacak.
		if ((strcmp(dosya->d_name, ".") != 0) && (strcmp(dosya->d_name, "..") != 0 )) 
		{     
			sprintf(fname, "%s/%s", cwd, dosya->d_name); //dosya ismini fname'e attim
			sprintf(name, "%s", dosya->d_name); // ozelliklerin yazilacagi fonksiyona yollanir

			index=strlen(fname);
			/*if( fname[index-1] != '~'  ) // '~' barindiran dosyalar listelenmez!
			{   */
			    #ifndef DEBUG
				    puts(fname);
			    #endif
				if (stat(fname, &status) == -1) 
				{                            
					perror("stat");                                  
					break;
				}

                #ifndef DEBUG
		            printf("pid:%d\n", getpid()); 
		        #endif

                printFileFeatures(name);
               																									
			//}	
		}
	}
	closedir(dir);
}    

void printFileFeatures(char fileName[MAX_PATH_LEN]){
	struct stat fileStat; // ozelliklere erisebilmek icin stat kullanildi.

	if(stat(fileName, &fileStat) < 0) 
		fprintf(stderr, "ERROR\n");
	

	fprintf(stderr, "\t%s\n", fileName); 

    printf("\t\tType: ");
	if (S_ISREG(fileStat.st_mode))
        printf("regular\n");
    else if (S_ISDIR(fileStat.st_mode))
        printf("directory\n");

    fprintf(stderr, "\t\tSize: %d bytes\n",fileStat.st_size);

    printf("\t\taccess_rights: ");
	printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
	printf("\n");
}