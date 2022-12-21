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

