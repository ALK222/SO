/**
 * @file student_records.h
 * @author Alejandro Barrachina Argudo
 * @author David Cantador Piedras
 * @brief Ejercicio evaluable SO 2022-2023
 * @version 0.1
 * @date 2023-01-03
 *
 * Ejercicio evaluable correspondiente a la Parte 3 de la práctica 2
 *
 */
#ifndef STUDENT_RECORDS_H
#define STUDENT_RECORDS_H

#include <stdio.h>
#include <unistd.h> /* getop */
#include <stdlib.h> /* EXIT_SUCESS, EXIT_FAILURE */
#include <string.h>

#define MAX_CHARS_NIF 9

/**
 * @brief Struct with student information
 *
 */
typedef struct
{
    int student_id;              /* Student unique id */
    char NIF[MAX_CHARS_NIF + 1]; /* Student NIF */
    char *first_name;            /* First name */
    char *last_name;             /* Last name */
} student_t;

/**
 * @brief Defines how the file will be opened
 *
 */
typedef enum
{
    CREATE,    /* Creates or completely rewrites the file */
    APPEND,    /* Appends the new information to the end of the file */
    LIST,      /* Only reads the information from the file*/
    ID_SEARCH, /* Only reads the information from the file to search for an ID */
    NIF_SEARCH /* Only reads the information from the file to search for a NIF */
} open_mode_t;

/**
 * Structure to hold the "variables" associated with
 * command-line options
 */
struct options
{
    char outfile[10000]; /* Name or path to the file */
    open_mode_t mode;    /* Opening and operation mode */
};

/**
 * @brief Takes a buffer with information and parses it to student information.
 *
 * @param records char buffer with the raw information.
 * @param nr_records number of records to parse.
 * @return student_t* List of students.
 */
student_t *parse_records(char *records[], int nr_records);

/**
 * @brief Prints the help message.
 *
 * @param name Name of the program.
 */
void printUsage(char *name);

/**
 * @brief Dumps the entries into the given file.
 *
 * @param entries Student list.
 * @param nr_entries Number of students.
 * @param students Database for the data.
 */
void dump_entries(student_t *entries, int nr_entries, FILE *students);

/**
 * @brief Loads the student data from the file.
 * @see loadstr
 *
 * @param students File where the data is stored.
 * @param nr_entries Pointer to the number of students, will be loaded with the file.
 * @return student_t*
 */
student_t *read_student_file(FILE *students, int *nr_entries);

/**
 * @brief Loads student data from a file.
 *
 * @param students File where the data is stored.
 * @return char* Selected info about the student (NIF, First name or Last name).
 */
char *loadstr(FILE *students);

/**
 * @brief Lists students with a special format.
 *
 * @param records List of students.
 * @param nr_entries number of students.
 */
void listStudents(student_t *records, int nr_entries);

/**
 * @brief Inserts non duplicate students on the database.
 *
 * @param nr_entries Number of existing entries on the database.
 * @param nr_args Number of additions.
 * @param list List of additions.
 * @param records List of already added students.
 * @param file Database file.
 * @return Number of final additions.
 */
int searchDuplicates(int nr_entries, int nr_args, student_t *list, student_t *records, FILE *file);

/**
 * @brief Parses a given parameter list and returns a list of students.
 *
 * @param argv Arguments passed to the program.
 * @param nr_args Pointer to the number of arguments, transformed into number of students.
 * @return char** List of raw student data.
 */
char **parse_args(char **argv, int *nr_args);

/**
 * @brief Searches an entry on the database.
 *
 * @param options File and search mode.
 * @param searchElement NIF or ID to search.
 */
void searchEntry(struct options options, char *searchElement);

#endif // STUDENT_RECORDS_H
