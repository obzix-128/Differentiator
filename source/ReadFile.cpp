#include "ReadFile.h"


ReturnValue getG(char* task_buffer)
{
    int pointer = 0;

    ReturnValue value = {};
    CHECK_RETURN_VALUE(value, getE(task_buffer, &pointer));

    if(task_buffer[pointer] != '$')
    {
        value.error = SYNTAX_ERROR;
        return value;
    }

    pointer++;
    return value;
}

ReturnValue getE(char* task_buffer, int* pointer)
{

    ReturnValue value = {};
    CHECK_RETURN_VALUE(value, getT(task_buffer, pointer));

    while(task_buffer[*pointer] == '+' || task_buffer[*pointer] == '-')
    {
        int operation = task_buffer[*pointer];
        (*pointer)++;

        ReturnValue value_two = {};
        CHECK_RETURN_VALUE(value_two, getT(task_buffer, pointer));
        if (value_two.error != NO_ERROR)
        {
            return value_two;
        }

        switch(operation)
        {
            case '+':
            {
                value.node = newNode(OP, 0, 0, ADD, value.node, value_two.node);
                break;
            }
            case '-':
            {
                value.node = newNode(OP, 0, 0, SUB, value.node, value_two.node);
                break;
            }
            default:
            {
                value.error = SYNTAX_ERROR;
                return value;
                break;
            }
        }
    }

    return value;
}

ReturnValue getT(char* task_buffer, int* pointer)
{
    ReturnValue value = {};
    CHECK_RETURN_VALUE(value, getS(task_buffer, pointer));

    while(task_buffer[*pointer] == '*' || task_buffer[*pointer] == '/')
    {
        int operation = task_buffer[*pointer];
        (*pointer)++;

        ReturnValue value_two = {};
        CHECK_RETURN_VALUE(value_two, getS(task_buffer, pointer));

        switch(operation)
        {
            case '*':
            {
                value.node = newNode(OP, 0, 0, MUL, value.node, value_two.node);
                break;
            }
            case '/':
            {
                value.node = newNode(OP, 0, 0, DIV, value.node, value_two.node);
                break;
            }
            default:
            {
                value.error = SYNTAX_ERROR;
                return value;
                break;
            }
        }
    }

    return value;
}

ReturnValue getS(char* task_buffer, int* pointer)
{
    ReturnValue value = {};
    CHECK_RETURN_VALUE(value, getP(task_buffer, pointer));

    while(task_buffer[*pointer] == '^')
    {
        (*pointer)++;

        ReturnValue value_two = {};
        CHECK_RETURN_VALUE(value_two, getP(task_buffer, pointer));

        value.node = newNode(OP, 0, 0, POW, value.node, value_two.node);
    }

    return value;
}

ReturnValue getP(char* task_buffer, int* pointer)
{
    ReturnValue value = {};

    if(task_buffer[*pointer] == '(')
    {
        (*pointer)++;

        CHECK_RETURN_VALUE(value, getE(task_buffer, pointer));

        if(task_buffer[*pointer] != ')')
        {
            value.error = SYNTAX_ERROR;
            return value;
        }

        (*pointer)++;
    }
    else
    {
        ReturnValue value_two   = {};
        ReturnValue value_three = {};
        ReturnValue value_four  = {};

        value       = getV(task_buffer, pointer);
        value_two   = getN(task_buffer, pointer);
        value_three = getF(task_buffer, pointer);
        value_four  = getL(task_buffer, pointer);

        if(value.error == NO_ERROR)
        {
            return value;
        }
        else if(value_two.error == NO_ERROR)
        {
            return value_two;
        }
        else if(value_three.error == NO_ERROR)
        {
            return value_three;
        }
        else if(value_four.error == NO_ERROR)
        {
            return value_four;
        }
        else
        {
            errorHandler(value.error, __PRETTY_FUNCTION__);
            return value;
        }
    }
    return value;
}

ReturnValue getL(char* task_buffer, int* pointer)
{
    ReturnValue value = {};

    if(task_buffer[*pointer] != 'l')
    {
        value.error = SYNTAX_ERROR;
        return value;
    }
    (*pointer)++;

    if(task_buffer[*pointer] != '(')
    {
        value.error = SYNTAX_ERROR;
        return value;
    }
    (*pointer)++;

    ReturnValue value_two = getE(task_buffer, pointer);

    if(task_buffer[*pointer] != ')')
    {
        value.error = SYNTAX_ERROR;
        return value;
    }
    (*pointer)++;

    if(task_buffer[*pointer] != '(')
    {
        value.error = SYNTAX_ERROR;
        return value;
    }
    (*pointer)++;

    ReturnValue value_three = getE(task_buffer, pointer);

    if(task_buffer[*pointer] != ')')
    {
        value.error = SYNTAX_ERROR;
        return value;
    }
    (*pointer)++;

    value.node = newNode(OP, 0, 0, LOG, value_two.node, value_three.node);

    return value;
}

ReturnValue getF(char* task_buffer, int* pointer)
{
    Operations operation = NUL;
    ReturnValue value = {};
    switch(task_buffer[*pointer])
    {
        case 's':
        {
            operation = SIN;
            break;
        }
        case 'c':
        {
            operation = COS;
            break;
        }
        case 't':
        {
            operation = TAN;
            break;
        }
        case 'e':
        {
            operation = EXP;
            break;
        }
        case 'n':
        {
            operation = LN;
            break;
        }
        default:
        {
            value.error = SYNTAX_ERROR;
            return value;
        }
    }
    (*pointer)++;

    if(task_buffer[*pointer] != '(')
    {
        value.error = SYNTAX_ERROR;
        return value;
    }
    (*pointer)++;

    ReturnValue value_two = getE(task_buffer, pointer);
    value.node = newNode(OP, 0, 0, operation, value_two.node, NULL);

    if(task_buffer[*pointer] != ')')
    {
        value.error = SYNTAX_ERROR;
        return value;
    }
    (*pointer)++;

    return value;
}

ReturnValue getV(char* task_buffer, int* pointer)
{
    char variable = 0;
    int starting_position = *pointer;

    if('a' <= task_buffer[*pointer] && task_buffer[*pointer] <= 'z' &&
       task_buffer[(*pointer) + 1] != '(')
    {
        variable = task_buffer[*pointer];
        (*pointer)++;
    }

    ReturnValue value = {};

    if(*pointer == starting_position)
    {
        value.error = SYNTAX_ERROR;
        return value;
    }

    value.node = newNode(VAR, 0, variable, NUL, NULL, NULL);

    return value;
}

ReturnValue getN(char* task_buffer, int* pointer)
{
    int number = 0;
    int starting_position = *pointer;

    while('0' <= task_buffer[*pointer] && task_buffer[*pointer] <= '9')
    {
        number = number * 10 + task_buffer[*pointer] - '0';
        (*pointer)++;
    }

    ReturnValue value = {};

    if(*pointer == starting_position)
    {
        value.error = SYNTAX_ERROR;
        return value;
    }

    value.node = newNode(NUM, number, 0, NUL, NULL, NULL);

    return value;
}
