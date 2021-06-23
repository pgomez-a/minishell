#include "../koala.h"

static void	multiple_expansion(int count, char *copy, char **result)
{
	char	*env;

	env = ft_strdup("");
	while (copy[count])
	{
		if (copy[count] == '$')
		{
			if (getenv(env))
				do_join(0, result, getenv(env));
			free(env);
			env = ft_strdup("");
		}
		else
			do_join(1, &env, ft_charstr(copy[count]));
		count++;
	}
	if (getenv(env))
		do_join(0, result, getenv(env));
	free(env);
}

static void	manage_expansion(t_que **var)
{
	char	*copy;
	char	*result;
	int	count;

	copy = ft_strdup((*var)->line);
	count = 0;
	while (copy[count] != '$')
		count++;
	copy[count++] = '\0';
	result = ft_strdup(copy);
	multiple_expansion(count, copy, &result);
	free((*var)->line);
	(*var)->line = ft_strdup(result);
	free(result);
	free(copy);
}

static void	expand_cmds(t_cmd **tpar)
{
	t_que	*tque;

	if ((*tpar)->cmd)
	{
		tque = (*tpar)->cmd;
		while (tque)
		{
			if (tque->op != 2 && ft_strchr(tque->line, '$'))
				manage_expansion(&tque);
			tque = tque->next;
		}
	}
}

static void	expand_reds(t_cmd **tpar)
{
	t_que	*tque;

	if ((*tpar)->red)
	{
		tque = (*tpar)->red;
		while (tque)
		{
			if (tque->op > 0 && ft_strchr(tque->line, '$'))
				manage_expansion(&tque);
			tque = tque->next;
		}
	}
}

void	call_env(t_cmd **par)
{
	t_cmd	*tpar;

	if (*par)
	{
		tpar = *par;
		while (tpar)
		{
			expand_cmds(&tpar);
			expand_reds(&tpar);
			tpar = tpar->next;
		}
	}
}
