#ifndef UTILS_H
# define UTILS_H

# include <errno.h>
# include "libft.h"

# define SUCCESS	0
# define ERROR 		1

# define PREVIOUS_HISTORY 1
# define NEXT_HISTORY 2
# define LAST_HISTORY 3

# define ESCAPED_CHAR		0b00000001

enum	e_separators
{
	NONE,
	PIPE,
	SEMICOLON,
	INPUT,
	TRUNC,
	APPEND,
	HEREDOC
};

typedef struct s_doubly_lst {
	char				*str;
	int					*type;
	int					flag;
	struct s_doubly_lst	*next;
	struct s_doubly_lst	*prev;
}				t_dlst;

typedef struct s_env
{
	size_t		size;
	char		**array;
}				t_env;

typedef struct s_all
{
	t_dlst			*lst_token;
	t_dlst			*shell_history;
	t_dlst			*ptr_history;
	t_dlst			*env;
	unsigned char	exit_status;
	int				next_operator;
	int				fd_in;
	int				fd_out;
	int				hist_iter;
	int				sigint_exit_status;
	char			*line;
	int				cursor_counter;
	int				sh_counter;
}				t_all;

void		*ft_realloc(void *ptr, size_t size);
void		ft_crash(const char *str);
void		*ft_malloc(size_t size);
int			ft_iswhitespace(int c);
char		*str_join_char(char *str, char ch);
t_dlst		*doubly_lst_append(t_dlst **lst, t_dlst *new);
t_dlst		*doubly_lstlast(t_dlst *lst);
t_dlst		*doubly_lst_new(char *str, int flag);
t_dlst		*doubly_lst_dup(t_dlst *head);
void		doubly_lst_merge_sort(t_dlst **head);
int			doubly_lst_size(t_dlst *lst);
void		doubly_lst_clear(t_dlst **lst);
void		doubly_lst_delete_element(t_dlst **lst);
int			free_all_exit(t_all *all, int error_code);
void		free_doble_array(char **array);
int			is_separator(t_dlst *ptr_token);
void		go_to_end_or_separator(t_dlst **ptr_token);
int			is_number(char *str);
int			next_operator(t_dlst *ptr_token);
int			is_pipe(t_dlst *ptr_token);
int			prev_operator(t_dlst *ptr_token);
void		init_fd(t_all *all);
void		close_fds(t_all *all);
void		close_fd(int *fd, int value);
int			myputchar(int nb);
int			last_token(t_dlst *ptr_token);
int			is_valid_variable_name(char *variable_name, char end_char);
int			is_last_token_escaped(t_dlst *ptr_token);
char		*ft_str_replace(char *dst, char *src, int dst_start, int dst_end);
void		print_promt(void);
void		free_char_and_null(char	**str);
void		doubly_lst_split(t_dlst *head, t_dlst **left, t_dlst **right);

#endif
