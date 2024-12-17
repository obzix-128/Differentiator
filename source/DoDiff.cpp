#include "DoDiff.h"

#define DIFF_LEFT(left_branch)                                     \
ReturnValue left_branch = {};                                      \
CHECK_RETURN_VALUE(left_branch,  diff(log_file, task_node->left));

#define DIFF_RIGHT(right_branch)                                     \
ReturnValue right_branch = {};                                       \
CHECK_RETURN_VALUE(right_branch,  diff(log_file, task_node->right));

#define COPY_LEFT(copy_branch)                              \
ReturnValue copy_branch = {};                               \
CHECK_RETURN_VALUE(copy_branch, treeCopy(task_node->left));

#define COPY_RIGHT(copy_branch)                              \
ReturnValue copy_branch = {};                                \
CHECK_RETURN_VALUE(copy_branch, treeCopy(task_node->right));

#define NODE_COPY(copy_branch)                       \
ReturnValue copy_branch = {};                        \
CHECK_RETURN_VALUE(copy_branch, treeCopy(task_node));

#define NEW_OP_NODE(result, operation, left, right)               \
ReturnValue result = {};                                          \
result.node = newNode(OP, 0, 0, operation, left.node, right.node);

#define NEW_NUM_NODE(result, value)                       \
ReturnValue result = {};                                  \
result.node = newNode(NUM, value, 0, POISON, NULL, NULL);


ReturnValue diff(FILE* log_file, Node* task_node)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,  NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(task_node, NULL_ADDRESS_ERROR);

    ReturnValue new_node = {};

    switch(task_node->type)
    {
        case NUM:
        {
            new_node = diffNumeral();
            break;
        }
        case VAR:
        {
            new_node = diffVariable();
            break;
        }
        case OP:
        {
            new_node = diffOperation(log_file, task_node);
            break;
        }
        case POISON_TYPE:
        {
            new_node.error = TYPE_ERROR;
            return new_node;
            break;
        }
        default:
        {
            new_node.error = TYPE_ERROR;
            return new_node;
            break;
        }
    }

    return new_node;
}

ReturnValue diffNumeral(void)
{
    ReturnValue new_node = {};

    new_node.node = newNode(NUM, 0, 0, POISON, NULL, NULL);

    return new_node;
}

ReturnValue diffVariable(void)
{
    ReturnValue new_node = {};

    new_node.node = newNode(NUM, 1, 0, POISON, NULL, NULL);

    return new_node;
}

ReturnValue diffOperation(FILE* log_file, Node* task_node)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,  NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(task_node, NULL_ADDRESS_ERROR);

    ReturnValue new_node = {};

    int number_of_variables_in_branch = 0;
    CHECK_RETURN_VALUE(new_node, checkForVariables(task_node, &number_of_variables_in_branch));

    if(number_of_variables_in_branch == 0)
    {
        new_node.node = newNode(NUM, 0, 0, POISON, NULL, NULL);
        return new_node;
    }
    else
    {
        switch(task_node->value.operation)
        {
            case ADD:
            {
                CHECK_RETURN_VALUE(new_node, diffAddition(log_file, task_node));
                break;
            }
            case SUB:
            {
                CHECK_RETURN_VALUE(new_node, diffSubtraction(log_file, task_node));
                break;
            }
            case MUL:
            {
                CHECK_RETURN_VALUE(new_node, diffMultiplication(log_file, task_node));
                break;
            }
            case DIV:
            {
                CHECK_RETURN_VALUE(new_node, diffDivision(log_file, task_node));
                break;
            }
            case POW:
            {
                CHECK_RETURN_VALUE(new_node, diffPower(log_file, task_node));
                break;
            }
            case SIN:
            {
                CHECK_RETURN_VALUE(new_node, diffSin(log_file, task_node));
                break;
            }
            case COS:
            {
                CHECK_RETURN_VALUE(new_node, diffCos(log_file, task_node));
                break;
            }
            case TAN:
            {
                CHECK_RETURN_VALUE(new_node, diffTan(log_file, task_node));
                break;
            }
            case EXP:
            {
                CHECK_RETURN_VALUE(new_node, diffExponent(log_file, task_node));
                break;
            }
            case LN:
            {
                CHECK_RETURN_VALUE(new_node, diffNaturalLog(log_file, task_node));
                break;
            }
            case LOG:
            {
                CHECK_RETURN_VALUE(new_node, diffLog(log_file, task_node));
                break;
            }
            case POISON:
            {
                new_node.error = TYPE_ERROR;
                return new_node;
                break;
            }
            default:
            {
                new_node.error = TYPE_ERROR;
                return new_node;
                break;
            }
        }
    }

    return new_node;
}

