#include "../../includes/minishell.h"

int	main(void)
{
    char	*input;
    char	*removed_quotes;

    // "ls"
    input = strdup("\"ls\"");
    removed_quotes = remove_quotes(input);
    assert(strcmp(removed_quotes, "ls") == 0);
    free(removed_quotes);

    // "'ls'"
    input = strdup("\"\'ls\'\"");
    removed_quotes = remove_quotes(input);
    assert(strcmp(removed_quotes, "\'ls\'") == 0);
    free(removed_quotes);

    // ls
    input = strdup("ls");
    removed_quotes = remove_quotes(input);
    assert(strcmp(removed_quotes, "ls") == 0);
    free(removed_quotes);

    // "ls"'ls'
    input = strdup("\"ls\"\'ls\'");
    removed_quotes = remove_quotes(input);
    assert(strcmp(removed_quotes, "lsls") == 0);
    free(removed_quotes);

    // "ls"'ls'"ls"
    input = strdup("\"ls\"\'ls\'\"ls\"");
    removed_quotes = remove_quotes(input);
    assert(strcmp(removed_quotes, "lslsls") == 0);
    free(removed_quotes);

    // 'ls'"ls"'ls'
    input = strdup("\'ls\'\"ls\"\'ls\'");
    removed_quotes = remove_quotes(input);
    assert(strcmp(removed_quotes, "lslsls") == 0);
    free(removed_quotes);

    return (0);
}
