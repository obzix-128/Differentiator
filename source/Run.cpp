#include "Run.h"


ReturnValue differentiate(FILE* log_file, Node* task_node)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,  NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(task_node, NULL_ADDRESS_ERROR);

    ReturnValue new_node = {};

    switch(task_node->type)
    {
        case NUM:
        {
            new_node = differentiateNumeral();
            break;
        }
        case VAR:
        {
            new_node = differentiateVariable();
            break;
        }
        case OP:
        {
            new_node = differentiateOperation(log_file, task_node);
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

ReturnValue differentiateNumeral()
{
    ReturnValue new_node = {};

    new_node.node = newNode(NUM, 0, 0, NUL, NULL, NULL);

    return new_node;
}

ReturnValue differentiateVariable()
{
    ReturnValue new_node = {};

    new_node.node = newNode(NUM, 1, 0, NUL, NULL, NULL);

    return new_node;
}

ReturnValue differentiateOperation(FILE* log_file, Node* task_node)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,  NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(task_node, NULL_ADDRESS_ERROR);

    ReturnValue new_node = {};

    int number_of_variables_in_branch = 0;
    CHECK_RETURN_VALUE(new_node, checkForVariables(task_node, &number_of_variables_in_branch));
printf("number_of_variables_in_branch = %d\n", number_of_variables_in_branch);
    if(number_of_variables_in_branch == 0)
    {
        new_node.node = newNode(NUM, 0, 0, NUL, NULL, NULL);
        return new_node;
    }
    else
    {
        switch(task_node->value.operation)
        {
            case ADD:
            {
                CHECK_RETURN_VALUE(new_node, differentiateAddition(log_file, task_node));
                break;
            }
            case SUB:
            {
                CHECK_RETURN_VALUE(new_node, differentiateSubtraction(log_file, task_node));
                break;
            }
            case MUL:
            {
                CHECK_RETURN_VALUE(new_node, differentiateMultiplication(log_file, task_node));
                break;
            }
            case DIV:
            {
                CHECK_RETURN_VALUE(new_node, differentiateDivision(log_file, task_node));
                break;
            }
            case POW:
            {
                CHECK_RETURN_VALUE(new_node, differentiatePower(log_file, task_node));
                break;
            }
            case SIN:
            {
                CHECK_RETURN_VALUE(new_node, differentiateSine(log_file, task_node));
                break;
            }
            case COS:
            {
                CHECK_RETURN_VALUE(new_node, differentiateCosine(log_file, task_node));
                break;
            }
            case TAN:
            {
                CHECK_RETURN_VALUE(new_node, differentiateTangent(log_file, task_node));
                break;
            }
            case EXP:
            {
                CHECK_RETURN_VALUE(new_node, differentiateExponent(log_file, task_node));
                break;
            }
            case LN:
            {
                CHECK_RETURN_VALUE(new_node, differentiateNaturalLogarithm(log_file, task_node));
                break;
            }
            case LOG:
            {
                CHECK_RETURN_VALUE(new_node, differentiateLogarithm(log_file, task_node));
                break;
            }
            case NUL:
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

ReturnValue differentiateAddition(FILE* log_file, Node* task_node)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,  NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(task_node, NULL_ADDRESS_ERROR);

    ReturnValue left_node  = {};
    ReturnValue right_node = {};
    CHECK_RETURN_VALUE(left_node,  differentiate(log_file, task_node->left ));
    CHECK_RETURN_VALUE(right_node, differentiate(log_file, task_node->right));

    ReturnValue answer = {};
    answer.node = newNode(OP, 0, 0, ADD, left_node.node, right_node.node);

    return answer;
}

ReturnValue differentiateSubtraction(FILE* log_file, Node* task_node)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,  NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(task_node, NULL_ADDRESS_ERROR);

    ReturnValue left_node  = {};
    ReturnValue right_node = {};
    CHECK_RETURN_VALUE(left_node,  differentiate(log_file, task_node->left ));
    CHECK_RETURN_VALUE(right_node, differentiate(log_file, task_node->right));

    ReturnValue answer = {};
    answer.node = newNode(OP, 0, 0, SUB, left_node.node, right_node.node);

    return answer;
}

ReturnValue differentiateMultiplication(FILE* log_file, Node* task_node)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,  NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(task_node, NULL_ADDRESS_ERROR);

    ReturnValue left_node  = {};
    ReturnValue right_node = {};
    CHECK_RETURN_VALUE(left_node, differentiate(log_file, task_node->left));
    ReturnValue copy_task_node_right = {};
    CHECK_RETURN_VALUE(copy_task_node_right, treeCopy(task_node->right));
    Node* left_term = newNode(OP, 0, 0, MUL, left_node.node, copy_task_node_right.node);

    CHECK_RETURN_VALUE(right_node, differentiate(log_file, task_node->right));
    ReturnValue copy_task_node_left = {};
    CHECK_RETURN_VALUE(copy_task_node_left, treeCopy(task_node->left));
    Node* right_term = newNode(OP, 0, 0, MUL, right_node.node, copy_task_node_left.node);

    ReturnValue answer = {};
    answer.node = newNode(OP, 0, 0, ADD, left_term, right_term);

    return answer;
}

ReturnValue differentiateDivision(FILE* log_file, Node* task_node)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,  NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(task_node, NULL_ADDRESS_ERROR);

    ReturnValue left_node  = {};
    ReturnValue right_node = {};

    CHECK_RETURN_VALUE(left_node, differentiate(log_file, task_node->left));
    ReturnValue copy_task_node_right = {};
    CHECK_RETURN_VALUE(copy_task_node_right, treeCopy(task_node->right));
    Node* left_term = newNode(OP, 0, 0, MUL, left_node.node, copy_task_node_right.node);

    CHECK_RETURN_VALUE(right_node, differentiate(log_file, task_node->right));
    ReturnValue copy_task_node_left = {};
    CHECK_RETURN_VALUE(copy_task_node_left, treeCopy(task_node->left));
    Node* right_term = newNode(OP, 0, 0, MUL, right_node.node, copy_task_node_left.node);

    Node* numerator = newNode(OP, 0, 0, SUB, left_term, right_term);

    ReturnValue copy_task_node_right_for_denominator = {};
    CHECK_RETURN_VALUE(copy_task_node_right_for_denominator, treeCopy(task_node->right));
    Node* squaring = newNode(NUM, 2, 0, NUL, NULL, NULL);
    Node* denominator = newNode(OP, 0, 0, POW, copy_task_node_right_for_denominator.node, squaring);

    ReturnValue answer = {};
    answer.node = newNode(OP, 0, 0, DIV, numerator, denominator);

    return answer;
}

