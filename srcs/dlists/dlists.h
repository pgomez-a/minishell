#ifndef DLISTS_H
# define DLISTS_H

# include "../libft/libft.h"

typedef struct s_dlist
{
	struct s_dlist	*previous;
	char			*content;
	struct s_dlist	*next;
}	t_dlist;

t_dlist	*ft_dlstnew(void *content);

void	ft_dlstadd_front(t_dlist **alst, t_dlist *new);

void	ft_dlstclear(t_dlist **lst, void (*del)(void *));

t_dlist	*ft_dlstlast(t_dlist *lst);

t_dlist	*ft_dlstfirst(t_dlist *lst);

t_dlist	*ft_dlstmap(t_dlist *lst, char *(*f)(const char *),
			void (*del)(void *));

void	ft_dlstadd_back(t_dlist **lst, t_dlist *new);

void	ft_dlstdelone(t_dlist **lst, void (*del)(void *));

#endif
