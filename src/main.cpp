#include <conio.h>
#include <stdlib.h>
#include "hstr.h"
#include "Token.h"
#include "Lexer.h"

FILE* readFile(const char* src)
{
    FILE* file = fopen(src, "r");

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
    printf("Opening file...\n");
    FILE* file = readFile("res/script.es");

    Lexer lexer(file);
    List<Token>* tokens = lexer.make_tokens();
    fclose(file);

    for (int i = 0; i < tokens->length; i++)
    {
        Token* tok = tokens->get(i);
        printf("Type: ");
        printf("%s", TokenTypeStrings[(int) tok->type]);

        if (tok->value)
        {
            printf("\nValue: ");
            printf(tok->value);
        }

        printf("\n\n");
    }

    getch();

    return 0;
}
