#ifndef DODIFF_H
#define DODIFF_H

#include "Differentiator.h"
#include "ErrorHandler.h"
#include "WorkWithLogFile.h"
#include "ReadFile.h"

ReturnValue diff(FILE* log_file, Node* task_node);
ReturnValue diffNumeral (void);
ReturnValue diffVariable(void);
ReturnValue diffOperation(FILE* log_file, Node* task_node);

ReturnValue treeCopy(Node* node);
ReturnValue checkForVariables(Node* task_node, int* counter);

ReturnValue diffAddition           (FILE* log_file, Node* task_node);
ReturnValue diffSubtraction        (FILE* log_file, Node* task_node);
ReturnValue diffMultiplication     (FILE* log_file, Node* task_node);
ReturnValue diffDivision           (FILE* log_file, Node* task_node);
ReturnValue diffPower              (FILE* log_file, Node* task_node);
ReturnValue diffPowerFunction      (FILE* log_file, Node* task_node);
ReturnValue diffExponentialFunction(FILE* log_file, Node* task_node);
ReturnValue diffSin                (FILE* log_file, Node* task_node);
ReturnValue diffCos                (FILE* log_file, Node* task_node);
ReturnValue diffTan                (FILE* log_file, Node* task_node);
ReturnValue diffExponent           (FILE* log_file, Node* task_node);
ReturnValue diffNaturalLog         (FILE* log_file, Node* task_node);
ReturnValue diffLog                (FILE* log_file, Node* task_node);

#define IF_NULL_ADDRESS_RETURN_ERROR(var, error) if(var == NULL)                               \
                                                 {                                             \
                                                     errorHandler(error, __PRETTY_FUNCTION__); \
                                                     ReturnValue check_errors = {NULL, error};  \
                                                     return check_errors;                       \
                                                 }

#endif // DODIFF_H
