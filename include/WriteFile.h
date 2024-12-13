#ifndef WRITEFILE_H
#define WRITEFILE_H

#include "Differentiator.h"
#include "ErrorHandler.h"
#include "WorkWithLogFile.h"

ErrorNumbers writeAnswer(FILE* log_file, FILE* file_to_write, Node* root_of_task,
                         Node* root_of_answer);
ErrorNumbers printTitle(FILE* log_file, FILE* file_to_write);
ErrorNumbers printEnd(FILE* log_file, FILE* file_to_write);
ErrorNumbers writeToFile(FILE* log_file, FILE* file_to_write, Node* node);
ErrorNumbers writeOperation(FILE* log_file, FILE* file_to_write, Node* node);

#endif // WRITEFILE_H
