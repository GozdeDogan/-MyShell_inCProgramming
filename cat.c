/*************************************************************************************************/
/*	Gozde DOGAN 
/*	131044019
/*	CSE344 - Homework 3
/*	cat.c
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

char cwd[MAX_PATH_LEN];


void cat();
void findLengthLineAndNumOFline(FILE *fPtrInFile, int *n, int *m); //dosyanin satir ve sutun sayisini bulur.
void allocate2DArr(char **arr, int n, int m); // string'e dosyanin satir ve sutun sayisi kadar yer alir.
void free2DArr(char **arr, int n); // alinan yer islem bitince free edilir.

// Shell.c de execvp ile calistirilir.
// Arguman olarak dosya adi gelmesini bekler.
int main(int argc, char *argv[]){
	cat(argv[1]);
	_exit(EXIT_SUCCESS);
	// shell'de fork yapilarak cagrildigi icin child olacaktir. Bu nedenle de exit ile cikis yapidi.
	// child oldugu icinde derste belirtildigi sekilde _exit kullanildi.
}

void cat(char file[MAX_PATH_LEN]){
	FILE *fp;
	char **fileDatas;


	fp = fopen(file, "r");

	if(fp == NULL){
		fprintf(stderr, "\t%s couldn't open!\n", file);
		//exit(EXIT_FAILURE);
	}
	else{
		int n, m;

		findLengthLineAndNumOFline(fp, &n, &m); // dosyanin boyutlari bulundu.

		// bulunan boyutlara gore string arrayine yer alindi.
		if(n != 0 && m != 0){
			fileDatas = (char **)calloc(n, sizeof(char *));
			for (int i = 0; i < n; ++i)
			{
				fileDatas[i] = (char *)calloc(m, sizeof(char));
			}

			rewind(fp);

			// string arrayi dolduruldu
			int i=0;
		    do{ //Dosyayi okuyup string arrayine yazdim
		    
		        fgets(fileDatas[i], m, fp); //dosya '\n' degerleri ile okunuyor!

		        #ifndef DEBUG
		            printf("*-%s-*\n", fileDatas[i]);
		        #endif
		        i++;
		    }while(!feof(fp) && i < n);

		    // doldurulan string arrayi ekrana yazildi.
		    for (int i = 0; i < n; ++i)
		    {
	    		fprintf(stderr, "\t%s", fileDatas[i]); // dosya okunurken '\n' degerleri ile okundugu icin '\n' yazilmadi

		    }
		}
		else{ // dosya bossa bos oldugu yazildi.
			fprintf(stderr, "\tFile is empty\n");
		}

		// string icin alinan yer free edildi.
		free2DArr(fileDatas, n);

		fclose(fp);
	}

}

/**
    Dosyadaki satir sayisini ve en uzun sutundaki karakter sayisini bulur.
    Burdan gelen sonuclara gore dynamic allocation yapilir.
*/
void findLengthLineAndNumOFline(FILE *fPtrInFile, int *n, int *m){
	int iLenghtLine = 0;
	int iMaxSize = 0;
	int iNumOfLine = 0;
	char ch;



		while(!feof(fPtrInFile)){
			fscanf(fPtrInFile, "%c", &ch);
			iMaxSize++;
				if(ch == '\n'){
					iNumOfLine=iNumOfLine+1;
					if(iMaxSize >=(iLenghtLine))
						iLenghtLine=iMaxSize;
					iMaxSize=0;
				}
		}
		//iNumOfLine-=1; //bir azalttim cunku dongu bir defa fazla donuyor ve iNumOfLine
                        //bir fazla bulunuyor.
        iLenghtLine+=1;

        #ifndef DEBUG
            printf("iLenghtLine:%d\tiNumOfLine:%d\n", iLenghtLine, iNumOfLine);
        #endif

        *n = iNumOfLine;
        *m = iLenghtLine;
}

void allocate2DArr(char **arr, int n, int m){
	arr = (char **)calloc(n, sizeof(char *));
	for (int i = 0; i < n; ++i)
	{
		arr[i] = (char *)calloc(m, sizeof(char));
	}
}

void free2DArr(char **arr, int n){
	for (int i = 0; i < n; ++i)
	{
		free(arr[i]);
	}

	free(arr);
}