#ifndef STUDENT_RECORDS_H
#define STUDENT_RECORDS_H

#include <stdio.h>
#include <unistd.h> /* getop */
#include <stdlib.h> /* EXIT_SUCESS, EXIT_FAILURE */
#include <string.h>

#define MAX_CHARS_NIF 9

typedef struct
{
    int student_id;
    char NIF[MAX_CHARS_NIF + 1];
    char *first_name;
    char *last_name;
} student_t;

typedef enum
{
    CREATE,
    APPEND,
    LIST,
    ID_SEARCH,
    NIF_SEARCH
} open_mode_t;

/**
 * Structure to hold the "variables" associated with
 * command-line options
 */
struct options
{
    char outfile[10000];
    open_mode_t mode;
};

student_t *parse_records(char *records[], int nr_records);
void printUsage(char *argv[]);
int dump_entries(student_t *entries, int nr_entries, FILE *students);
student_t *read_student_file(FILE *students, int *nr_entries);
char *loadstr(FILE *students);

#endif // STUDENT_RECORDS_H
