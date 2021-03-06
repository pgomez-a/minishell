#include "dlists.h"

void	ft_dlstadd_back(t_dlist **lst, t_dlist *new)
{
	t_dlist	*last;

	last = ft_dlstlast(*lst);
	if (*lst)
	{
		last->next = new;
		new->previous = last;
	}
	else
		*lst = new;
}

t_dlist	*ft_dlstmap(t_dlist *lst, char *(*f)(const char *), void (*del)(void *))
{
	t_dlist	*newlst;
	t_dlist	*lstcpy;

	lstcpy = 0;
	lst = ft_dlstfirst(lst);
	while (lst)
	{
		newlst = ft_dlstnew((*f)(lst->content));
		if (!newlst)
		{
			ft_dlstclear(&lstcpy, del);
			return (0);
		}
		lst = lst->next;
		ft_dlstadd_back(&lstcpy, newlst);
	}
	return (lstcpy);
}

void	ft_dlstdelone(t_dlist **lst, void (*del)(void *))
{
	t_dlist	*tmp;

	if (!(*lst))
		return ;
	if ((*lst)->previous)
		((*lst)->previous)->next = (*lst)->next;
	if ((*lst)->next)
		((*lst)->next)->previous = (*lst)->previous;
	(*del)((*lst)->content);
	tmp = *lst;
	if ((*lst)->next)
		*lst = (*lst)->next;
	else
		*lst = (*lst)->previous;
	free(tmp);
}