ReturnValue checkForVariables(Node* task_node, int* counter)
{
    IF_NULL_ADDRESS_RETURN_ERROR(task_node, NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(counter,   NULL_ADDRESS_ERROR);

    ReturnValue check_error = {};

    if(task_node->left != 0)
    {
        CHECK_RETURN_VALUE(check_error, checkForVariables(task_node->left, counter));
    }
    if(task_node->right != 0)
    {
        CHECK_RETURN_VALUE(check_error, checkForVariables(task_node->right, counter));
    }

    if(task_node->type == VAR)
    {
        (*counter)++;
    }

    return check_error;
}

ReturnValue diffAddition(FILE* log_file, Node* task_node)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,  NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(task_node, NULL_ADDRESS_ERROR);

    DIFF_LEFT (left_branch );
    DIFF_RIGHT(right_branch);

    NEW_OP_NODE(result, ADD, left_branch, right_branch);

    return result;
}

ReturnValue diffSubtraction(FILE* log_file, Node* task_node)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,  NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(task_node, NULL_ADDRESS_ERROR);

    DIFF_LEFT (left_branch );
    DIFF_RIGHT(right_branch);

    NEW_OP_NODE(result, SUB, left_branch, right_branch);

    return result;
}

ReturnValue diffMultiplication(FILE* log_file, Node* task_node)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,  NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(task_node, NULL_ADDRESS_ERROR);

    DIFF_LEFT (left_branch);
    COPY_RIGHT(copy_right );
    NEW_OP_NODE(left_mul, MUL, left_branch, copy_right);

    DIFF_RIGHT(right_branch);
    COPY_LEFT (copy_left   );
    NEW_OP_NODE(right_mul, MUL, right_branch, copy_left);

    NEW_OP_NODE(result, ADD, left_mul, right_mul);

    return result;
}

ReturnValue diffDivision(FILE* log_file, Node* task_node)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,  NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(task_node, NULL_ADDRESS_ERROR);

    DIFF_LEFT (left_branch);
    COPY_RIGHT(copy_right );
    NEW_OP_NODE(left_mul, MUL, left_branch, copy_right);

    DIFF_RIGHT(right_branch);
    COPY_LEFT (copy_left   );
    NEW_OP_NODE(right_mul, MUL, right_branch, copy_left);

    NEW_OP_NODE(result, SUB, left_mul, right_mul);

    return result;
}

ReturnValue diffPower(FILE* log_file, Node* task_node)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,  NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(task_node, NULL_ADDRESS_ERROR);

    ReturnValue check_error = {};
    ReturnValue answer      = {};

    int number_of_variables_in_basis     = 0;
    int number_of_variables_in_indicator = 0;

    CHECK_RETURN_VALUE(check_error, checkForVariables(task_node->left, &number_of_variables_in_basis));
    CHECK_RETURN_VALUE(check_error, checkForVariables(task_node->right,
                                                      &number_of_variables_in_indicator));

    if(number_of_variables_in_basis > 0 && number_of_variables_in_indicator > 0)
    {
        ReturnValue left_branch  = {};
        ReturnValue right_branch = {};

        CHECK_RETURN_VALUE(left_branch,  diffPowerFunction      (log_file, task_node));
        CHECK_RETURN_VALUE(right_branch, diffExponentialFunction(log_file, task_node));

        answer.node = newNode(OP, 0, 0, ADD, left_branch.node, right_branch.node);
    }
    else if(number_of_variables_in_basis > 0)
    {
        CHECK_RETURN_VALUE(answer, diffPowerFunction(log_file, task_node));
    }
    else if(number_of_variables_in_indicator > 0)
    {
        CHECK_RETURN_VALUE(answer, diffExponentialFunction(log_file, task_node));
    }
    else
    {
        answer.error = DIFF_POWER_ERROR;
    }

    return answer;
}

ReturnValue diffExponentialFunction(FILE* log_file, Node* task_node) // TODO? Показательная функция на английском?
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,  NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(task_node, NULL_ADDRESS_ERROR);

    ReturnValue null_node = {};

    COPY_LEFT  (copy_left);
    NEW_OP_NODE(natural_log, LN, copy_left, null_node);

    NODE_COPY  (task_node_copy);
    NEW_OP_NODE(preliminary_stage, MUL, task_node_copy, natural_log);

    DIFF_RIGHT (right_branch);
    NEW_OP_NODE(result, MUL, preliminary_stage, right_branch);

    return result;
}

