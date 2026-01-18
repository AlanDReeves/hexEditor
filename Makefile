hexEdit: hexEdit.o
	gcc hexEdit.o -o hexEdit

hexEdit.o: hexEdit.c
	gcc -fPIC -c hexEdit.c -o hexEdit.o
