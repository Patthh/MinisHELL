#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include <dirent.h> // opendir, readir

# define PROMPT "minishell$ "
# define TRUE 1
# define FALSE 0
# define EXIT_STATUS

// check the token type number of the symbols
// grep 'TKN_' include/minishell.h | awk '{print NR-1, $1}'
typedef enum e_token
{
	TKN_IN,			// 0 <
	TKN_OUT,		// 1 >
	TKN_RDA,		// 2 >>
	TKN_RDH,		// 3 <<
	TKN_PIPE,		// 4 |
	TKN_ENV,		// 5 $VAR
	TKN_STATUS,		// 6 $?
	TKN_WHITESPACE, // 7
	TKN_EOF,		// 8
	TKN_BG,			// 9 &
	TKN_START,		// 10 (
	TKN_END,		// 11 )
	TKN_AND,		// 12 &&
	TKN_OR,			// 13 ||
	TKN_SINGLE,		// 14 single quote
	TKN_DOUBLE,		// 15 double quote
	TKN_WILDCARD,	// 16 *
	TKN_WORD,		// 17
}	t_token_type;

// token structure for lexer
typedef struct s_token
{
	t_token_type			type;
	char					*value;
	int						error;
	struct s_token			*next;
}	t_token;

// redirection structure
typedef struct s_redirection
{
	char					*type; // IN, OUT, APPEND, HEREDOC
	char					*filename;
	struct s_redirection	*next;
}	t_redirection;

// command structure to handle a single command
typedef struct s_command
{
	char					**arguments;
	t_redirection			*input;
	t_redirection			*output;
	int						fd_in;
	int						fd_out;
	int						is_builtin;
	struct s_command		*next;
}	t_command;

// command structure to handle multiple commands
typedef struct s_pipeline
{
	t_command				**commands; // array of commands
	int						cmd_count;
}	t_pipeline;

// structure to handle env
typedef struct s_env
{
	char					*key;
	char					*value;
	struct s_env			*next;
}	t_env;

typedef struct s_program
{
	char					**envp; // array of environment variables
	t_token					*token;
	t_command				*command;
	t_env					*env_list;
	int						status;
	int						exit;
}	t_program;

// SHELL
void	run_shell(t_program *minishell);
int		handle_input(char *input, t_program *minishell);
// void	ft_exit(const char *input, t_token *tokens, t_program *minishell);

// LEXER
t_token	*tokenizer(const char *input, t_program *minishell);
t_token	*token_new(t_token_type type, const char *value);
void	token_add(t_token **head, t_token *new_token);
t_token	*token_word(const char **input);

void	token_redirector(const char **input, t_token **head);
void	token_operator(const char **input, t_token **head);
void	token_paranthesis(const char **input, t_token **head);
void	token_quotes(const char **input, t_token **head, t_program *minishell);
int		quote_counter(const char *input);
void	token_dollar(const char **input, t_token **head, t_program *minishell);
void	token_wildcard(const char **input, t_token **head);

char	*env_name(const char **input);
char	*env_value(t_program *minishell, const char *key);
void	env_token(t_token **head, t_program *minishell, const char *key);
char	*env_quote(t_program *minishell, const char *input);

// MEMORY
void	init_shell(t_program *program, char **envp);
void	free_shell(t_program *program);
void	free_token(t_token *token);
void	free_list(t_token *head);

// UTILS
void	ft_error(const char *message);
void	ft_putstr_fd(char *s, int fd);
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strdup(const char *s);
char	*ft_strndup(const char *src, size_t n);
char	*ft_strchr(const char *string, int c);
int		ft_isalnum(int c);
size_t	ft_strlen(const char *str);
char	*ft_itoa(int n);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isspace(int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strstr(const char *big, const char *little);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

// TESTING
void	print_tokens(t_token *head);

#endif
