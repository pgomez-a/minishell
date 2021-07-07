#include "../../inc/koala.h"

static void	multiple_expansion(int count, char *copy, char **result, char **envp)
{
	char	*env;

	env = ft_strdup("");
	while (copy[count])
	{
		if (copy[count] == '$')
		{
			if (env[0] == '\0')
				do_join(1, result, ft_charstr('$'));
			else if (koala_getenv(env, envp))
				do_join(0, result, koala_getenv(env, envp));
			free(env);
			env = ft_strdup("");
		}
		else
			do_join(1, &env, ft_charstr(copy[count]));
		count++;
	}
	if (env[0] == '\0')
		do_join(1, result, ft_charstr('$'));
	else if (koala_getenv(env, envp))
		do_join(0, result, koala_getenv(env, envp));
	free(env);
}

static void	manage_expansion(t_que **var, char **envp)
{
	char	*copy;
	char	*result;
	int		count;

	copy = ft_strdup((*var)->line);
	count = 0;
	while (copy[count] != '$')
		count++;
	copy[count++] = '\0';
	result = ft_strdup(copy);
	multiple_expansion(count, copy, &result, envp);
	free((*var)->line);
	(*var)->line = ft_strdup(result);
	free(result);
	free(copy);
}

static void	expand_cmds(t_cmd **tpar, char **envp)
{
	t_que	*tque;

	if ((*tpar)->cmd)
	{
		tque = (*tpar)->cmd;
		while (tque)
		{
			if (tque->op != 2 && ft_strchr(tque->line, '$'))
				manage_expansion(&tque, envp);
			tque = tque->next;
		}
	}
}

static void	expand_reds(t_cmd **tpar, char **envp)
{
	t_que	*tque;

	if ((*tpar)->red)
	{
		tque = (*tpar)->red;
		while (tque)
		{
			if (tque->op > 0 && ft_strchr(tque->line, '$'))
				manage_expansion(&tque, envp);
			tque = tque->next;
		}
	}
}

void	call_env(t_cmd **par, char **envp)
{
	t_cmd	*tpar;

	if (*par)
	{
		tpar = *par;
		while (tpar)
		{
			expand_cmds(&tpar, envp);
			expand_reds(&tpar, envp);
			tpar = tpar->next;
		}
	}
}
