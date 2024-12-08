#include "Simplify.h"


ReturnValue simplifyExpression(FILE* log_file, Node* root)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,  NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(root,      NULL_ADDRESS_ERROR);

    ReturnValue check_error = {};

    int simplification_counter = 0;

    do
    {
        simplification_counter = 0;
        CHECK_RETURN_VALUE(check_error, findBranchSuitableForEvaluation(log_file, root,
                                                                        &simplification_counter));
    }
    while(simplification_counter != 0);

    return check_error;
}

ReturnValue findBranchSuitableForEvaluation(FILE* log_file, Node* node, int* simplification_counter)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,               NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(node,                   NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(simplification_counter, NULL_ADDRESS_ERROR);

    ReturnValue check_error = {};
    ReturnValueEvaluate branch_value = {};

    if(node->left != 0)
    {
        int number_of_variables_in_branch = 0;
        CHECK_RETURN_VALUE(check_error, checkForVariables(node->left, &number_of_variables_in_branch));

        if(number_of_variables_in_branch == 0)
        {
            branch_value = evaluate(log_file, node->left, simplification_counter);
            if(branch_value.error != NO_ERROR)
            {
                check_error.error = branch_value.error;
                return check_error;
            }
            node->left = newNode(NUM, branch_value.value, 0, NUL, NULL, NULL);
        }
        else
        {
        CHECK_RETURN_VALUE(check_error, findBranchSuitableForEvaluation(log_file, node->left,
                                                                        simplification_counter));
        }
    }
    if(node->right != 0)
    {
        int number_of_variables_in_branch = 0;

        CHECK_RETURN_VALUE(check_error, checkForVariables(node->right, &number_of_variables_in_branch));
        if(number_of_variables_in_branch == 0)
        {
            branch_value = evaluate(log_file, node->right, simplification_counter);
            if(branch_value.error != NO_ERROR)
            {
                check_error.error = branch_value.error;
                return check_error;
            }
            node->right = newNode(NUM, branch_value.value, 0, NUL, NULL, NULL);
        }
        else
        {
        CHECK_RETURN_VALUE(check_error, findBranchSuitableForEvaluation(log_file, node->right,
                                                                        simplification_counter));
        }
    }

    return check_error;
}

ReturnValueEvaluate evaluate(FILE* log_file, Node* node, int* simplification_counter)
{
    ReturnValueEvaluate check_error = {};
    if(log_file == NULL || node == NULL)
    {
        check_error.error = NULL_ADDRESS_ERROR;
        return check_error;
    }

    ReturnValueEvaluate answer = {};

    switch(node->type)
    {
        case NUM:
        {
            answer.value = node->value.numeral;
            break;
        }
        case VAR:
        {
            check_error.error = TYPE_ERROR;
            return check_error;
            break;
        }
        case OP:
        {
            answer = evaluateOperation(log_file, node, simplification_counter);
            if(answer.error != NO_ERROR)
            {
                return answer;
            }
            (*simplification_counter)++;
            break;
        }
        case NUL:
        {
            check_error.error = TYPE_ERROR;
            return check_error;
            break;
        }
        default:
        {
            check_error.error = TYPE_ERROR;
            return check_error;
            break;
        }
    }

    return answer;
}

ReturnValueEvaluate evaluateOperation(FILE* log_file, Node* node, int* simplification_counter)
{
    ReturnValueEvaluate check_error = {};
    if(log_file == NULL || node == NULL)
    {
        check_error.error = NULL_ADDRESS_ERROR;
        return check_error;
    }

    ReturnValueEvaluate answer = {};

    switch(node->value.operation)
    {
        case ADD:
        {
            ReturnValueEvaluate left_branch  = evaluate(log_file, node->left,  simplification_counter);
            ReturnValueEvaluate right_branch = evaluate(log_file, node->right, simplification_counter);

            answer.value = left_branch.value + right_branch.value;
            break;
        }
        case SUB:
        {
            ReturnValueEvaluate left_branch  = evaluate(log_file, node->left,  simplification_counter);
            ReturnValueEvaluate right_branch = evaluate(log_file, node->right, simplification_counter);

            answer.value = left_branch.value - right_branch.value;
            break;
        }
        case MUL:
        {
            ReturnValueEvaluate left_branch  = evaluate(log_file, node->left,  simplification_counter);
            ReturnValueEvaluate right_branch = evaluate(log_file, node->right, simplification_counter);

            answer.value = left_branch.value * right_branch.value;
            break;
        }
        case DIV:
        {
            ReturnValueEvaluate left_branch  = evaluate(log_file, node->left,  simplification_counter);
            ReturnValueEvaluate right_branch = evaluate(log_file, node->right, simplification_counter);

            answer.value = left_branch.value / right_branch.value;
            break;
        }
        case POW:
        {
            ReturnValueEvaluate left_branch  = evaluate(log_file, node->left,  simplification_counter);
            ReturnValueEvaluate right_branch = evaluate(log_file, node->right, simplification_counter);

            answer.value = pow(left_branch.value, right_branch.value);
            break;
        }
        case SIN:
        {
            ReturnValueEvaluate left_branch  = evaluate(log_file, node->left, simplification_counter);

            answer.value = sin(left_branch.value);
            break;
        }
        case COS:
        {
            ReturnValueEvaluate left_branch  = evaluate(log_file, node->left, simplification_counter);

            answer.value = cos(left_branch.value);
            break;
        }
        case TAN:
        {
            ReturnValueEvaluate left_branch  = evaluate(log_file, node->left, simplification_counter);

            answer.value = tan(left_branch.value);
            break;
        }
        case EXP:
        {
            ReturnValueEvaluate left_branch  = evaluate(log_file, node->left, simplification_counter);

            answer.value = exp(left_branch.value);
            break;
        }
        case LN:
        {
            ReturnValueEvaluate left_branch  = evaluate(log_file, node->left, simplification_counter);

            answer.value = log(left_branch.value);
            break;
        }
        case LOG:
        {
            ReturnValueEvaluate left_branch  = evaluate(log_file, node->left,  simplification_counter);
            ReturnValueEvaluate right_branch = evaluate(log_file, node->right, simplification_counter);

            answer.value = log(right_branch.value) / log(left_branch.value);
            break;
        }
        case NUL:
        {
            check_error.error = TYPE_ERROR;
            return check_error;
            break;
        }
        default:
        {
            check_error.error = TYPE_ERROR;
            return check_error;
            break;
        }
    }

    return answer;
}
