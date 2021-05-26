#ifndef QUEUE_H
# define QUEUE_H

typedef struct s_que {
	char		*line;
	struct s_que	*next;
}	t_que;

t_data	*ini_que(char *line);
void	push_que(char *line, t_que **que);
char	*pop_que(t_que **que);

#endif
