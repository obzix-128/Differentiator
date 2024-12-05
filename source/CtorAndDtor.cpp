#include "CtorAndDtor.h"


Node* newNode(NodeType type, double numeral_value, int variable_value, Operations operation_value,
              Node* left, Node* right)
{
    Node* new_node = (Node*) calloc(1, sizeof(Node));

    new_node->type  = type;
    new_node->left  = left;
    new_node->right = right;

    if(new_node->type == NUM)
    {
        new_node->value.numeral = numeral_value;
    }
    else if(new_node->type == VAR)
    {
        new_node->value.variable = variable_value;
    }
    else if(new_node->type == OP)
    {
        new_node->value.operation = operation_value;
    }

    return new_node;
}
