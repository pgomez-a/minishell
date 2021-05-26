/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 08:42:38 by pgomez-a          #+#    #+#             */
/*   Updated: 2021/05/26 08:56:20 by pgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H

# include "../libft/libft.h"

typedef struct s_que {
	char			*line;
	struct s_que	*next;
}	t_que;

/** queue.c **/

void	push_que(char *line, t_que **que);
char	*pop_que(t_que **que);

#endif
