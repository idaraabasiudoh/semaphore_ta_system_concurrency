
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define NUM_STUDENTS 20
#define MAX_ID 9998
#define MIN_ID 1

bool is_unique(int *array, int size, int value)
{
    for (int i = 0; i < size; i++)
    {
        if (array[i] == value)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    FILE *fp = fopen("students.txt", "w");
    if (!fp)
    {
        fprintf(stderr, "Failed to create students.txt\n");
        return 1;
    }

    srand(time(NULL));

    int students[NUM_STUDENTS];
    for (int i = 0; i < NUM_STUDENTS - 1; i++)
    {
        int num;
        do
        {
            num = (rand() % (MAX_ID - MIN_ID + 1)) + MIN_ID;
        } while (!is_unique(students, i, num));

        students[i] = num;
    }
    students[NUM_STUDENTS - 1] = 9999;

    for (int i = 0; i < NUM_STUDENTS; i++)
    {
        if (fprintf(fp, "%04d\n", students[i]) < 0)
        {
            fprintf(stderr, "Failed to write to students.txt\n");
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    printf("Successfully generated students.txt\n");
    return 0;
}
