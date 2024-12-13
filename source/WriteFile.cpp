#include "WriteFile.h"


ErrorNumbers writeAnswer(FILE* log_file, FILE* file_to_write, Node* root_of_task, Node* root_of_answer)
{
    CHECK_NULL_ADDR_ERROR(log_file,       NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(file_to_write,  NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(root_of_task,   NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(root_of_answer, NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = NO_ERROR;

    CHECK_ERROR(printTitle(log_file, file_to_write));

    fprintf(file_to_write, "Возьмём производную следующей функции:\n");
    fprintf(file_to_write, "\\newline\n");
    fprintf(file_to_write, "$\n");
    CHECK_ERROR(writeToFile(log_file, file_to_write, root_of_task));
    fprintf(file_to_write, "$\n");
    fprintf(file_to_write, "\\newline\n");

    fprintf(file_to_write, "В силу тривиальности задачи приведём только ответ:\n");
    fprintf(file_to_write, "\\newline\n");
    fprintf(file_to_write, "$\n");
    CHECK_ERROR(writeToFile(log_file, file_to_write, root_of_answer));
    fprintf(file_to_write, "$\n");

    CHECK_ERROR(printEnd(log_file, file_to_write));

    return check_error;
}

ErrorNumbers printTitle(FILE* log_file, FILE* file_to_write)
{
    CHECK_NULL_ADDR_ERROR(log_file,      NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(file_to_write, NULL_ADDRESS_ERROR);

    fprintf(file_to_write, "\\documentclass[12pt, a4paper]{article}\n");
    fprintf(file_to_write, "\\usepackage[utf8]{inputenc}\n");
    fprintf(file_to_write, "\\usepackage[english, russian]{babel}\n");
    fprintf(file_to_write, "\n");
    fprintf(file_to_write, "\\usepackage{amsmath} \n");
    fprintf(file_to_write, "\\usepackage{graphicx} %% Required for inserting images\n");
    fprintf(file_to_write, "\\graphicspath{ {images/} }\n");
    fprintf(file_to_write, "\n");
    fprintf(file_to_write, "\\title{Как брать производную? Гайд для чайников.}\n");
    fprintf(file_to_write, "\n");
    fprintf(file_to_write, "\\begin{document}\n");
    fprintf(file_to_write, "\n");
    fprintf(file_to_write, "\\maketitle\n");
    fprintf(file_to_write, "\n");
    fprintf(file_to_write, "\\newpage\n");

    return NO_ERROR;
}

ErrorNumbers printEnd(FILE* log_file, FILE* file_to_write)
{
    CHECK_NULL_ADDR_ERROR(log_file,      NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(file_to_write, NULL_ADDRESS_ERROR);

    fprintf(file_to_write, "\n");
    fprintf(file_to_write, "\\end{document}\n");
    fprintf(file_to_write, "\n");

    return NO_ERROR;
}

ErrorNumbers writeToFile(FILE* log_file, FILE* file_to_write, Node* node)
{
    CHECK_NULL_ADDR_ERROR(log_file,      NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(file_to_write, NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(node,          NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = NO_ERROR;

    switch(node->type)
    {
        case NUM:
        {
            fprintf(file_to_write, "%lg", node->value.numeral);
            break;
        }
        case VAR:
        {
            fprintf(file_to_write, "%c", node->value.variable);
            break;
        }
        case OP:
        {
            CHECK_ERROR(writeOperation(log_file, file_to_write, node));
            break;
        }
        case POISON_TYPE:
        {
            check_error = TYPE_ERROR;
            return check_error;
        }
        default:
        {
            check_error = TYPE_ERROR;
            return check_error;
        }
    }

    return check_error;
}

ErrorNumbers writeOperation(FILE* log_file, FILE* file_to_write, Node* node)
{
    CHECK_NULL_ADDR_ERROR(log_file,      NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(file_to_write, NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(node,          NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = NO_ERROR;

    switch(node->value.operation)
    {
        case ADD:
        {
            fprintf(file_to_write, "(");

            CHECK_ERROR(writeToFile(log_file, file_to_write, node->left));

            fprintf(file_to_write, " + ");

            CHECK_ERROR(writeToFile(log_file, file_to_write, node->right));

            fprintf(file_to_write, ")");

            break;
        }
        case SUB:
        {
            fprintf(file_to_write, "(");

            CHECK_ERROR(writeToFile(log_file, file_to_write, node->left));

            fprintf(file_to_write, " - ");

            CHECK_ERROR(writeToFile(log_file, file_to_write, node->right));

            fprintf(file_to_write, ")");

            break;
        }
        case MUL:
        {
            fprintf(file_to_write, "(");

            CHECK_ERROR(writeToFile(log_file, file_to_write, node->left));

            fprintf(file_to_write, " \\cdot ");

            CHECK_ERROR(writeToFile(log_file, file_to_write, node->right));

            fprintf(file_to_write, ")");

            break;
        }
        case DIV:
        {
            fprintf(file_to_write, "\\frac{(");

            CHECK_ERROR(writeToFile(log_file, file_to_write, node->left));

            fprintf(file_to_write, ")}{(");

            CHECK_ERROR(writeToFile(log_file, file_to_write, node->right));

            fprintf(file_to_write, ")}");

            break;
        }
        case POW:
        {
            fprintf(file_to_write, "(");

            CHECK_ERROR(writeToFile(log_file, file_to_write, node->left));

            fprintf(file_to_write, ")^{");

            CHECK_ERROR(writeToFile(log_file, file_to_write, node->right));

            fprintf(file_to_write, "}");

            break;
        }
        case SIN:
        {
            fprintf(file_to_write, "\\sin{(");

            CHECK_ERROR(writeToFile(log_file, file_to_write, node->left));

            fprintf(file_to_write, ")}");

            break;
        }
        case COS:
        {
            fprintf(file_to_write, "\\cos{(");

            CHECK_ERROR(writeToFile(log_file, file_to_write, node->left));

            fprintf(file_to_write, ")}");

            break;
        }
        case TAN:
        {
            fprintf(file_to_write, "\\tan{(");

            CHECK_ERROR(writeToFile(log_file, file_to_write, node->left));

            fprintf(file_to_write, ")}");

            break;
        }
        case EXP:
        {
            fprintf(file_to_write, "\\exp{(");

            CHECK_ERROR(writeToFile(log_file, file_to_write, node->left));

            fprintf(file_to_write, ")}");

            break;
        }
        case LN:
        {
            fprintf(file_to_write, "\\ln{(");

            CHECK_ERROR(writeToFile(log_file, file_to_write, node->left));

            fprintf(file_to_write, ")}");

            break;
        }
        case LOG:
        {
            fprintf(file_to_write, "\\log_{(");

            CHECK_ERROR(writeToFile(log_file, file_to_write, node->left));

            fprintf(file_to_write, ")}{(");

            CHECK_ERROR(writeToFile(log_file, file_to_write, node->right));

            fprintf(file_to_write, ")}");

            break;
        }
        case POISON:
        {
            check_error = TYPE_ERROR;
            return check_error;
            break;
        }
        default:
        {
            check_error = TYPE_ERROR;
            return check_error;
            break;
        }
    }

    return check_error;
}
