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

ErrorNumbers writeAdd(FILE* log_file, FILE* file_to_write, Node* node);
ErrorNumbers writeSub(FILE* log_file, FILE* file_to_write, Node* node);
ErrorNumbers writeMul(FILE* log_file, FILE* file_to_write, Node* node);
ErrorNumbers writeDiv(FILE* log_file, FILE* file_to_write, Node* node);
ErrorNumbers writePow(FILE* log_file, FILE* file_to_write, Node* node);
ErrorNumbers writeSin(FILE* log_file, FILE* file_to_write, Node* node);
ErrorNumbers writeCos(FILE* log_file, FILE* file_to_write, Node* node);
ErrorNumbers writeTan(FILE* log_file, FILE* file_to_write, Node* node);
ErrorNumbers writeExp(FILE* log_file, FILE* file_to_write, Node* node);
ErrorNumbers writeLn (FILE* log_file, FILE* file_to_write, Node* node);
ErrorNumbers writeLog(FILE* log_file, FILE* file_to_write, Node* node);

#endif // WRITEFILE_H
