#ifndef RUN_H
#define RUN_H

#include "Differentiator.h"
#include "ErrorHandler.h"
#include "WorkWithLogFile.h"
#include "ReadFile.h"

ReturnValue differentiate(FILE* log_file, Node* task_node);
ReturnValue differentiateNumeral();
ReturnValue differentiateVariable();
ReturnValue differentiateOperation(FILE* log_file, Node* task_node);
ReturnValue treeCopy(Node* node);

#define IF_NULL_ADDRESS_RETURN_ERROR(var, error) if(var == NULL)                               \
                                                 {                                             \
                                                     errorHandler(error, __PRETTY_FUNCTION__); \
                                                     ReturnValue check_error = {NULL, error};  \
                                                     return check_error;                       \
                                                 }

#endif // RUN_H
