#include "tasystem.h"

sem_t *semaphores[NUM_TAS];
int shared_index;
int *student_numbers;

void load_students(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < NUM_STUDENTS; i++)
    {
        fscanf(file, "%d", &student_numbers[i]);
    }
    fclose(file);
}

void TA_process(int ta_id)
{
    int iterations = 0;
    char filename[20];
    sprintf(filename, "TA%d.txt", ta_id + 1);
    FILE *output_file = fopen(filename, "w");
    if (!output_file)
    {
        perror("Error creating TA file");
        exit(EXIT_FAILURE);
    }

    while (iterations < NUM_ITERATIONS)
    {
        // Lock semaphores for the current TA and the next TA
        sem_wait(semaphores[ta_id]);
        sem_wait(semaphores[(ta_id + 1) % NUM_TAS]);

        // Critical section
        printf("TA %d is accessing the database\n", ta_id + 1);
        int student_id = student_numbers[shared_index];
        shared_index = (shared_index + 1) % NUM_STUDENTS;

        // Unlock semaphores
        sem_post(semaphores[ta_id]);
        sem_post(semaphores[(ta_id + 1) % NUM_TAS]);

        printf("TA %d is marking student %d\n", ta_id + 1, student_id);
        int mark = rand() % 11;
        sleep(rand() % 10 + 1);
        fprintf(output_file, "Student: %d, Mark: %d\n", student_id, mark);
        fflush(output_file);

        if (student_id == 9999)
        {
            iterations++;
        }
    }

    fclose(output_file);
    printf("TA %d has finished marking\n", ta_id + 1);
}

int main()
{
    pid_t pids[NUM_TAS];
    for (int i = 0; i < NUM_TAS; i++)
    {
        char sem_name[20];
        sprintf(sem_name, "/sem_%d", i);
        sem_unlink(sem_name);
        semaphores[i] = sem_open(sem_name, O_CREAT | O_EXCL, 0644, 1);
        if (semaphores[i] == SEM_FAILED)
        {
            perror("Semaphore initialization failed");
            exit(EXIT_FAILURE);
        }
    }

    student_numbers = mmap(NULL, NUM_STUDENTS * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    shared_index = 0;

    load_students("students.txt");

    for (int i = 0; i < NUM_TAS; i++)
    {
        if ((pids[i] = fork()) == 0)
        {
            srand(getpid());
            TA_process(i);
            exit(EXIT_SUCCESS);
        }
    }

    for (int i = 0; i < NUM_TAS; i++)
    {
        waitpid(pids[i], NULL, 0);
    }

    for (int i = 0; i < NUM_TAS; i++)
    {
        sem_close(semaphores[i]);
        char sem_name[20];
        sprintf(sem_name, "/sem_%d", i);
        sem_unlink(sem_name);
    }

    munmap(student_numbers, NUM_STUDENTS * sizeof(int));

    return 0;
}