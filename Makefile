CC=gcc

output: test.o test2.o PythonListReplication.o ./Lib/PythonTupleReplication.o
	$(CC) ./test.o ./PythonListReplication.o ./Lib/PythonTupleReplication.o -o output
	$(CC) ./test2.o ./PythonListReplication.o ./Lib/PythonTupleReplication.o -o output2

test.o: ./unitTest/test.c
	$(CC) -c ./unitTest/test.c

test2.o: ./unitTest/test2.c
	$(CC) -c ./unitTest/test2.c

# List library
PythonListReplication.o: ./Lib/PythonListReplication.c ./Lib/PythonListReplication.h
	$(CC) -c ./Lib/PythonListReplication.c

# Tuple library

PythonTupleReplication.o: ./Lib/PythonTupleReplication.c ./Lib/PythonTupleReplication.h
	$(CC) -c ./Lib/PythonTupleReplication.c

clean:
	rm *.o *.exe *.exe.stackdump