#include "Differentiator.h"
#include "WorkWithLogFile.h"
#include "ErrorHandler.h"


int main(const int argc, const char** argv)
{
    const int _NUMBERS_OF_ARGUMENTS = 2;
    if(argc != _NUMBERS_OF_ARGUMENTS)
    {
        errorHandler(NUMBER_OF_ARG_ERROR, __PRETTY_FUNCTION__);
        return NUMBER_OF_ARG_ERROR;
    }

    ErrorNumbers check_error = NO_ERROR;

    FILE* log_file = NULL;
    CHECK_ERROR(openFile(&log_file, argv[1], OPEN_FILE_IN_RECORDING_MODE));
    fprintf(log_file, "<pre>\n");

    struct Node root = {};
    struct Node node_1 = {};
    struct Node node_2 = {};

    root.type = OP;
    root.value.operation = ADD;
    root.left = &node_1;
    root.right = &node_2;

    node_1.type = NUM;
    node_2.type = NUM;
    node_1.value.numeral = 88;
    node_2.value.numeral = 99;

    CHECK_ERROR(treeDump(log_file, &root, __PRETTY_FUNCTION__, NULL));

    fclose(log_file);

    return check_error;
}
