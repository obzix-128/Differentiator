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

ReturnValue recursiveDescent    (char* task_buffer);
ReturnValue getExpression       (char* task_buffer, int* pointer);
ReturnValue getTerm             (char* task_buffer, int* pointer);
ReturnValue getPower            (char* task_buffer, int* pointer);
ReturnValue getPrimaryExpression(char* task_buffer, int* pointer);
ReturnValue getFuncWithTwoArg   (char* task_buffer, int* pointer);
ReturnValue getFuncWithOneArg   (char* task_buffer, int* pointer);
ReturnValue getVariable         (char* task_buffer, int* pointer);
ReturnValue getNumeral          (char* task_buffer, int* pointer);

#define CHECK_RETURN_VALUE(var, func) var = func;                                       \
                                      if(var.error != NO_ERROR)                         \
                                      {                                                 \
                                          errorHandler(var.error, __PRETTY_FUNCTION__); \
                                          return var;                                   \
                                      }

#endif // READFILE_H
