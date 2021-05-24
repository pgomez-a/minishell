#ifndef PROMPT_H
# define PROMPT_H

# include "./libft/libft.h"

typedef struct s_cmd {
	char	*tot;
	char	*cmand;
	char	*param;
	char	*argum;
	int	error;
}	t_cmd;

/* get_command.c */
int	set_command(char *str, t_cmd *elem);

/* ft_utils */
void	clear_cmand_struct(t_cmd *elem);

#endif
