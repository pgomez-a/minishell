#include "dlists.h"

t_dlist	*ft_dlstnew(void *content)
{
	t_dlist	*lst;

	lst = (t_dlist *)ft_calloc(1, sizeof(t_dlist));
	if (!lst)
		return (0);
	lst->content = content;
	return (lst);
}

void	ft_dlstadd_front(t_dlist **alst, t_dlist *new)
{
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	*alst = ft_dlstfirst(*alst);
	(*alst)->previous = new;
	new->next = *alst;
	*alst = new;
}

void	ft_dlstclear(t_dlist **lst, void (*del)(void *))
{
	t_dlist	*dnext;

	*lst = ft_dlstfirst(*lst);
	while (*lst)
	{
		dnext = (*lst)->next;
		(*del)((*lst)->content);
		free(*lst);
		*lst = dnext;
	}
}

t_dlist	*ft_dlstlast(t_dlist *lst)
{
	t_dlist	*last;

	if (!lst)
		return (0);
	last = lst;
	while (last->next)
		last = last->next;
	return (last);
}

t_dlist	*ft_dlstfirst(t_dlist *lst)
{
	t_dlist	*first;

	if (!lst)
		return (0);
	first = lst;
	while (first->previous)
		first = first->previous;
	return (first);
}
