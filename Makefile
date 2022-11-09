output: test2.o PythonListReplication.o
	gcc ./test2.o ./PythonListReplication.o -o output

test2.o: test2.c
	gcc -c ./test2.c

PythonListReplication.o: ./Lib/PythonListReplication.c ./Lib/PythonListReplication.h
	gcc -c ./Lib/PythonListReplication.c

clean:
	rm *.o output