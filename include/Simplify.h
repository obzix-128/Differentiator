#ifndef SIMPLIFY_H
#define SIMPLIFY_H

#include <math.h>

#include "Differentiator.h"
#include "ErrorHandler.h"
#include "WorkWithLogFile.h"
#include "ReadFile.h"
#include "Run.h"

struct ReturnValueEvaluate
{
    ErrorNumbers error;
    double value;
};

ReturnValue simplifyExpression(FILE* log_file, Node* node);
ReturnValue findBranchSuitableForEvaluation(FILE* log_file, Node* node, int* simplification_counter);
ReturnValueEvaluate evaluate(FILE* log_file, Node* node, int* simplification_counter);
ReturnValueEvaluate evaluateOperation(FILE* log_file, Node* node, int* simplification_counter);

#endif // SIMPLIFY_H
