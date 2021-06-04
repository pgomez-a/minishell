#ifndef LISTS_H
# define LISTS_H

# include "../libft/libft.h"

typedef struct s_dlist
{
	struct s_dlist	*previous;
	char			*content;
	struct s_dlist	*next;
}	t_dlist;

t_dlist	*ft_dlstnew(char *content);

void	ft_dlstadd_front(t_dlist **alst, t_dlist *new);

void	ft_dlstclear(t_dlist **lst, void (*del)(void *));

t_dlist	*ft_dlstlast(t_dlist *lst);

t_dlist	*ft_dlstfirst(t_dlist *lst);

t_dlist	*ft_dlstmap(t_dlist *lst, char *(*f)(const char *), void (*del)(void *));

#endif
