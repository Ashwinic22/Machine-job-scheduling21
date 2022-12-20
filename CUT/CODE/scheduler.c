// In a particular factory there are 3 machines which can perform multiple jobs.
// The exact jobs to be performed are made available in many files. The exact
// information to be performed are made available to the operator in different
// files. The moment a job has been allocated to a machine, its time will be
// advanced by certain duration.
// The jobs performed successfully are to be put in files and those jobs which
// could not be processed will be recorded in an invalid files.

// Following is the list of functional requirements
// 1. A company has 3 machines and multiple jobs to be done using these machines. Application has to prepare schedule for machines.
// 3. Format of Job description files
// Job No: Description: Machine No :Duration(in minutes):Client name (optional)
// Example job entries
// J001:Pipe bending:M1:45:Expert Accessories
// J002:Surface cleaning: M2:30:Nice parts makers
// J001:Pipe bending: M2:60:Expert Accessories.

// 4. 3 Machines are resources to be shared among jobs. All machines  start at time T1. Whenever a machine is allocated to a job its time will advanced by "Duration" and an entry will be written in "Schedule"
// Schedule entries format
// Job No:Start time: End time
// Example schedule entries for jobs specified in requirement "3" above.
// - Schedule for machine 1
// J001:1:45
// Schedule for machine 2
// J002:1:30
// Schedule for machine 3
// J001:31:91.
// 5. All jobs files should be processed as specified in requirement "4" above.
// 6. At the end, schedule ot each machines to be displayed and stored in schedule1.txt, schedule2. txt and schedule3. txt files.
// 7. Invalid Jobs entries from all input files should be written to invalidJobs. txt file. Display error messages for invalid entries and those should be discarded.
// 8. Read date and start time from user - display schedule in date and time format

// Things to do
// 1. All entries across the entire application should be validated properly.
// 2. Use the appropriate data-structures for all processes.
// 3. Dynamic memory should be used through-out.
// 4. Only binary files should be used for data storage.
// 5. Ensure that no memory leak is there throughout the application.
// 6. Instead of frequent file I/0 carry out all operations in memory and do
// the Reading writing to and from file only once at the beginning and end.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100

typedef struct
{
    char jobNo[10];
    char description[20];
    char machineNo[10];
    int duration;
    char clientName[30];
} job;

typedef struct
{
    char jobNo[10];
    int start;
    int end;
} schedule;

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

void writeSchedule(schedule *scheduleList, int scheduleCount)
{
    FILE *fp;
    char fileName[20];
    int i;
    for (i = 0; i < scheduleCount; i++)
    {
        sprintf(fileName, "schedule%d.txt", i + 1);
        fp = fopen(fileName, "w");
        fprintf(fp, "- Schedule for machine %d \n", i + 1);
        fprintf(fp, "%s:%d:%d", scheduleList[i].jobNo, scheduleList[i].start, scheduleList[i].end);
        fclose(fp);
    }
}

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
        if (strlen(jobList[i].jobNo) != 4 ||
            strlen(jobList[i].description) < 1 ||
            strlen(jobList[i].machineNo) != 2 ||
            jobList[i].duration < 1 ||
            strlen(jobList[i].clientName) < 1)
        {
            printf("Invalid job entry: %s", jobList[i].jobNo);
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

void scheduleJob(
    job *jobList,
    int jobCount,
    schedule *scheduleList,
    int *scheduleCount)
{
    int i;
    for (i = 0; i < jobCount; i++)
    {
        scheduleList[i].start = 1;
        scheduleList[i].end = jobList[i].duration;
        strcpy(scheduleList[i].jobNo, jobList[i].jobNo);
    }
    *scheduleCount = i;
}
int main(int argc, char *argv[])
{
    job jobList[MAX];
    int jobCount;
    int i;
    for (i = 1; i < argc; i++)
    {
        readFile(jobList, &jobCount, argv[i]);
    }
    findDisplayAndRemoveInvalidJobs(jobList, &jobCount, "invalidJobs.txt");
    schedule scheduleList[MAX];
    int scheduleCount;
    scheduleJob(jobList, jobCount, scheduleList, &scheduleCount);
    writeSchedule(scheduleList, scheduleCount);
    return 0;
}
