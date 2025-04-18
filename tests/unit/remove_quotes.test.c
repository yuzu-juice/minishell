#include "../../includes/minishell.h"

int	main(void)
{
	char	*removed_quotes;

	// "ls"
	removed_quotes = remove_quotes("\"ls\"");
	assert(strcmp(removed_quotes, "ls") == 0);

	// "'ls'"
	removed_quotes = remove_quotes("\"\'ls\'\"");
	assert(strcmp(removed_quotes, "\'ls\'") == 0);

    // ls
	removed_quotes = remove_quotes("ls");
	assert(strcmp(removed_quotes, "ls") == 0);

    // "ls"'ls'
	removed_quotes = remove_quotes("\"ls\"\'ls\'");
	assert(strcmp(removed_quotes, "lsls") == 0);

    // "ls"'ls'"ls"
	removed_quotes = remove_quotes("\"ls\"\'ls\'\"ls\"");
	assert(strcmp(removed_quotes, "lslsls") == 0);

    // 'ls'"ls"'ls'
	removed_quotes = remove_quotes("\'ls\'\"ls\"\'ls\'");
	assert(strcmp(removed_quotes, "lslsls") == 0);

	return (0);
}
