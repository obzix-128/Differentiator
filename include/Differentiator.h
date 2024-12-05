#ifndef DIFFERENTIATOR_H
#define DIFFERENTIATOR_H

#include <stdio.h>
#include <stdlib.h>

enum ErrorNumbers
{
    NO_ERROR            = 0,
    NULL_ADDRESS_ERROR  = 1,
    CALLOC_ERROR        = 2,
    NUMBER_OF_ARG_ERROR = 3,
    OPEN_ERROR          = 4,
    FSEEK_ERROR         = 5,
    FTELL_ERROR         = 6,
    SYNTAX_ERROR        = 7,
    ERROR_UNKNOWN_TYPE  = 8
};

enum Operations
{
    NUL = 0,
    ADD = '+',
    SUB = '-',
    MUL = '*',
    DIV = '/'
};

enum NodeType
{
    NUM = 1,
    VAR = 2,
    OP  = 3
};

union ValueType
{
    double numeral;
    char variable;
    enum Operations operation;
};

struct Node
{
    enum NodeType type;
    union ValueType value;
    struct Node* left;
    struct Node* right;
};

#define CHECK_NULL_ADDR_ERROR(variable, ERROR_NUMBER) if(variable == NULL) \
                                                      { \
                                                          return ERROR_NUMBER; \
                                                      }

#endif // DIFFERENTIATOR_H