binary: server.o libworld.so
	gcc -o binary server.o -L. -lworld -Wl,-rpath,.

server.o: server.c
	gcc -c server.c

libworld.so: rem.o
	gcc -shared -o libworld.so rem.o

rem.o: rem.c
	gcc -c -fPIC rem.c

clean:
	rm -f *.o *.so binary