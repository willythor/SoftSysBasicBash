typedef enum {QUIT, CD, LS} inputs;
int getCommands(
    char *userInput,
    char **tokens,
    int numtokens,
    char **commands
    );
