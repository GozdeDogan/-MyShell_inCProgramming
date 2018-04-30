all:
	clear 
	
	gcc -c list.c
	gcc list.o -o ls 

	gcc -c cat.c
	gcc cat.o -o cat


	gcc -c wc.c
	gcc wc.o -o wc


	gcc -c Shell.c 
	gcc Shell.o -o shell 


	gcc -c 131044019_main.c
	gcc 131044019_main.o -o 131044019_main


clean:
	rm *.o ls
	rm *.o cat
	rm *.o wc
	rm *.o shell
	rm *.o 131044019_main