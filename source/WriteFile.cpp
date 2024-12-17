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
            CHECK_ERROR(writeNumeral(log_file, file_to_write, node));
            break;
        }
        case VAR:
        {
            CHECK_ERROR(writeVariable(log_file, file_to_write, node));
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

ErrorNumbers writeNumeral(FILE* log_file, FILE* file_to_write, Node* node)
{
    CHECK_NULL_ADDR_ERROR(log_file,      NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(file_to_write, NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(node,          NULL_ADDRESS_ERROR);

    if(node->value.numeral < 0)
    {
        fprintf(file_to_write, "(%lg)", node->value.numeral);
    }
    else
    {
        fprintf(file_to_write, "%lg", node->value.numeral);
    }

    return NO_ERROR;
}

ErrorNumbers writeVariable(FILE* log_file, FILE* file_to_write, Node* node)
{
    CHECK_NULL_ADDR_ERROR(log_file,      NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(file_to_write, NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(node,          NULL_ADDRESS_ERROR);

    fprintf(file_to_write, "%c", node->value.variable);

    return NO_ERROR;
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
            CHECK_ERROR(writeAdd(log_file, file_to_write, node));
            break;
        }
        case SUB:
        {
            CHECK_ERROR(writeSub(log_file, file_to_write, node));
            break;
        }
        case MUL:
        {
            CHECK_ERROR(writeMul(log_file, file_to_write, node));
            break;
        }
        case DIV:
        {
            CHECK_ERROR(writeDiv(log_file, file_to_write, node));
            break;
        }
        case POW:
        {
            CHECK_ERROR(writePow(log_file, file_to_write, node));
            break;
        }
        case SIN:
        {
            CHECK_ERROR(writeSin(log_file, file_to_write, node));
            break;
        }
        case COS:
        {
            CHECK_ERROR(writeCos(log_file, file_to_write, node));
            break;
        }
        case TAN:
        {
            CHECK_ERROR(writeTan(log_file, file_to_write, node));
            break;
        }
        case EXP:
        {
            CHECK_ERROR(writeExp(log_file, file_to_write, node));
            break;
        }
        case LN:
        {
            CHECK_ERROR(writeLn(log_file, file_to_write, node));
            break;
        }
        case LOG:
        {
            CHECK_ERROR(writeLog(log_file, file_to_write, node));
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

ErrorNumbers writeAdd(FILE* log_file, FILE* file_to_write, Node* node)
{
    CHECK_NULL_ADDR_ERROR(log_file,      NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(file_to_write, NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(node,          NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = NO_ERROR;

    CHECK_ERROR(writeToFile(log_file, file_to_write, node->left));

    fprintf(file_to_write, " + ");

    CHECK_ERROR(writeToFile(log_file, file_to_write, node->right));

    return check_error;
}

ErrorNumbers writeSub(FILE* log_file, FILE* file_to_write, Node* node)
{
    CHECK_NULL_ADDR_ERROR(log_file,      NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(file_to_write, NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(node,          NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = NO_ERROR;

    CHECK_ERROR(writeToFile(log_file, file_to_write, node->left));

    fprintf(file_to_write, " - ");

    CHECK_ERROR(writeToFile(log_file, file_to_write, node->right));

    return check_error;
}

ErrorNumbers writeMul(FILE* log_file, FILE* file_to_write, Node* node)
{
    CHECK_NULL_ADDR_ERROR(log_file,      NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(file_to_write, NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(node,          NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = NO_ERROR;

    if(node->left->type == OP &&
       (node->left->value.operation == ADD || //TODO? Сдвинуть на пробел влево?
        node->left->value.operation == SUB))
    {
        fprintf(file_to_write, "(");
        CHECK_ERROR(writeToFile(log_file, file_to_write, node->left));
        fprintf(file_to_write, ")");
    }
    else
    {
        CHECK_ERROR(writeToFile(log_file, file_to_write, node->left));
    }

    fprintf(file_to_write, " \\cdot ");

    if(node->right->type == OP &&
       (node->right->value.operation == ADD ||
        node->right->value.operation == SUB))
    {
        fprintf(file_to_write, "(");
        CHECK_ERROR(writeToFile(log_file, file_to_write, node->right));
        fprintf(file_to_write, ")");
    }
    else
    {
        CHECK_ERROR(writeToFile(log_file, file_to_write, node->right));
    }

    return check_error;
}

ErrorNumbers writeDiv(FILE* log_file, FILE* file_to_write, Node* node)
{
    CHECK_NULL_ADDR_ERROR(log_file,      NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(file_to_write, NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(node,          NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = NO_ERROR;

    fprintf(file_to_write, "\\frac{");
    CHECK_ERROR(writeToFile(log_file, file_to_write, node->left));
    fprintf(file_to_write, "}{");
    CHECK_ERROR(writeToFile(log_file, file_to_write, node->right));
    fprintf(file_to_write, "}");

    return check_error;
}

ErrorNumbers writePow(FILE* log_file, FILE* file_to_write, Node* node)
{
    CHECK_NULL_ADDR_ERROR(log_file,      NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(file_to_write, NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(node,          NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = NO_ERROR;

    if(node->left->type == OP)
    {
        fprintf(file_to_write, "(");
        CHECK_ERROR(writeToFile(log_file, file_to_write, node->left));
        fprintf(file_to_write, ")");
    }
    else
    {
        CHECK_ERROR(writeToFile(log_file, file_to_write, node->left));
    }

    fprintf(file_to_write, "^{");
    CHECK_ERROR(writeToFile(log_file, file_to_write, node->right));
    fprintf(file_to_write, "}");

    return check_error;
}

ErrorNumbers writeSin(FILE* log_file, FILE* file_to_write, Node* node)
{
    CHECK_NULL_ADDR_ERROR(log_file,      NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(file_to_write, NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(node,          NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = NO_ERROR;

    fprintf(file_to_write, "\\sin{(");
    CHECK_ERROR(writeToFile(log_file, file_to_write, node->left));
    fprintf(file_to_write, ")}");

    return check_error;
}

ErrorNumbers writeCos(FILE* log_file, FILE* file_to_write, Node* node)
{
    CHECK_NULL_ADDR_ERROR(log_file,      NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(file_to_write, NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(node,          NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = NO_ERROR;

    fprintf(file_to_write, "\\cos{(");
    CHECK_ERROR(writeToFile(log_file, file_to_write, node->left));
    fprintf(file_to_write, ")}");

    return check_error;
}

ErrorNumbers writeTan(FILE* log_file, FILE* file_to_write, Node* node)
{
    CHECK_NULL_ADDR_ERROR(log_file,      NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(file_to_write, NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(node,          NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = NO_ERROR;

    fprintf(file_to_write, "\\tan{(");
    CHECK_ERROR(writeToFile(log_file, file_to_write, node->left));
    fprintf(file_to_write, ")}");

    return check_error;
}

ErrorNumbers writeExp(FILE* log_file, FILE* file_to_write, Node* node)
{
    CHECK_NULL_ADDR_ERROR(log_file,      NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(file_to_write, NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(node,          NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = NO_ERROR;

    fprintf(file_to_write, "\\exp{(");
    CHECK_ERROR(writeToFile(log_file, file_to_write, node->left));
    fprintf(file_to_write, ")}");

    return check_error;
}

ErrorNumbers writeLn(FILE* log_file, FILE* file_to_write, Node* node)
{
    CHECK_NULL_ADDR_ERROR(log_file,      NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(file_to_write, NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(node,          NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = NO_ERROR;

    fprintf(file_to_write, "\\ln{(");
    CHECK_ERROR(writeToFile(log_file, file_to_write, node->left));
    fprintf(file_to_write, ")}");

    return check_error;
}

ErrorNumbers writeLog(FILE* log_file, FILE* file_to_write, Node* node)
{
    CHECK_NULL_ADDR_ERROR(log_file,      NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(file_to_write, NULL_ADDRESS_ERROR);
    CHECK_NULL_ADDR_ERROR(node,          NULL_ADDRESS_ERROR);

    ErrorNumbers check_error = NO_ERROR;

    fprintf(file_to_write, "\\log_{");
    CHECK_ERROR(writeToFile(log_file, file_to_write, node->left));
    fprintf(file_to_write, "}{(");
    CHECK_ERROR(writeToFile(log_file, file_to_write, node->right));
    fprintf(file_to_write, ")}");

    return check_error;
}
