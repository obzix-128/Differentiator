#include "Simplify.h"


ReturnValue simplifyExpression(FILE* log_file, Node* root)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,  NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(root,      NULL_ADDRESS_ERROR);

    ReturnValue check_error = {};
    check_error.node = root;

    int simplification_counter = 0;

    do
    {
        simplification_counter = 0;
        CHECK_RETURN_VALUE(check_error, findBranchSuitableForEvaluation(log_file, check_error.node,
                                                                        &simplification_counter));
        CHECK_RETURN_VALUE(check_error,
                           findBranchesToRemoveTrivialCalculations(log_file, check_error.node,
                                                                   &simplification_counter));
    }
    while(simplification_counter != 0);

    return check_error;
}

ReturnValue findBranchesToRemoveTrivialCalculations(FILE* log_file, Node* node,
                                                    int* simplification_counter)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,               NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(node,                   NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(simplification_counter, NULL_ADDRESS_ERROR);

    ReturnValue answer = {};

    if(node->type == NUM || node->type == VAR)
    {
        answer.node = node;
        return answer;
    }
    else if(node->type == OP)
    {
        CHECK_RETURN_VALUE(answer, determineTypeOfNodeOperation(log_file, node,
                                                                simplification_counter));
    }
    else
    {
        answer.error = TYPE_ERROR;
        return answer;
    }

    ReturnValue left_branch  = {};
    ReturnValue right_branch = {};

    if(answer.node->left != NULL)
    {
        CHECK_RETURN_VALUE(left_branch,
                           findBranchesToRemoveTrivialCalculations(log_file, answer.node->left,
                                                                   simplification_counter));
        answer.node->left = left_branch.node;
    }
    if(answer.node->right != NULL)
    {
        CHECK_RETURN_VALUE(right_branch,
                           findBranchesToRemoveTrivialCalculations(log_file, answer.node->right,
                                                                   simplification_counter));
        answer.node->right = right_branch.node;
    }

    return answer;
}

ReturnValue determineTypeOfNodeOperation(FILE* log_file, Node* node, int* simplification_counter)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,               NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(node,                   NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(simplification_counter, NULL_ADDRESS_ERROR);

    ReturnValue answer = {};

    switch(node->value.operation)
    {
        case ADD:
        {
            CHECK_RETURN_VALUE(answer, removeTrivialAddition(log_file, node,
                                                             simplification_counter));
            break;
        }
        case SUB:
        {
            CHECK_RETURN_VALUE(answer, removeTrivialSubtraction(log_file, node,
                                                                simplification_counter));
            break;
        }
        case MUL:
        {
            CHECK_RETURN_VALUE(answer, removeTrivialMultiplication(log_file, node,
                                                                   simplification_counter));
            break;
        }
        case DIV:
        {
            CHECK_RETURN_VALUE(answer, removeTrivialDivision(log_file, node,
                                                             simplification_counter));
            break;
        }
        case POW:
        {
            CHECK_RETURN_VALUE(answer, removeTrivialPower(log_file, node,
                                                          simplification_counter));
            break;
        }
        case SIN:
        {
            answer.node = node;
            break;
        }
        case COS:
        {
            answer.node = node;
            break;
        }
        case TAN:
        {
            answer.node = node;
            break;
        }
        case EXP:
        {
            answer.node = node;
            break;
        }
        case LN:
        {
            CHECK_RETURN_VALUE(answer, removeTrivialNaturalLogarithm(log_file, node,
                                                                     simplification_counter));
            break;
        }
        case LOG:
        {
            CHECK_RETURN_VALUE(answer, removeTrivialLogarithm(log_file, node,
                                                              simplification_counter));
            break;
        }
        case POISON:
        {
            answer.error = TYPE_ERROR;
            return answer;
            break;
        }
        default:
        {
            answer.error = TYPE_ERROR;
            return answer;
            break;
        }
    }

    return answer;
}

