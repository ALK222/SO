#include "student_records.h"

student_t *parse_records(char *records[], int nr_records)
{

    student_t *aux = (student_t *)malloc(sizeof(student_t) * nr_records);
    int i;
    for (i = 0; i < nr_records; ++i)
    {
        aux[i].student_id = atoi(strsep(&records[i], ":"));
        strcpy(aux[i].NIF, strsep(&records[i], ":"));
        aux[i].first_name = strsep(&records[i], ":");
        aux[i].last_name = strsep(&records[i], ":");
    }

    return aux;
}

void printUsage(char **argv)
{
    fprintf(stderr, "Usage: %s -f file [ -h | -l | -c | -a | -q [ -i|-n ID] ] ] [ list of records ]", argv[0]);
}

int dump_entries(student_t *entries, int nr_entries, FILE *students)
{
    int i;
    for (i = 0; i < nr_entries; ++i)
    {
        fwrite(&entries[i].student_id, sizeof(int), 1, students);
        fwrite(entries[i].NIF, strlen(entries[i].NIF) + 1, 1, students);
        fwrite(entries[i].first_name, strlen(entries[i].first_name) + 1, 1, students);
        fwrite(entries[i].last_name, strlen(entries[i].last_name) + 1, 1, students);
    }

    return 0;
}

student_t *read_student_file(FILE *students, int *nr_entries)
{
    fseek(students, 0, SEEK_SET);
    fread(nr_entries, sizeof(int), 1, students);
    student_t *aux = (student_t *)malloc(sizeof(student_t) * (*nr_entries));

    for (int i = 0; i <= *nr_entries; i++)
    {
        fread(&aux[i].student_id, sizeof(int), 1, students);
        strcpy(aux[i].NIF, loadstr(students));
        aux[i].first_name = loadstr(students);
        aux[i].last_name = loadstr(students);
    }
    return aux;
}

char *loadstr(FILE *students)
{
    char c;
    int len = 1;
    fread(&c, sizeof(char), 1, students);
    while (c != '\0')
    {
        ++len;
        fread(&c, sizeof(char), 1, students);
    }
    char *str = malloc(sizeof(char) * len);
    fseek(students, -len, SEEK_CUR);
    fread(str, sizeof(char), len, students);
    return str;
}

void listStudents(student_t *records, int nr_entries)
{
    int i;
    for (i = 0; i < nr_entries; ++i)
    {
        student_t aux = records[i];
        printf("[Entry #%d]\n\
        \tStudent_id=%d\n\
        \tNIF=%s\n\
        \tFirst_name=%s\n\
        \tLast_name=%s\n",
               i, aux.student_id, aux.NIF, aux.first_name, aux.last_name);
    }
}

int searchDuplicates(int nr_entries, int nr_args, student_t *list, student_t *records, FILE *file)
{
    int new = 0;
    int i;

    for (i = 0; i < nr_args; ++i)
    {
        int found = 0;

        int j;
        for (j = 0; j < nr_entries; j++)
        {
            if (list[i].student_id == records[j].student_id)
            {
                found = 1;
                printf("Found duplicate student_id %d \n", list[i].student_id);
            }
        }
        if (found == 0)
        {
            dump_entries(&list[i], 1, file);
            new ++;
        }
    }

    return new;
}

char **parse_args(char **argv, int *nr_args)
{
    char p;
    int i = 0;

    do
    {
        p = argv[optind - 1 + i][0];
        if (p != '-')
        {
            i++;
        }
    } while (i < (*nr_args) && p != '-');

    *nr_args = i;
    char **buffer = malloc(sizeof(char *) * (*nr_args));
    for (i = 0; i < (*nr_args); i++)
    {
        buffer[i] = strdup(argv[optind - 1 + i]);
    }
    return buffer;
}

