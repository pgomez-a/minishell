#include "prompt.h"

static int	check_valid_command(char *str)
{
	int	verif;

	verif = ft_strncmp(str, "echo", ft_strlen(str));
	if (verif == 0)
		return 0;
	verif = ft_strncmp(str, "cd", ft_strlen(str));
	if (verif == 0)
		return 0;
	verif = ft_strncmp(str, "pwd", ft_strlen(str));
	if (verif == 0)
		return 0;
	verif = ft_strncmp(str, "export", ft_strlen(str));
	if (verif == 0)
		return 0;
	verif = ft_strncmp(str, "unset", ft_strlen(str));
	if (verif == 0)
		return 0;
	verif = ft_strncmp(str, "env", ft_strlen(str));
	if (verif == 0)
		return 0;
	verif = ft_strncmp(str, "exit", ft_strlen(str));
	if (verif == 0)
		return 0;
	ft_printf("koala: command not found: %s\n", str);
	return (1);

}

int	set_command(char *str, t_cmd *elem)
{
	int	count;
	int	verif;

	verif = 0;
	count = 0;
	while (str[count] && str[count] != ' ')
		count++;
	if (str[count] != '\0')
		verif = 1;
	str[count] = '\0';
	elem->cmand = ft_strdup(str);
	if (verif == 1)
		elem->argum = ft_strdup(str + count + 1);
	verif = check_valid_command(elem->cmand);
	return (verif);
}
