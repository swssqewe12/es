#include <conio.h>
#include "hstr.h"
#include "Token.h"
#include "Lexer.h"

int main()
{
    FILE* file = fopen("res\\script.txt", "r");
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