ReturnValue removeTrivialAddition(FILE* log_file, Node* node, int* simplification_counter)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,               NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(node,                   NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(simplification_counter, NULL_ADDRESS_ERROR);

    ReturnValue return_value = {};

    if(node->left->type == NUM && isItAboutSame(node->left->value.numeral, 0))
    {
        return_value.node = newNode(node->right->type, 0, 0, POISON, node->right->left,
                                    node->right->right);
        return_value.node->value = node->right->value;

        free(node);

        (*simplification_counter)++;
    }
    else if(node->right->type == NUM && isItAboutSame(node->right->value.numeral, 0))
    {
        return_value.node = newNode(node->left->type, 0, 0, POISON, node->left->left,
                                    node->left->right);
        return_value.node->value = node->left->value;

        free(node);

        (*simplification_counter)++;
    }
    else
    {
        return_value.node = node;
    }

    return return_value;
}

ReturnValue removeTrivialSubtraction(FILE* log_file, Node* node, int* simplification_counter)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,               NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(node,                   NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(simplification_counter, NULL_ADDRESS_ERROR);

    ReturnValue return_value = {};

    if(node->left->type == NUM && isItAboutSame(node->left->value.numeral, 0))
    {
        Node* negative_one = newNode(NUM, -1, 0, POISON, NULL, NULL);
        return_value.node = newNode(OP, 0, 0, MUL, negative_one, node->right);

        free(node);

        (*simplification_counter)++;
    }
    else if(node->right->type == NUM && isItAboutSame(node->right->value.numeral, 0))
    {
        return_value.node = newNode(node->left->type, 0, 0, POISON, node->left->left,
                                    node->left->right);
        return_value.node->value = node->left->value;

        free(node);

        (*simplification_counter)++;
    }
    else
    {
        return_value.node = node;
    }

    return return_value;
}