ReturnValue differentiatePower(FILE* log_file, Node* task_node)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,  NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(task_node, NULL_ADDRESS_ERROR);

    ReturnValue copy_basis_of_degree = {};
    CHECK_RETURN_VALUE(copy_basis_of_degree, treeCopy(task_node->left));

    ReturnValue copy_degree_indicator = {};
    CHECK_RETURN_VALUE(copy_degree_indicator, treeCopy(task_node->right));

    Node* one = newNode(NUM, 1, 0, NUL, NULL, NULL);
    Node* new_degree_indicator = newNode(OP, 0, 0, SUB, copy_degree_indicator.node, one);

    Node* new_power_expression = newNode(OP, 0, 0, POW, copy_basis_of_degree.node,
                                         new_degree_indicator);

    ReturnValue derivative_of_degree_base = {};
    CHECK_RETURN_VALUE(derivative_of_degree_base, differentiate(log_file, task_node->left));

    Node* part_of_answer = newNode(OP, 0, 0, MUL, derivative_of_degree_base.node,
                                   new_power_expression);

    ReturnValue another_copy_degree_indicator = {};
    CHECK_RETURN_VALUE(another_copy_degree_indicator, treeCopy(task_node->right));

    ReturnValue answer = {};
    answer.node = newNode(OP, 0, 0, MUL, another_copy_degree_indicator.node, part_of_answer);

    return answer;
}

ReturnValue differentiateSine(FILE* log_file, Node* task_node)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,  NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(task_node, NULL_ADDRESS_ERROR);

    ReturnValue copy_sine_argument = {};
    CHECK_RETURN_VALUE(copy_sine_argument, treeCopy(task_node->left));

    Node* derivative_of_sine = newNode(OP, 0, 0, COS, copy_sine_argument.node, NULL);

    ReturnValue derivative_of_sine_argument = {};
    CHECK_RETURN_VALUE(derivative_of_sine_argument, differentiate(log_file, task_node->left));

    ReturnValue answer = {};
    answer.node = newNode(OP, 0, 0, MUL, derivative_of_sine, derivative_of_sine_argument.node);

    return answer;
}

