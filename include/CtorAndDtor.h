#ifndef CTORANDDTOR_H
#define CTORANDDTOR_H

#include "Differentiator.h"

Node* newNode(NodeType type, double numeral_value, int variable, Operations operation_value,
              Node* left, Node* right);

#endif // CTORANDDTOR_H
