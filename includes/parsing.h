#ifndef PARSING_H
# define PARSING_H

# include "error_handlers.h"
# include "utils.h"
# include "minishell.h"
# include "environment.h"

# define SPECIAL_CHARS			"$&;|<>\'\\\""
# define DQUOTES_EXCEPTION		"\\$`\""

typedef struct s_line {
	char	*line;
	char	*str;
	char	*merged_str;
	int		escaped_char;
}				t_line;

typedef struct s_str {
	char	*str;
	int		escaped_char;
}				t_str;

int		read_line(int fd, char **line);
t_dlst	*parsing(t_all *all);
char	*quote_handler(t_line *l, t_all *all);
char	*handle_backslash(char **line, t_all *all);
char	*get_variable_name(char **line, t_all *all);
char	*dollar_handler(char **str, t_all *all);
char	*single_operator_handler(char **line, t_all *all);
char	*double_operator_handler(char **line, t_all *all);
char	*get_str(char **line, t_all *all);
void	merge_str_and_lst_append(t_line *l, t_all *all);
char	*double_quotes_handler(t_line *l, t_all *all);
void	add_history_to_lst(char *str, t_dlst **head, t_dlst **p_history);

#endif
