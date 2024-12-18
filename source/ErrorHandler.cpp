#include "ErrorHandler.h"


ErrorNumbers errorHandler(ErrorNumbers error, const char* func_name)
{
    fprintf(stderr, "%s\n", func_name);

    switch(error)
    {
        case NO_ERROR:
        {
            fprintf(stderr, "No errors were found\n");
            break;
        }
        case NULL_ADDRESS_ERROR:
        {
            fprintf(stderr, "ERROR: a null address was detected\n");
            break;
        }
        case CALLOC_ERROR:
        {
            fprintf(stderr, "ERROR: calloc\n");
            break;
        }
        case NUMBER_OF_ARG_ERROR:
        {
            fprintf(stderr, "ERROR: Incorrect number of arguments\n");
            break;
        }
        case OPEN_ERROR:
        {
            fprintf(stderr, "ERROR: File not open\n");
            break;
        }
        case FSEEK_ERROR:
        {
            fprintf(stderr, "ERROR: An error occurred in the fseek function\n");
            break;
        }
        case FTELL_ERROR:
        {
            fprintf(stderr, "ERROR: An error occurred in the ftell function\n");
            break;
        }
        case SYNTAX_ERROR:
        {
            fprintf(stderr, "ERROR: There is a syntax error in the task\n");
            break;
        }
        case TYPE_ERROR:
        {
            fprintf(stderr, "ERROR: An unknown node type has been detected\n");
            break;
        }
        case DIFF_POWER_ERROR:
        {
            fprintf(stderr, "ERROR: An error occurred in the diffPower function\n");
            break;
        }
        case UNCERTAINTY_ERROR:
        {
            fprintf(stderr, "ERROR: Arithmetic calculations led to uncertainty\n");
            break;
        }
        default:
        {
            fprintf(stderr, "Unknown error\n");
            break;
        }
    }

    return NO_ERROR;
}
