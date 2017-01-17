default:	life	

life:	life.c
	gcc -o life life.c -Wall -Werror -ggdb

clean:	
	rm a.out life
