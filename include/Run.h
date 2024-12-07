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
ReturnValue checkForVariables(Node* task_node, int* counter);

ReturnValue differentiateAddition(FILE* log_file, Node* task_node);
ReturnValue differentiateSubtraction(FILE* log_file, Node* task_node);
ReturnValue differentiateMultiplication(FILE* log_file, Node* task_node);
ReturnValue differentiateDivision(FILE* log_file, Node* task_node);
ReturnValue differentiatePower(FILE* log_file, Node* task_node);
ReturnValue differentiateSine(FILE* log_file, Node* task_node);
ReturnValue differentiateCosine(FILE* log_file, Node* task_node);
ReturnValue differentiateTangent(FILE* log_file, Node* task_node);
ReturnValue differentiateExponent(FILE* log_file, Node* task_node);
ReturnValue differentiateNaturalLogarithm(FILE* log_file, Node* task_node);
ReturnValue differentiateLogarithm(FILE* log_file, Node* task_node);

#define IF_NULL_ADDRESS_RETURN_ERROR(var, error) if(var == NULL)                               \
                                                 {                                             \
                                                     errorHandler(error, __PRETTY_FUNCTION__); \
                                                     ReturnValue check_error = {NULL, error};  \
                                                     return check_error;                       \
                                                 }

#endif // RUN_H
