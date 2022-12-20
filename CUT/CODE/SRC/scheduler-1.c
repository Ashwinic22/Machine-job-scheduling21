#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100
// define the structure for job
typedef struct
{
    char jobNo[10];
    char description[20];
    char machineNo[10];
    int duration;
    char clientName[30];
} job;

// define the structure for schedule
typedef struct
{
    char jobNo[10];
    char machineNo[10];
    int start;
    int end;
} schedule;

// define the structure for jobSchedule
typedef struct
{
    char jobNo[10];
    char description[20];
    char machineNo[10];
    int duration;
    char clientName[30];
    int start;
    int end;
} jobSchedule;

// define structure to hold jobSchedules for each machine
typedef struct
{
    int machineNo;
    jobSchedule jobScheduleList[MAX];
    int jobScheduleCount;
} machineSchedule;

// read file and add it to joblist
void readFile(job *jobList, int *jobCount, char *fileName)
{
    FILE *fp;
    fp = fopen(fileName, "r");
    char line[100];
    int i = 0;
    while (fgets(line, 100, fp) != NULL)
    {
        char *token = strtok(line, ":");
        strcpy(jobList[i].jobNo, token);
        token = strtok(NULL, ":");
        strcpy(jobList[i].description, token);
        token = strtok(NULL, ":");
        strcpy(jobList[i].machineNo, token);
        token = strtok(NULL, ":");
        jobList[i].duration = atoi(token);
        token = strtok(NULL, ":");
        strcpy(jobList[i].clientName, token);
        i++;
    }
    *jobCount = i;
    fclose(fp);
}

// find invalid jobs and write them to invalidJobs and display them
void findDisplayAndRemoveInvalidJobs(
    job *jobList,
    int *jobCount,
    char *invalidJobsFileName)
{
    FILE *fp;
    fp = fopen(invalidJobsFileName, "w");
    int i;
    for (i = 0; i < *jobCount; i++)
    {
        // when job no is lessthen 4
        // when description is empty
        // when machine no is lessthen 2
        // when duration is lessthen 1
        // when client name is empty
        // the job is invalid
        if (strlen(jobList[i].jobNo) != 4 ||
            strlen(jobList[i].description) < 1 ||
            strlen(jobList[i].machineNo) != 2 ||
            jobList[i].duration < 1 ||
            strlen(jobList[i].clientName) < 1)
        {
            printf("Invalid job entry: %s\n", jobList[i].jobNo);
            fprintf(fp, "Invalid job entry: %s", jobList[i].jobNo);
            int j;
            for (j = i; j < *jobCount - 1; j++)
            {
                jobList[j] = jobList[j + 1];
            }
            *jobCount = *jobCount - 1;
            i--;
        }
    }
    fclose(fp);
}

// schedule Jobs
void scheduleJob(
    job *jobList,
    int jobCount,
    schedule *scheduleList,
    int *scheduleCount)
{
    int i;
    int time1=1,time2=1,time3=1;
    for (i = 0; i < jobCount; i++)
    {
	if (strcmp(jobList[i].machineNo, "m1")==0)
	{
		scheduleList[i].start = time1;
                scheduleList[i].end = time1 + jobList[i].duration - 1;
		time1 = time1 + jobList[i].duration;
	}
	else if(strcmp(jobList[i].machineNo, "m2")==0)
	{
		scheduleList[i].start = time2;
		scheduleList[i].end = time2 + jobList[i].duration - 1;
		time2 = time2 + jobList[i].duration;
	}
	else if(strcmp(jobList[i].machineNo, "m3")==0)
	{
		 scheduleList[i].start = time3;
		 scheduleList[i].end = time3 + jobList[i].duration - 1;
		 time3 = time3 + jobList[i].duration;
	}
	strcpy(scheduleList[i].jobNo, jobList[i].jobNo);
	strcpy(scheduleList[i].machineNo, jobList[i].machineNo);	
    }
    *scheduleCount = i;
}

// group scheduleList based on machines
void groupScheduleList(
    schedule *scheduleList,
    int scheduleCount,
    machineSchedule *machineScheduleList,
    int *machineScheduleCount)
{
    int i=0, j=0;
    int machineNo=0;
    // loop though for each schedule
    for (i = 0; i < scheduleCount; i++)
    {
        machineNo = atoi(scheduleList[i].machineNo + 1);
        for (j = 0; j < *machineScheduleCount; j++)
        {
            if (machineScheduleList[j].machineNo == machineNo)
            {
                break;
            }
        }
        if (j == *machineScheduleCount)
        {
            machineScheduleList[j].machineNo = machineNo;
            *machineScheduleCount = *machineScheduleCount + 1;
        }
        machineScheduleList[j].jobScheduleList[machineScheduleList[j].jobScheduleCount].start = scheduleList[i].start;
        machineScheduleList[j].jobScheduleList[machineScheduleList[j].jobScheduleCount].end = scheduleList[i].end;
        strcpy(machineScheduleList[j].jobScheduleList[machineScheduleList[j].jobScheduleCount].jobNo, scheduleList[i].jobNo);
        machineScheduleList[j].jobScheduleCount = machineScheduleList[j].jobScheduleCount + 1;
    }
}

// write schedule from groupScheduleList
void writeSchedule(
    machineSchedule *machineScheduleList,
    int machineScheduleCount)
{
    FILE *fp;
    int i;
    for (i = 0; i < machineScheduleCount; i++)
    {
        char fileName[20];
        sprintf(fileName, "schedule%d.txt", machineScheduleList[i].machineNo);
        fp = fopen(fileName, "w");
        fprintf(fp, "- Schedule for machine %d\n", machineScheduleList[i].machineNo);
        int j;
        for (j = 0; j < machineScheduleList[i].jobScheduleCount; j++)
        {
            fprintf(fp, "%s:%d:%d\n", machineScheduleList[i].jobScheduleList[j].jobNo, machineScheduleList[i].jobScheduleList[j].start, machineScheduleList[i].jobScheduleList[j].end);
        }
        fclose(fp);
    }
}

int main(int argc, char *argv[])
{
    // initialize the job list size with max
    job jobList[MAX]= { 0 };
    int jobCount=0;
    int i=0;
    for (i = 1; i < argc; i++)
    {
        // read each command line arg
        readFile(jobList, &jobCount, argv[i]);
    }
    // find invalid jobs and write them to invalidJobs and display them
    findDisplayAndRemoveInvalidJobs(jobList, &jobCount, "invalidJobs.txt");
    // initialize schedule list
    schedule scheduleList[MAX]= {0};
    // initialize schedule count
    int scheduleCount=0;
    // schedule Jobs
    scheduleJob(jobList, jobCount, scheduleList, &scheduleCount);
    // group scheduleList based on machines
    machineSchedule machineScheduleList[MAX] = {0};
    // initialize machineScheduleCount
    int machineScheduleCount = 0;
    groupScheduleList(scheduleList, scheduleCount, machineScheduleList, &machineScheduleCount);
    // write schedule from groupScheduleList
    writeSchedule(machineScheduleList, machineScheduleCount);
    return 0;
}
