#include "WorkWithLogFile.h"


ErrorNumbers openFile(FILE** file, const char* file_name, const char* opening_mode)
{
    CHECK_NULL_ADDR_ERROR(file,         NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(file_name,    NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(opening_mode, NULL_ADDRESS_ERROR);

    *file = fopen(file_name, opening_mode);
    CHECK_NULL_ADDR_ERROR(*file, OPEN_ERROR);

    return NO_ERROR;
}

ErrorNumbers readFile(const char* file_name, char** task_buffer)
{
    CHECK_NULL_ADDR_ERROR(file_name, NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(task_buffer,   NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = NO_ERROR;

    FILE* the_task_file = NULL;
    CHECK_ERROR(openFile(&the_task_file, file_name, OPEN_FILE_IN_READING_MODE));

    int size = 0;
    CHECK_ERROR(getFileSize(the_task_file, &size));

    *task_buffer = (char*) calloc(size, sizeof(char));
    CHECK_NULL_ADDR_ERROR(*task_buffer, CALLOC_ERROR);

    size = fread(*task_buffer, sizeof(char), size, the_task_file);

    fclose(the_task_file);

    return check_error;
}

ErrorNumbers getFileSize(FILE* the_task_file, int* size)
{
    CHECK_NULL_ADDR_ERROR(the_task_file, NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(size,          NULL_ADDRESS_ERROR);

    int check_error = 0;

    check_error = fseek(the_task_file, 0, SEEK_END);
    if(check_error != 0)
    {
        return FSEEK_ERROR;
    }

    *size = ftell(the_task_file);
    if(*size < 0)
    {
        return FTELL_ERROR;
    }

    check_error = fseek(the_task_file, 0, SEEK_SET);
    if(check_error != 0)
    {
        return FSEEK_ERROR;
    }

    return NO_ERROR;
}

ErrorNumbers treeDump(FILE* log_file, Node* root, const char* func_name, Node* new_node)
{
    CHECK_NULL_ADDR_ERROR(log_file,  NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(root,      NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(func_name, NULL_ADDRESS_ERROR);

    ErrorNumbers check_error;

    fprintf(log_file, "<h2>Dump is called from the function %s </h2>\n", func_name);

    fprintf(log_file, "root = [%p]\n", root);
    fprintf(log_file, "root->data = %d; [%p]\n", root->type, &root->type);

    if(root->type == NUM)
    {
        fprintf(log_file, "root->value = %lf; [%p]\n", root->value.numeral, &root->value.numeral);
    }
    else if(root->type == VAR)
    {
        fprintf(log_file, "root->value = %d; [%p]\n", root->value.variable, &root->value.variable);
    }
    else if(root->type == OP)
    {
        fprintf(log_file, "root->value = %d; [%p]\n", root->value.operation, &root->value.operation);
    }

    fprintf(log_file, "root->left = [%p]\n", root->left);
    fprintf(log_file, "root->right = [%p]\n", root->right);
    fprintf(log_file, "\n");

    CHECK_ERROR(createGraf(log_file, root, new_node));

    return check_error;
}

ErrorNumbers createGraf(FILE* log_file, Node* node, Node* new_node)
{
    CHECK_NULL_ADDR_ERROR(log_file, NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(node,     NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = NO_ERROR;

    static int counter = 0;

    const int FILE_NAME_SIZE = 100;
    char file_name[FILE_NAME_SIZE] = {};
    char command[FILE_NAME_SIZE] = {};

    sprintf(file_name, "image/Graf%d.txt", counter);

    FILE* file_to_write = NULL;
    CHECK_ERROR(openFile(&file_to_write, file_name, OPEN_FILE_IN_RECORDING_MODE));

    fprintf(file_to_write, "digraph\n");
    fprintf(file_to_write, "{\n");

    fprintf(file_to_write, "rankdir = TB;\n");

    fprintf(file_to_write, "{\n");

    CHECK_ERROR(buildAllNodes(node, file_to_write, new_node));

    fprintf(file_to_write, "}\n");

    fprintf(file_to_write, "}\n");

    fclose(file_to_write);

    sprintf(file_name, "image/Graf%d", counter);

    fprintf(log_file, "<img src = \"%s.png\" width = \"1400\">", file_name);

    sprintf(command, "dot %s.txt -T png -o %s.png", file_name, file_name);

    system(command);

    counter += 1;

    return check_error;
}

ErrorNumbers buildAllNodes(Node* node, FILE* file_to_write, Node* new_node)
{
    CHECK_NULL_ADDR_ERROR(node,          NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(file_to_write, NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = NO_ERROR;

    if(node->left != 0)
    {
        CHECK_ERROR(buildAllNodes(node->left, file_to_write, new_node));
    }
    if(node->right != 0)
    {
        CHECK_ERROR(buildAllNodes(node->right, file_to_write, new_node));
    }

    fprintf(file_to_write, "_%p[shape = record, style = \"filled\" fillcolor = \"", node);

    if(new_node == node)
    {
        fprintf(file_to_write, "#b0ffb0");
    }
    else
    {
        fprintf(file_to_write, "#bbffff");
    }

    if(node->left != NULL || node->right != NULL)
    {
        fprintf(file_to_write, "\", label = \" { address = %p | ", node);
    }
    else
    {
        fprintf(file_to_write, "\", label = \" { address = %p | ", node);
    }

    switch(node->type)
    {
        case NUM:
        {
            fprintf(file_to_write, "type = NUM | value = %.2lf | ", node->value.numeral);
            break;
        }
        case VAR:
        {
            fprintf(file_to_write, "type = VAR | value = %c | ", node->value.variable);
            break;
        }
        case OP:
        {
            fprintf(file_to_write, "type = OP | value = %c | ", node->value.operation);
            break;
        }
        case POISON_TYPE:
        {
            check_error = TYPE_ERROR;
        }
        default:
        {
            check_error = TYPE_ERROR;
        }
    }

    if(node->left != NULL)
    {
        fprintf(file_to_write, "{ <_l_%p> left = %p |", node->left, node->left);
    }
    else
    {
        fprintf(file_to_write, "{ left = NULL |");
    }

    if(node->right != NULL)
    {
        fprintf(file_to_write, " <_r_%p> right = %p }} \"]\n", node->right, node->right);
    }
    else
    {
        fprintf(file_to_write, " right = NULL }} \"]\n");
    }

    if(node->left != NULL)
    {
        fprintf(file_to_write, "_%p:<_l_%p>->_%p\n", node, node->left, node->left);
    }
    if(node->right != NULL)
    {
        fprintf(file_to_write, "_%p:<_r_%p>->_%p\n", node, node->right, node->right);
    }

    return check_error;
}
