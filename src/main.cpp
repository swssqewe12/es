#include <stdlib.h>
#include <time.h>
#include "List.h"
#include "Token.h"
#include "Lexer.h"
#include "Node.h"
#include "Parser.h"
#include "Interpreter.h"

FILE* openFile(const char* src, const char* mode)
{
    FILE* file = fopen(src, mode);

    if (file == NULL)
    {
        printf("Failed to open ");
        printf(src);
        printf(": ");
        perror("");
        exit(EXIT_FAILURE);
    }

    return file;
}

int main()
{
    time_t start_time, end_time;
    double diff_time;

    system("@cls||clear");
    printf("------------------\n");
    printf("Opening file...\n");
    FILE* file = openFile("res/script.es", "r");

    time(&start_time);
    printf("Lexing...\n");
    Lexer lexer(file);
    List<Token> tokens;
    lexer.make_tokens(tokens);
    fclose(file);

    printf("Parsing...\n");
    Parser parser(tokens);
    ProgramTree* tree = parser.parse();

    time(&end_time);
    diff_time = difftime(end_time, start_time);
    printf("DONE. (%fs)\n", diff_time);
    printf("------------------\n");

    Interpreter interpreter;
    interpreter.visit_ProgramTree(tree);

    return 0;
}
