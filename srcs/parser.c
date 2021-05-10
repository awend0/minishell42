#include "../includes/minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t');
}

t_cmdtable	parser(char *line)
{
	t_cmdtable	*table;
	
	while (ft_isspace(*line))
		line++;
	while (*line)
	{
		
	}
		
}
