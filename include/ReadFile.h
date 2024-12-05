#ifndef READFILE_H
#define READFILE_H

#include <assert.h>
#include <errno.h>

#include "Differentiator.h"
#include "ErrorHandler.h"
#include "CtorAndDtor.h"
#include "WorkWithLogFile.h"

struct ReturnValue
{
    Node* node;
    ErrorNumbers error;
};

ErrorNumbers readFile(const char* file_name, char** task_buffer);
ErrorNumbers getFileSize(FILE* the_task_file, int* size);

ReturnValue getG(char* task_buffer);
ReturnValue getE(char* task_buffer, int* pointer);
ReturnValue getT(char* task_buffer, int* pointer);
ReturnValue getP(char* task_buffer, int* pointer);
ReturnValue getV(char* task_buffer, int* pointer);
ReturnValue getN(char* task_buffer, int* pointer);

#define CHECK_RETURN_VALUE(var, func) var = func;                                       \
                                      if(var.error != NO_ERROR)                         \
                                      {                                                 \
                                          errorHandler(var.error, __PRETTY_FUNCTION__); \
                                          return var;                                   \
                                      }

#endif // READFILE_H
