SRCDIR     = ../SRC
INCLUDEDIR = ../HEADER
DATADIR    = ../DATA
OBJDIR     = ../OBJ
BINDIR	   = ../BIN
REPORTDIR  = ../../TOOLREPORT

jobScheduler:scheduler-1.o
	gcc -o ${BINDIR}/jobScheduler ${OBJDIR}/scheduler-1.o
scheduler-1.o:../SRC/scheduler-1.c 
	gcc -o ${OBJDIR}/scheduler-1.o -c ${SRCDIR}/scheduler-1.c

memcheck:
	valgrind -s --log-file="${REPORTDIR}/VALGRIND/valgrindReport.txt" ./${BINDIR}/jobScheduler ${DATADIR}/jobs-1.txt 
        
errorcheck:
	splint ${SRCDIR}/*.c -I ${INCLUDEDIR} > ${REPORTDIR}/SPLINT/errorcheck.txt
      
clean:
	rm ${BINDIR}/jobScheduler ${OBJDIR}/scheduler-1.o ${REPORTDIR}/VALGRIND/valgrindReport.txt ${REPORTDIR}/SPLINT/errorcheck.txt

