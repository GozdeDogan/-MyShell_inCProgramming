/******************************************************************************/
/* Gozde DOGAN - 131044019
/* CSE344 - Homework3
/*
/* 131044019_HW3_CSE344
/*
/* 29 Nisan 2018
/*
/* Kisa odev aciklamasi
/*
/******************************************************************************/

Calistirma sekli:
	make
	./131044019_main
	-> ekrana olusturulan shell gelecek ve command girmenizi bekleyecek!


131044019_HW3_CSE344:

	-> 131044019_main.c:	
			Ana program
			'./shell' in execvp ile calistirldigi c dosyasi

	-> Shell.c:
			Butun shell islemlerini gerceklestirildigi dosya.

	-> Shell.h:
			"Shell.c" icin hazirlanan kutuphane.

	-> cat.c:
			Girilen command 'cat file' seklinde ise calisiyor. 
			Arguman oalrak gelen file'in icerigini ekrana yaziyor.

	-> list.c:
			Girilen command 'ls' ise calisiyor.
			Bir arguman almaz, bulunan directory'de bulunan klasor ve file'lari listeler.
			Listeleme:
				filename:
					file type
					file size
					access rights
			seklinde yapilir.

	-> wc.c:
			Girilen command 'wc file' seklinde ise calisiyor.
			Arguman olarak girien file'i aliyor.
			File'daki satir sayisini:
				Lines : NUM
			seklinde ekrana yaziyor.

	-> commands.txt:
			Girilen ve dogru olan butun command'lerin tutuldugu dosya. 
			Program calistirildigi zaman komutlari burdan alir.
			-> 'history NUM' komutu girildiginde NUM. komutu getirir ekrana ve calistirir.

	-> inputFile.txt:
			'cat' ve 'wc' komutlari icin deneme amacli eklenen dosya.

	-> dir: cd'yi denemek icin klasor

	-> makefile:
			"gcc -c list.c
			 gcc list.o -o ls" 

			"gcc -c cat.c
			 gcc cat.o -o cat"


			"gcc -c wc.c
			 gcc wc.o -o wc"


			"gcc -c Shell.c 
			gcc Shell.o -o shell "


			"gcc -c 131044019_main.c
			 gcc 131044019_main.o -o 131044019_main"

			 Yukarida da goruldugu gibi once 'ls', 'cat' ve 'wc' komutlarinin gerceklestirildigi 
			 "list.c", "cat.c" ve "wc.c" dosyalari derleniyor.
			 Ardindan bu komutlarin kontrol edildigi "Shell.c" dosyasi derleniyor.
			 Son olarak da "131044019_main.c" dosyasi derleniyor.

			 Bu sekilde olmasinin sebebi;
			 	"131044019_main.c" de "./shell" calistiriliyor ve bunun icin "Shell.c" dosyasinin 
			 	derlenmis olmasi gerekiyor.
			 	"Shell.c" de "./ls", "./cat 'filename'" ve "./wc 'filename'" islemleri gerceklestiriliyor,
			 	bu islemlerin gerceklestirilebilmesi icinde "list.c", "cat.c" ve "wc.c" dosyalarinin derlenmis 
			 	olmasi gerekiyor.



---------------------------------------------------- ONEMLI ----------------------------------------------------

	-> up arrow key tusu yerinde derste Erchan Hocanin dedigi sekilde "history num" komutu eklendi.
	   up arrow key yerine "$ history 1" seklinde komut girmelisiniz.

    -> "make
    	./131044019_main"
    	seklinde derleme islemi gerceklestirildikten sonra ekran asagidaki sekilde olacaktir;

    	#################################################
    			    GOZDE DOGAN - 131044019	
    				CSE344 - HOMEWORK 3	
	    	        WELCOME MY SHELL
		#################################################


		myshell@myshell:~/home/gtusvy/Desktop/131044019_HW3_CSE344$

		Burda komut girmeniz beklenecektir. Komutlar asagidaki sekilde beklenmektedir;
			-> ls
			-> help
			-> cat 'filename'
			-> wc 'filename'
			-> cd .
			-> cd ..
			-> cd 'directoryname'
			-> pwd
			-> exit
			-> history 'NUM'


		-> "exit" yazmadan veya "CTRL-C" gelmeden bu shell'den cikis mumkun olmayacaktir.

		-> "cd 'directoryname'" denildiginde; bulunan klasor icinde oyle bir directory varsa gecis yapar yoksa
			yeni komut bekler;
			"myshell@myshell:~/home/gtusvy/Desktop/131044019_HW3_CSE344$"

		-> "cd ." denildiginde; bir onceki directory'e doner ama root 
			("myshell@myshell:~/home/gtusvy/Desktop/131044019_HW3_CSE344$") 'u gecmez.

		-> "cd .." denildiginde; root ("myshell@myshell:~/home/gtusvy/Desktop/131044019_HW3_CSE344$") 'a doner.

		-> "cat" denildiginde; "Usage cat: cat 'filename'" seklinde kullanim sekli gosterilir. Tekrar komut beklenir.

		-> "wc" denildiginde; "Usage wc: wc 'filename'" seklinde kullanim sekli gosterilir. Tekrar komut beklenir.

		-> Komutlar beklenen sekilde girilmezde "INVALID COMMAND" diyerek yeni komut bekler!


		------>>>>> ODEV VERILEN ISLETIM SİSTEMİ "DEBIAN" DA CALISTIRILMISTIR VE MEMORY LEAK YA DA ERROR İLE 
					KARSILASILMAMISTIR.

-----------------------------------------------------------------------------------------------------------------