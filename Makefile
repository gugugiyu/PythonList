output: test.o PythonListReplication.o
	gcc ./test.o ./PythonListReplication.o -o output

test.o: test.c
	gcc -c ./test.c

PythonListReplication.o: ./Lib/PythonListReplication.c ./Lib/PythonListReplication.h
	gcc -c ./Lib/PythonListReplication.c

clean:
	rm *.o output