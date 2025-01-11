#pragma once

char** fileParse(const char* filename, int* numLines);

void writeLineToFile(const char* filename, const char* line, size_t length);

void clearFile();