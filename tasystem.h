#ifndef TA_MANAGEMENT_H
#define TA_MANAGEMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/mman.h>

#define NUM_TAS 5
#define NUM_STUDENTS 20
#define NUM_ITERATIONS 3

extern sem_t *semaphores[NUM_TAS];
extern int shared_index;
extern int *student_numbers;

void load_students(const char *filename);
void TA_process(int ta_id);

#endif