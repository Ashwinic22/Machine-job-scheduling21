CODE = ../SRC
CODE = ../DATA
CODE = ../HEADER
CODE = ../OBJ
CODE = ../BIN
CUT  = ../TOOLREPORT

jobScheduler:scheduler-1.o
	gcc -o ../BIN/jobScheduler ../OBJ/scheduler-1.o
scheduler-1.o:../SRC/scheduler-1.c 
	gcc -o ../OBJ/scheduler-1.o -c ../SRC/scheduler-1.c

memcheck:
	valgrind scheduler-1.o 2>memcheck.txt
        
errorcheck:
	splint scheduler-1.c > errorcheck.txt
      
clean:
	rm ../BIN/jobScheduler ../OBJ/scheduler-1.o

