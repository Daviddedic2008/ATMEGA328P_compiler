#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "file_parser.h"


#define MAX_LINE_LENGTH 256
#define INITIAL_CAPACITY 10

char** fileParse(const char* filename, int* num_lines) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return NULL;
    }

    int capacity = INITIAL_CAPACITY;
    int count = 0;
    char** lines = (char**)malloc(capacity * sizeof(char*));
    if (!lines) {
        perror("Failed to allocate memory");
        fclose(file);
        return NULL;
    }

    char buffer[MAX_LINE_LENGTH];
    while (fgets(buffer, sizeof(buffer), file)) {
        if (count >= capacity) {
            capacity *= 2;
            lines = (char**)realloc(lines, capacity * sizeof(char*));
            if (!lines) {
                perror("Failed to reallocate memory");
                fclose(file);
                return NULL;
            }
        }

        lines[count] = _strdup(buffer);
        if (!lines[count]) {
            perror("Failed to duplicate string");
            fclose(file);
            return NULL;
        }
        count++;
    }

    fclose(file);
    *num_lines = count;
    return lines;
}


void writeLineToFile(const char* filename, const char* line, size_t length) {

    FILE* file = fopen(filename, "a");
    if (!file) {
        perror("Failed to open file");
        return;
    }
    size_t written = length;
    fprintf(file, "%s\n", line);
    if (written != length) {
        perror("Failed to write complete line to file");
        fclose(file);
        return;
    }


    if (fflush(file) != 0) {
        perror("Failed to flush the file buffer");
    }



    if (fclose(file) != 0) {
        perror("Failed to close file");
    }

}

void clearFile() {
    FILE* file = fopen("C:\\Users\\david\\CLionProjects\\untitled1\\compiler\\compiledArduino.txt", "w"); // Open the file in write mode
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // File is now empty
    fclose(file); // Close the file
}


