#!/usr/bin/env bash

# Ejercicio entregable de SO 2022-2023
# Pruebas para student_records
# Autor: Alejandro Barrahina Argudo
# Autor: Alejandro Barrachina Argudo

# exeutable file
EXE=./student_records
# file with test cases
TEST_RECORDS=./records.txt

# check if exe file is usable
if [ -f "$EXE" ]; then
    if [ -x "$EXE" ]; then
        echo "File $EXE found and executable."
    else
        echo "File $EXE is not executable."
        exit 2
    fi
else
    echo "File $EXE does not exist."
    exit 2
fi

# check if tets cases are present
if [ -f "$TEST_RECORDS" ]; then
    echo "Records file found."
else
    echo "Records file does not exist."
    exit 2
fi

# parsed test cases
RECORDS=$( cat $TEST_RECORDS )
# mode of the script
MODE="-c" # create new database
for STUDENT in $RECORDS
do
    # Add data to the database
    if ! ./student_records -f database $MODE "$STUDENT"; then
        (echo "Error en la ejecución de la opción $MODE con el estudiante $STUDENT")
        exit $? # exit with error
    fi
    MODE="-a" # append to file
done
# list contents of database
if ! ./student_records -f database -l; then
    (echo "Error en el listado")
    exit $? #exit with error
fi

# hex dump of database
xxd database

for STUDENT in $RECORDS
do
    # search elements in database
    NIF=$(echo "$STUDENT" | cut -d ":" -f2)
    if ! ./student_records -f database -q -n "$NIF"; then
        (echo "Error en la busquedaq de $NIF")
        exit $?
    fi
done