ReturnValue removeTrivialMultiplication(FILE* log_file, Node* node, int* simplification_counter)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,               NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(node,                   NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(simplification_counter, NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = NO_ERROR;
    ReturnValue return_value = {};

    if(node->left->type == NUM && isItAboutSame(node->left->value.numeral, 1))
    {
        return_value.node = newNode(node->right->type, 0, 0, POISON, node->right->left,
                                    node->right->right);
        return_value.node->value = node->right->value;

        free(node);

        (*simplification_counter)++;
    }
    else if(node->left->type == NUM && isItAboutSame(node->left->value.numeral, 0))
    {
        check_error = treeDtor(log_file, node);
        if(check_error != NO_ERROR)
        {
            return_value.error = check_error;
            return return_value;
        }

        return_value.node = newNode(NUM, 0, 0, POISON, NULL, NULL);

        (*simplification_counter)++;
    }
    else if(node->right->type == NUM && isItAboutSame(node->right->value.numeral, 1))
    {
        return_value.node = newNode(node->left->type, 0, 0, POISON, node->left->left,
                                    node->left->right);
        return_value.node->value = node->left->value;

        free(node);

        (*simplification_counter)++;
    }
    else if(node->right->type == NUM && isItAboutSame(node->right->value.numeral, 0))
    {
        check_error = treeDtor(log_file, node);
        if(check_error != NO_ERROR)
        {
            return_value.error = check_error;
            return return_value;
        }

        return_value.node = newNode(NUM, 0, 0, POISON, NULL, NULL);
        (*simplification_counter)++;
    }
    else
    {
        return_value.node = node;
    }

    return return_value;
}

ReturnValue removeTrivialDivision(FILE* log_file, Node* node, int* simplification_counter)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,               NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(node,                   NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(simplification_counter, NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = NO_ERROR;
    ReturnValue return_value = {};

    if(node->left->type == NUM && isItAboutSame(node->left->value.numeral, 0))
    {
        check_error = treeDtor(log_file, node);
        if(check_error != NO_ERROR)
        {
            return_value.error = check_error;
            return return_value;
        }

        return_value.node = newNode(NUM, 0, 0, POISON, NULL, NULL);

        (*simplification_counter)++;
    }
    else if(node->right->type == NUM && isItAboutSame(node->right->value.numeral, 1))
    {
        return_value.node = newNode(node->left->type, 0, 0, POISON, node->left->left,
                                    node->left->right);
        return_value.node->value = node->left->value;

        free(node);

        (*simplification_counter)++;
    }
    else if(node->right->type == NUM && isItAboutSame(node->right->value.numeral, 0))
    {
        return_value.error = UNCERTAINTY_ERROR;
        return return_value;
    }
    else
    {
        return_value.node = node;
    }

    return return_value;
}

ReturnValue removeTrivialPower(FILE* log_file, Node* node, int* simplification_counter)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,               NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(node,                   NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(simplification_counter, NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = NO_ERROR;
    ReturnValue return_value = {};

    if(node->left->type == NUM && isItAboutSame(node->left->value.numeral, 1))
    {
        check_error = treeDtor(log_file, node);
        if(check_error != NO_ERROR)
        {
            return_value.error = check_error;
            return return_value;
        }

        return_value.node = newNode(NUM, 1, 0, POISON, NULL, NULL);

        (*simplification_counter)++;
    }
    else if(node->left->type == NUM && isItAboutSame(node->left->value.numeral, 0))
    {
        check_error = treeDtor(log_file, node);
        if(check_error != NO_ERROR)
        {
            return_value.error = check_error;
            return return_value;
        }

        return_value.node = newNode(NUM, 0, 0, POISON, NULL, NULL);

        (*simplification_counter)++;
    }
    else if(node->right->type == NUM && isItAboutSame(node->right->value.numeral, 1))
    {

        return_value.node = newNode(node->left->type, 0, 0, POISON, node->left->left,
                                    node->left->right);
        return_value.node->value = node->left->value;

        free(node);

        (*simplification_counter)++;
    }
    else if(node->right->type == NUM && isItAboutSame(node->right->value.numeral, 0))
    {
        check_error = treeDtor(log_file, node);
        if(check_error != NO_ERROR)
        {
            return_value.error = check_error;
            return return_value;
        }

        return_value.node = newNode(NUM, 1, 0, POISON, NULL, NULL);
        (*simplification_counter)++;
    }
    else
    {
        return_value.node = node;
    }

    return return_value;
}

ReturnValue removeTrivialNaturalLogarithm(FILE* log_file, Node* node, int* simplification_counter)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,               NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(node,                   NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(simplification_counter, NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = NO_ERROR;
    ReturnValue return_value = {};

    if(node->left->type == NUM && isItAboutSame(node->left->value.numeral, 1))
    {
        check_error = treeDtor(log_file, node);
        if(check_error != NO_ERROR)
        {
            return_value.error = check_error;
            return return_value;
        }

        return_value.node = newNode(NUM, 0, 0, POISON, NULL, NULL);

        (*simplification_counter)++;
    }
    else
    {
        return_value.node = node;
    }

    return return_value;
}

ReturnValue removeTrivialLogarithm(FILE* log_file, Node* node, int* simplification_counter)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,               NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(node,                   NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(simplification_counter, NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = NO_ERROR;
    ReturnValue return_value = {};

    if(node->right->type == NUM && isItAboutSame(node->right->value.numeral, 1))
    {
        check_error = treeDtor(log_file, node);
        if(check_error != NO_ERROR)
        {
            return_value.error = check_error;
            return return_value;
        }

        return_value.node = newNode(NUM, 0, 0, POISON, NULL, NULL);

        (*simplification_counter)++;
    }
    else
    {
        return_value.node = node;
    }

    return return_value;
}

ReturnValue findBranchSuitableForEvaluation(FILE* log_file, Node* node, int* simplification_counter)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,               NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(node,                   NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(simplification_counter, NULL_ADDRESS_ERROR);

    ReturnValue result       = {};
    ReturnValue left_branch  = {};
    ReturnValue right_branch = {};

    if(node->left != 0)
    {
        CHECK_RETURN_VALUE(left_branch, evaluateNode(log_file, node->left, simplification_counter));
        node->left = left_branch.node;
    }
    if(node->right != 0)
    {
        CHECK_RETURN_VALUE(right_branch, evaluateNode(log_file, node->right, simplification_counter));
        node->right = right_branch.node;
    }
    result.node = node;

    return result;
}

ReturnValue evaluateNode(FILE* log_file, Node* node, int* simplification_counter)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,               NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(node,                   NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(simplification_counter, NULL_ADDRESS_ERROR);

    ReturnValue check_error = {};
    ReturnValue result      = {};

    ReturnValueEvaluate branch_value = {};

    int number_of_variables_in_branch = 0;
    CHECK_RETURN_VALUE(check_error, checkForVariables(node, &number_of_variables_in_branch));

    if(number_of_variables_in_branch == 0)
    {
        branch_value = evaluate(log_file, node, simplification_counter);
        if(branch_value.error != NO_ERROR)
        {
            check_error.error = branch_value.error;
            return check_error;
        }

        ErrorNumbers check_return_value = treeDtor(log_file, node);
        if(check_return_value != NO_ERROR)
        {
            check_error.error = check_return_value;
            return check_error;
        }

        node = newNode(NUM, branch_value.value, 0, POISON, NULL, NULL);
    }
    else
    {
    CHECK_RETURN_VALUE(check_error, findBranchSuitableForEvaluation(log_file, node,
                                                                    simplification_counter));
    }
    result.node = node;

    return result;
}

ReturnValueEvaluate evaluate(FILE* log_file, Node* node, int* simplification_counter)
{
    ReturnValueEvaluate check_error = {};
    if(log_file == NULL || node == NULL || simplification_counter == NULL)
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
        case POISON:
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
    if(log_file == NULL || node == NULL || simplification_counter == NULL)
    {
        check_error.error = NULL_ADDRESS_ERROR;
        return check_error;
    }

    ReturnValueEvaluate answer       = {};
    ReturnValueEvaluate left_branch  = {};
    ReturnValueEvaluate right_branch = {};

    if(node->left != NULL)
    {
        left_branch  = evaluate(log_file, node->left, simplification_counter);
    }
    if(node->right != NULL)
    {
        right_branch = evaluate(log_file, node->right, simplification_counter);
    }

    switch(node->value.operation)
    {
        case ADD:
        {
            answer.value = left_branch.value + right_branch.value;
            break;
        }
        case SUB:
        {
            answer.value = left_branch.value - right_branch.value;
            break;
        }
        case MUL:
        {
            answer.value = left_branch.value * right_branch.value;
            break;
        }
        case DIV:
        {
            if(isItAboutSame(right_branch.value, 0))
            {
                answer.error = UNCERTAINTY_ERROR;
                return answer;
            }

            answer.value = left_branch.value / right_branch.value;
            break;
        }
        case POW:
        {
            answer.value = pow(left_branch.value, right_branch.value);
            break;
        }
        case SIN:
        {
            answer.value = sin(left_branch.value);
            break;
        }
        case COS:
        {
            answer.value = cos(left_branch.value);
            break;
        }
        case TAN:
        {
            answer.value = tan(left_branch.value);
            break;
        }
        case EXP:
        {
            answer.value = exp(left_branch.value);
            break;
        }
        case LN:
        {
            if(left_branch.value <= 0)
            {
                answer.error = UNCERTAINTY_ERROR;
                return answer;
            }

            answer.value = log(left_branch.value);
            break;
        }
        case LOG:
        {
            if(left_branch.value <= 0  ||
               right_branch.value <= 0 ||
               isItAboutSame(right_branch.value, 1))
            {
                answer.error = UNCERTAINTY_ERROR;
                return answer;
            }

            answer.value = log(right_branch.value) / log(left_branch.value);
            break;
        }
        case POISON:
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
