/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuraw <zuraw@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:57:25 by pzurawic          #+#    #+#             */
/*   Updated: 2024/12/27 16:20:56 by zuraw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L

# define BUFFER_SIZE 100000000

# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <signal.h>
# include <string.h>
# include <termios.h>
# include <termcap.h>
# include <ncurses.h>
# include <stdbool.h>
# include "./libft/libft.h"
/* MACROS */
# define QUOT_ERROR "Incorrect number of quotation marks\n"
# define CMD_ERROR "Instruction cannot ends with OPERATOR\n"

/* ENUMS */
typedef enum e_tokens	t_tokens;

// rozpoznawanie white space -> często służą jako separatory tokenów
typedef enum e_tokens
{
	ARG,		//	jakikolwiek tekst
	BUILTIN,	//	echo cd pwd export unset env exit
	OPERATOR,	//	< > << >> | || & &&
	QUOT,		//	" '
}	t_tokens;

/* STRUCTS */
typedef struct s_data	t_data;
typedef struct s_parse	t_parse;
typedef struct s_token	t_token;
typedef struct s_exec	t_exec;

// GENERALNE INFORMACJE
typedef struct s_data
{
	char		**envp;

	t_parse		*parsing;
	t_exec		*exec;
}	t_data;

// POMOCNICZY STRUCT DO PARSINGU
typedef struct s_token
{
	int			id;			// id tokena
	int			curr_ev;	// aktualna zmienna środowiskowa
	int			env_var_count;	// ilość zmiennych środowiskowych
	char		*text;		// przechowuje część inputa
	char		**env_var;	// lista zmiennych środowiskowych
	char		**envp;		// przechowuje całe envp
	char		*proc_text; // przechowuje przetworzony tekst
	t_tokens	token;		// informacja o tokenie inputa (ENUM)
}	t_token;

typedef struct s_exec
{
	char			*operator;	// operator
	char			*cmd;		// komenda
	char			**args;		// argumenty komendy
	char			**envp;		// zmienne środowiskowe
	int				out;		// deskryptor wyjścia
	int				in;			// deskryptor wejścia
	t_tokens		token;		// informacja o tokenie komendy - ENUM
	struct s_exec	*next;		// następny element
	struct s_exec	*prev;		// przeszły element
}	t_exec;

// PRZEZNACZONE DO PARSINGU
typedef struct s_parse
{
	char	*input;			// tekst z inputa
	char	**words;		// tablica słów z inputa
	char	*operators;		// tablica operatorów
	int		input_items;	// ilość tokenów w input
	t_token	**tokens;		// tokeny każdego fragmentu inputa
	t_data	*data;
}	t_parse;

/* GLOBAL VAR */
extern int				g_exit_code;

/***************************** FUNCTIONS **********************************/

//		SIGNALS
void	interactive_mode_signals(t_data *data);

/*				EXECUTION				*/
void handle_operator(t_exec **exec, t_parse *parsing, int *i);
void handle_command(t_exec **exec, t_parse *parsing, int i);
char	*ft_strtok(char *str, char delim);
char	*ft_strchr(const char *s, int c);
int	execute_command(t_data *data, t_exec *command_struct);
int	execute_pipeline(t_data *data);
int	ft_strcmp(char *s1, char *s2);
char	*ft_strtok(char *str, char delim);
char	*find_path(const char *cmd);
int	handle_heredoc(const char *delimiter);
// char	**copy_double_array(char **src);


/*				UTILS				*/
// 		INPUT_HANDLING
bool	input_reader(t_data *data);

// 		UTILS
void	error_exit(void);
void	exit_clear(t_data *data);
void	free_tokens(t_parse *parsing);
void	free_words(t_parse *parsing);
void	free_double_array(char **str);

//		UTILS2
void	free_data_envp(t_data *data);

//		UTILS_SET
void	set_data(t_data *data, char **envp);
int		is_separator(t_parse *parsing, int i);
t_exec	*alloc_exec(void);
void	copy_envp(t_data *data, char **envp);

//		CLEARING
void	clear_parsing(t_parse *parsing);
void	clear_exec(t_exec *exec);
/* void	clear_single_exec(t_exec *exec); */

//		SET_PARSING
void	set_parsing(t_parse *parsing, t_data *data);

//		UTILS_OPERATORS
void	set_operators(char *operators);
bool	look_for_operator(char c);

/*				PARSING				*/
//		PARSING
int		parsing(t_data *data);

//		PARSING_TOKENS
void	tokenize(t_parse *parsing);

//		PARSING_TOKENS_WORDS
void	set_words_tab(t_parse *parsing);

//		EVNP_HANDLER
void	envp_handler(t_token *token);

//		ENV_HANDLER_UTILS
void	alloc_env_var(t_token *token);
void	get_env_var(t_token *token, int *i, int *j, char *value);
int		env_var_count(t_token *token);
char	*get_env_value(char *var_name, char **envp);

//		PROCESS_TEXT
void	process_text(t_token *token);

//		PROCESS_TEXT_UTILS
int		skip_squot(char *text);
int		dec_by_quot_mark(t_token *token, int len);

//		PROCESS_TEXT_COPY
void	copy_text(t_token *token, int len, char quot_mark);

//		PROCESS_TEXT_COPY_UTILS
void	alloc_proc_text(t_token *token, int len);
void	track_quot_mark(t_token *token, char *quot_mark, int i);

//		PUSH_TO_EXEC
void	push_to_exec(t_parse *parsing, t_exec *exec);

/*				BUILTIN				*/
//		REDIRECT_BUILTINS
void	execute_builtin(t_data *data, t_exec *exec);

//		ECHO_PWD_ENV_EXIT
int		builtin_echo(t_exec *exec);
int		builtin_env(char **args, char **envp);
void	builtin_exit(t_data *data);
char	*get_current_path(void);
int		builtin_pwd(void);

//		EXPORT
int		builtin_export(t_exec *exec, t_data *data);

//		EXPORT_SORT_AND_VALID
void	print_sorted_array(char **envp);
bool	is_valid(char *arg);

//		 EXPORT_ARGS
void	update_envp(t_data *data, t_exec *exec, int *j);
void	set_exec_envp(t_exec *exec, char **envp);

//		UNSET
int		builtin_unset(t_exec *exec, t_data *data);

//		CD
int		builtin_cd(t_exec *exec, t_data *data);

//		CD_UTILS
int		change_dir(char *temp_path);
int		is_correct(t_exec *exec);

#endif