ReturnValue diffPowerFunction(FILE* log_file, Node* task_node)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,  NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(task_node, NULL_ADDRESS_ERROR);

    COPY_LEFT (copy_left );
    COPY_RIGHT(copy_right);

    NEW_NUM_NODE(one, 1);

    NEW_OP_NODE(new_power, SUB, copy_right, one);
    NEW_OP_NODE(new_power_expression, POW, copy_left, new_power)

    DIFF_LEFT(left_branch);

    NEW_OP_NODE(preliminary_stage, MUL, left_branch, new_power_expression);

    COPY_RIGHT(another_copy_right);

    NEW_OP_NODE(result, MUL, another_copy_right, preliminary_stage);

    return result;
}

ReturnValue diffSin(FILE* log_file, Node* task_node)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,  NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(task_node, NULL_ADDRESS_ERROR);

    ReturnValue null_node = {};

    COPY_LEFT(copy_left);

    NEW_OP_NODE(cos, COS, copy_left, null_node);

    DIFF_LEFT(left_branch);

    NEW_OP_NODE(result, MUL, cos, left_branch);

    return result;
}

ReturnValue diffCos(FILE* log_file, Node* task_node)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,  NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(task_node, NULL_ADDRESS_ERROR);

    ReturnValue null_node = {};

    COPY_LEFT(copy_left);

    NEW_NUM_NODE(negative_one, -1);

    NEW_OP_NODE(sin, SIN, copy_left, null_node);

    NEW_OP_NODE(negative_sin, MUL, sin, negative_one);

    DIFF_LEFT(left_branch);

    NEW_OP_NODE(result, MUL, negative_sin, left_branch);

    return result;
}

ReturnValue diffTan(FILE* log_file, Node* task_node)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,  NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(task_node, NULL_ADDRESS_ERROR);

    ReturnValue null_node = {};

    COPY_LEFT(copy_left);

    NEW_OP_NODE(cos, COS, copy_left, null_node);
    NEW_NUM_NODE(two, 2);
    NEW_OP_NODE(denominator, POW, cos, two)

    DIFF_LEFT(left_branch);

    NEW_OP_NODE(result, DIV, left_branch, denominator);

    return result;
}

ReturnValue diffExponent(FILE* log_file, Node* task_node)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,  NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(task_node, NULL_ADDRESS_ERROR);

    NODE_COPY(task_node_copy);

    DIFF_LEFT(left_branch);

    NEW_OP_NODE(result, MUL, task_node_copy, left_branch);

    return result;
}

ReturnValue diffNaturalLog(FILE* log_file, Node* task_node)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,  NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(task_node, NULL_ADDRESS_ERROR);

    COPY_LEFT(copy_left);

    DIFF_LEFT(left_branch);

    NEW_OP_NODE(result, DIV, left_branch, copy_left);

    return result;
}

ReturnValue diffLog(FILE* log_file, Node* task_node)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,  NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(task_node, NULL_ADDRESS_ERROR);

    ReturnValue null_node = {};
    
    COPY_LEFT (copy_left );
    COPY_RIGHT(copy_right);

    NEW_OP_NODE(numerator,   LN, copy_right, null_node);
    NEW_OP_NODE(denominator, LN, copy_left,  null_node);

    NEW_OP_NODE(fraction, DIV, numerator, denominator);

    ReturnValue result = {};
    CHECK_RETURN_VALUE(result, diff(log_file, fraction.node));

    return result;
}

ReturnValue treeCopy(Node* node)
{
    IF_NULL_ADDRESS_RETURN_ERROR(node, NULL_ADDRESS_ERROR);

    ReturnValue copy_node = {};

    switch(node->type)
    {
        case NUM:
        {
            copy_node.node = newNode(node->type, node->value.numeral, 0, POISON, NULL, NULL);
            break;
        }
        case VAR:
        {
            copy_node.node = newNode(node->type, 0, node->value.variable, POISON, NULL, NULL);
            break;
        }
        case OP:
        {
            ReturnValue copy_node_left  = {};
            ReturnValue copy_node_right = {};

            if(node->left != 0)
            {
                CHECK_RETURN_VALUE(copy_node_left, treeCopy(node->left));
            }
            if(node->right != 0)
            {
                CHECK_RETURN_VALUE(copy_node_right, treeCopy(node->right));
            }

            copy_node.node = newNode(node->type, 0, 0, node->value.operation, copy_node_left.node,
                                     copy_node_right.node);
            break;
        }
        case POISON:
        {
            copy_node.error = TYPE_ERROR;
            return copy_node;
            break;
        }
        default:
        {
            copy_node.error = TYPE_ERROR;
            return copy_node;
            break;
        }
    }

    return copy_node;
}