void searchEntry(struct options options, char *searchElement)
{
    int found = 0;
    int i = 0;
    int filterElement;

    int nr_entries;

    FILE *file = NULL;

    if ((file = fopen(options.outfile, "rb")) == NULL)
    {
        fprintf(stderr, "File %s could not be opened: ", options.outfile);
        perror(NULL);
        exit(EXIT_FAILURE);
    }

    student_t *list = read_student_file(file, &nr_entries);

    while (i < nr_entries && found == 0)
    {
        switch (options.mode)
        {
        case ID_SEARCH:
            filterElement = atoi(searchElement);
            if (list[i].student_id == filterElement)
            {
                found = 1;
            }
            break;
        case NIF_SEARCH:
            if (strcmp(list[i].NIF, searchElement) == 0)
            {
                found = 1;
            }

        default:
            break;
        }
        if (found != 1)
        {
            ++i;
        }
    }

    if (found == 0)
    {
        printf("No entry was found\n");
    }
    else
    {
        listStudents(&list[i], 1);
    }
}

int main(int argc, char **argv)
{
    int opt;
    struct options options;
    int search = 0;
    student_t *records = NULL;
    char **buffer = NULL;
    char *searchElement;
    int nr_args;
    FILE *file;

    while ((opt = getopt(argc, argv, "hlqi:n:c:a:f:")) != -1)
    {
        switch (opt)
        {
        case 'h':
            printUsage(argv);
            exit(EXIT_SUCCESS);
            break;
        case 'f':
            strcpy(options.outfile, optarg);
            break;
        case 'l':
            if ((file = fopen(options.outfile, "rb")) == NULL)
            {
                fprintf(stderr, "File %s could not be opened: ", options.outfile);
                perror(NULL);
                exit(EXIT_FAILURE);
            }
            records = read_student_file(file, &nr_args);
            listStudents(records, nr_args);
            fclose(file);
            free(records);

            break;
        case 'q':
            search = 1;
            break;
        case 'a':
            if ((file = fopen(options.outfile, "rb+")) == NULL)
            {
                fprintf(stderr, "File %s could not be opened: ", options.outfile);
                perror(NULL);
                exit(EXIT_FAILURE);
            }
            int nr_entries;
            student_t *students = read_student_file(file, &nr_entries);
            nr_args = argc - optind + 1;
            buffer = parse_args(argv, &nr_args);
            records = parse_records(buffer, nr_args);
            int new = 0;
            new = searchDuplicates(nr_entries, nr_args, records, students, file);
            nr_entries += new;
            fseek(file, 0, SEEK_SET);
            fwrite(&nr_entries, sizeof(int), 1, file);
            printf("%d extra records written\n", new);
            fclose(file);
            free(students);
            free(records);
            free(buffer);
            break;
        case 'c':
            if ((file = fopen(options.outfile, "wb+")) == NULL)
            {
                fprintf(stderr, "File %s could not be opened: ", options.outfile);
                perror(NULL);
                exit(EXIT_FAILURE);
            }

            nr_args = argc - optind + 1;
            buffer = parse_args(argv, &nr_args);

            records = parse_records(buffer, nr_args);

            printf("%d records written successfully\n", nr_args);
            fwrite(&nr_args, sizeof(int), 1, file);
            dump_entries(records, nr_args, file);
            fclose(file);
            free(records);
            free(buffer);

            break;
        case 'i':
            if (search == 0)
            {
                fprintf(stderr, "Search mode not enabled");
                exit(EXIT_FAILURE);
            }
            options.mode = ID_SEARCH;
            searchElement = strdup(optarg);
            break;
        case 'n':
            if (search == 0)
            {
                fprintf(stderr, "Search mode not enabled");
                exit(EXIT_FAILURE);
            }
            options.mode = NIF_SEARCH;
            searchElement = strdup(optarg);
            break;
        default:
            printUsage(argv);
            exit(EXIT_FAILURE);
            break;
        }
    }

    if (search == 1)
    {
        if (options.mode == ID_SEARCH || options.mode == NIF_SEARCH)
        {
            searchEntry(options, searchElement);
        }
        else
        {
            fprintf(stderr, "No search mode selected: ");
            perror(NULL);
            exit(EXIT_FAILURE);
        }
    }

    exit(EXIT_SUCCESS);
}
