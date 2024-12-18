#ifndef SIMPLIFY_H
#define SIMPLIFY_H

#include "Differentiator.h"
#include "ErrorHandler.h"
#include "WorkWithLogFile.h"
#include "ReadFile.h"
#include "DoDiff.h"
#include "WorkWithDouble.h"
#include "CtorAndDtor.h"

struct ReturnValueEvaluate
{
    ErrorNumbers error;
    double value;
};

ReturnValue simplifyExpression(FILE* log_file, Node* node);

ReturnValue findBranchForEvaluation(FILE* log_file, Node* node, int* simplification_counter);
ReturnValue evaluateNode(FILE* log_file, Node* node, int* simplification_counter);
ReturnValueEvaluate evaluate               (FILE* log_file, Node* node, int* simplification_counter);
ReturnValueEvaluate evaluateOperation      (FILE* log_file, Node* node, int* simplification_counter);

ReturnValue findBranchesToRemoveTrivialCalculations(FILE* log_file, Node* node,
                                                    int* simplification_counter);
ReturnValue removeTrivialOperation       (FILE* log_file, Node* node, int* simplification_counter);
ReturnValue removeTrivialAddition        (FILE* log_file, Node* node, int* simplification_counter);
ReturnValue removeTrivialSubtraction     (FILE* log_file, Node* node, int* simplification_counter);
ReturnValue removeTrivialMultiplication  (FILE* log_file, Node* node, int* simplification_counter);
ReturnValue removeTrivialDivision        (FILE* log_file, Node* node, int* simplification_counter);
ReturnValue removeTrivialPower           (FILE* log_file, Node* node, int* simplification_counter);
ReturnValue removeTrivialNaturalLogarithm(FILE* log_file, Node* node, int* simplification_counter);
ReturnValue removeTrivialLogarithm       (FILE* log_file, Node* node, int* simplification_counter);

#endif // SIMPLIFY_H
