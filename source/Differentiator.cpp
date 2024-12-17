#include "Differentiator.h"
#include "WorkWithLogFile.h"
#include "ErrorHandler.h"
#include "ReadFile.h"
#include "DoDiff.h"
#include "Simplify.h"
#include "WriteFile.h"


int main(const int argc, const char** argv)
{
    const int _NUMBERS_OF_ARGUMENTS = 4;
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

    ReturnValue task = recursiveDescent(task_buffer);
    if(task.error != NO_ERROR)
    {
        errorHandler(task.error, __PRETTY_FUNCTION__);
        return task.error;
    }

    CHECK_ERROR(treeDump(log_file, task.node, __PRETTY_FUNCTION__, NULL));

    ReturnValue answer = diff(log_file, task.node);
    if(answer.error != NO_ERROR)
    {
        errorHandler(answer.error, __PRETTY_FUNCTION__);
        return answer.error;
    }

    CHECK_ERROR(treeDump(log_file, answer.node, __PRETTY_FUNCTION__, NULL));

    answer = simplifyExpression(log_file, answer.node);
    if(answer.error != NO_ERROR)
    {
        errorHandler(answer.error, __PRETTY_FUNCTION__);
        return answer.error;
    }

    CHECK_ERROR(treeDump(log_file, answer.node, __PRETTY_FUNCTION__, NULL));

    FILE* file_to_write = NULL;
    CHECK_ERROR(openFile(&file_to_write, argv[3], OPEN_FILE_IN_RECORDING_MODE));
    CHECK_ERROR(writeAnswer(log_file, file_to_write, task.node, answer.node))

    CHECK_ERROR(treeDtor(log_file, answer.node));
    CHECK_ERROR(treeDtor(log_file, task.node));

    free(task_buffer);
    fclose(file_to_write);
    fclose(log_file);

    printf("DONE\n");

    return check_error;
}