ReturnValue differentiateCosine(FILE* log_file, Node* task_node)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,  NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(task_node, NULL_ADDRESS_ERROR);

    ReturnValue copy_cosine_argument = {};
    CHECK_RETURN_VALUE(copy_cosine_argument, treeCopy(task_node->left));

    Node* negative_one = newNode(NUM, -1, 0, NUL, NULL, NULL);
    Node* part_of_derivative_of_cosine = newNode(OP, 0, 0, SIN, copy_cosine_argument.node, NULL);
    Node* derivative_of_cosine = newNode(OP, 0, 0, MUL, negative_one, part_of_derivative_of_cosine);

    ReturnValue derivative_of_cosine_argument = {};
    CHECK_RETURN_VALUE(derivative_of_cosine_argument, differentiate(log_file, task_node->left));

    ReturnValue answer = {};
    answer.node = newNode(OP, 0, 0, MUL, derivative_of_cosine, derivative_of_cosine_argument.node);

    return answer;
}

ReturnValue differentiateTangent(FILE* log_file, Node* task_node)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,  NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(task_node, NULL_ADDRESS_ERROR);

    ReturnValue copy_tangent_argument = {};
    CHECK_RETURN_VALUE(copy_tangent_argument, treeCopy(task_node->left));

    Node* basis_of_degree = newNode(OP, 0, 0, COS, copy_tangent_argument.node, NULL);
    Node* squaring = newNode(NUM, 2, 0, NUL, NULL, NULL);

    Node* denominator = newNode(OP, 0, 0, POW, basis_of_degree, squaring);

    ReturnValue derivative_of_tangent_argument = {};
    CHECK_RETURN_VALUE(derivative_of_tangent_argument, differentiate(log_file, task_node->left));

    ReturnValue answer = {};
    answer.node = newNode(OP, 0, 0, DIV, derivative_of_tangent_argument.node, denominator);

    return answer;
}

ReturnValue differentiateExponent(FILE* log_file, Node* task_node)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,  NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(task_node, NULL_ADDRESS_ERROR);

    ReturnValue copy_operation = {};
    CHECK_RETURN_VALUE(copy_operation, treeCopy(task_node));

    ReturnValue derivative_of_exponent_argument = {};
    CHECK_RETURN_VALUE(derivative_of_exponent_argument, differentiate(log_file, task_node->left));

    ReturnValue answer = {};
    answer.node = newNode(OP, 0, 0, MUL, copy_operation.node, derivative_of_exponent_argument.node);

    return answer;
}

ReturnValue differentiateNaturalLogarithm(FILE* log_file, Node* task_node)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,  NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(task_node, NULL_ADDRESS_ERROR);

    ReturnValue copy_logarithm_argument = {};
    CHECK_RETURN_VALUE(copy_logarithm_argument, treeCopy(task_node->left));

    ReturnValue derivative_of_logarithm_argument = {};
    CHECK_RETURN_VALUE(derivative_of_logarithm_argument, differentiate(log_file, task_node->left));

    ReturnValue answer = {};
    answer.node = newNode(OP, 0, 0, DIV, derivative_of_logarithm_argument.node,
                          copy_logarithm_argument.node);

    return answer;
}

ReturnValue differentiateLogarithm(FILE* log_file, Node* task_node)
{
    IF_NULL_ADDRESS_RETURN_ERROR(log_file,  NULL_ADDRESS_ERROR);
    IF_NULL_ADDRESS_RETURN_ERROR(task_node, NULL_ADDRESS_ERROR);

    ReturnValue copy_base_of_logarithm = {};
    CHECK_RETURN_VALUE(copy_base_of_logarithm, treeCopy(task_node->left));
    ReturnValue copy_logarithm_argument = {};
    CHECK_RETURN_VALUE(copy_logarithm_argument, treeCopy(task_node->right));

    Node* numerator   = newNode(OP, 0, 0, LN,  copy_logarithm_argument.node, NULL);
    Node* denominator = newNode(OP, 0, 0, LN,  copy_base_of_logarithm.node,  NULL);
    Node* fraction    = newNode(OP, 0, 0, DIV, numerator,             denominator);

    ReturnValue answer = {};
    CHECK_RETURN_VALUE(answer, differentiate(log_file, fraction));

    return answer;
}

ReturnValue treeCopy(Node* node)
{
    IF_NULL_ADDRESS_RETURN_ERROR(node, NULL_ADDRESS_ERROR);

    ReturnValue copy_node = {};

    switch(node->type)
    {
        case NUM:
        {
            copy_node.node = newNode(node->type, node->value.numeral, 0, NUL, NULL, NULL);
            break;
        }
        case VAR:
        {
            copy_node.node = newNode(node->type, 0, node->value.variable, NUL, NULL, NULL);
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
        case NUL:
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

