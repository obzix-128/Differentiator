#include "Differentiator.h"
#include "WorkWithLogFile.h"
#include "ErrorHandler.h"
#include "ReadFile.h"


int main(const int argc, const char** argv)
{
    const int _NUMBERS_OF_ARGUMENTS = 3;
    if(argc != _NUMBERS_OF_ARGUMENTS)
    {
        errorHandler(NUMBER_OF_ARG_ERROR, __PRETTY_FUNCTION__);
        return NUMBER_OF_ARG_ERROR;
    }

    ErrorNumbers check_error = NO_ERROR;

    FILE* log_file = NULL;
    CHECK_ERROR(openFile(&log_file, argv[1], OPEN_FILE_IN_RECORDING_MODE));
    fprintf(log_file, "<pre>\n");

    char* task_buffer = NULL;
    CHECK_ERROR(readFile(argv[2], &task_buffer));

    ReturnValue value = getG(task_buffer);
    if(value.error != NO_ERROR)
    {
        errorHandler(value.error, __PRETTY_FUNCTION__);
        return value.error;
    }

    CHECK_ERROR(treeDump(log_file, value.node, __PRETTY_FUNCTION__, NULL));

    CHECK_ERROR(treeDtor(log_file, value.node));

    free(task_buffer);
    fclose(log_file);

    printf("DONE\n");

    return check_error;
}
