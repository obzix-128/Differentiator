#ifndef WORKWITHLOGFILE_H
#define WORKWITHLOGFILE_H

#include "Differentiator.h"

#define OPEN_FILE_IN_RECORDING_MODE "w"

ErrorNumbers openFile(FILE** file, const char* file_name, const char* opening_mode);
ErrorNumbers treeDump(FILE* log_file, Node* root, const char* func_name, Node* new_node);
ErrorNumbers createGraf(FILE* log_file, Node* node, Node* new_node);
ErrorNumbers buildAllNodes(Node* node, FILE* file_to_write, Node* new_node);

#endif // WORKWITHLOGFILE_H
