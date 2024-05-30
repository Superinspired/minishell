#include "../minishell.h"

void	expect(t_minishell *minishell, void *ptr, char *message)
{
	if (!ptr)
	{
		minishell_destroy(minishell);
		perror(message);
		exit(EXIT_FAILURE);
	}
}