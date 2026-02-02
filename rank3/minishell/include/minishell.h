/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotrujil <jotrujil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:50:01 by jotrujil          #+#    #+#             */
/*   Updated: 2025/02/11 20:14:21 by jotrujil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <sys/wait.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <unistd.h>
# include <termios.h>
# include <dirent.h>

//COLORS
# define DEFAULT "\001\033[0;39m\002"
# define ORANGE "\001\033[1;38;5;208m\002"
# define GREEN  "\001\033[1;32m\002"

# define PIPE_READ_END 0
# define PIPE_WRITE_END 1

typedef struct s_prompt
{
	t_list	*cmds;
	pid_t	pid;
	char	**envp;
}	t_prompt;

typedef struct s_command
{
	char	**full_cmd;
	char	*full_path;
	int		in_file;
	int		out_file;
}	t_command;

typedef struct s_builtin
{
	char	*name;
	int		(*func)(t_prompt *);
}	t_builtin;

// UTILS

/* Count how many strings there are in the matrix */
int			ft_size_matrix(char **matrix);
/* Copy matrix and allocate memory */
char		**ft_dup_matrix(char **envp);
void		ft_free_matrix(char **matrix);
/* Write the error in the error console */
void		*ms_handle_error(char *error, char *param, int g_status_error);
/* Return the position where the character sent is found */
int			ms_strchr_pos(const char *s, int c);
/* Handle when the input is a Ctrl+C signal */
void		if_sigint(int sig);
/* Make substr from set to the next set string*/
char		*strtrim(char const *s1, char const *set);
/* Count how many str there are in the output separated with c character */
int			ms_count_strs(const char *s, char *c, int i[2]);
/* Create a matrix from s separated with char set */
char		**ms_separate_matrix(char **aux, char const *s,
				char *set, int i[3]);
/* Return the position where some char from search is found in *s */
int			ms_strchars_pos(const char *s, char *search);
/* Returns the index of an specific character inside a Sring.
Returns -1 if not exist. */
int			ft_strchr_i(const char *s, int c);
/* Replaces the n-th element in a matrix with elements from another matrix. */
char		**ms_matrix_replace_n(char ***src, char **add, int n);
/* Write str with '\n' in fd and return the nbr of characters */
int			ms_putendl_fd(char *s, int fd);

// PARSE

/* Add the new str in the end of the matrix */
char		**ms_add_end_env(char	**matrix, char *new);
/* Add or update an environment variable if already exists */
char		**ms_add_env(char *var, char *value, char **envp);
/* Take the value of the env that you want if it exists */
char		*ms_get_env(char *var, char **envp, int n);
/* Get the prompt to show in the terminal */
char		*ms_get_prompt(t_prompt prompt);
/* Executes a command and saves output to string ending in \n */
void		ms_get_exec(char ***out, char *full, char *args, char **envp);
/* Execute the parse and executor */
void		*ms_parse(char *output, t_prompt *p);
/* Separate the arguments from output in a matrix */
char		**ms_trim(char const *s, char *set);
/* End the parse and exec the output */
void		*ms_parse_and_exec(char **output, t_prompt *prompt);
/* Checks if an environment variable exists in envp. Returns 1 if exists */
int			ms_var_in_envp(char *argv, char **envp, int ij[2]);
/* After trim we obtein vars, paths and separate <>| */
char		**ms_split_output(char **output, t_prompt *prompt);
/* Obtein the variable developed in $ */
char		*ms_vars(char *str, int i, int j[2], t_prompt *prompt);
/* inside ms_vars, substitute the variable if exists */
char		*ms_get_sub_var(char *str, int i, t_prompt *prompt);
/* Develops the path sent from home */
char		*ms_paths(char *str, int i, int j[2], char *var);
/* Separates if there is | or < or > out of "" */
char		**ms_subsplit(char *output, char *set);
/* Uses  the matrix from ms_subsplit to extend the original matrix*/
char		**ft_matrix_replace_in(char ***big, char **small, int n);
/* Create a list where all commands' information is saved in structs */
t_list		*ms_nodes(char **args, int i);
/* Eliminates "" and '' from the strings */
char		**ms_clean_output(char **output);
/* Initializes a t_command pointer to save the next command */
t_command	*ms_command_init(void);
/* Fill or create the infile and outfile. And fill the full command */
t_command	*ms_params(t_command *node, char **temp[2], int *i);
/* If there is bad input filling the nodes, free everything */
t_list		*ms_break_fill(t_list *cmds, char **args, char **temp);
/* Function to clean the nodes list */
void		ms_clean(void *n);
/* Read each line for here_doc */
char		*ms_get_str(char *str[2], size_t len, char *limit, char *warn);
/* Do here do for << */
int			ms_here_doc(char *str[2], char *aux[2]);
/* By flags it choose >>, < or > */
int			ms_get_fd(int oldfd, char *path, int flags[2]);
/* when there is >> open and send fd to infile for >> conditions*/
t_command	*ms_out_2(t_command *node, char **args, int *i);
/* when there is > open and send fd to infile for > conditions */
t_command	*ms_out_1(t_command *node, char **args, int *i);
/* when there is < open and send fd to infile for < conditions */
t_command	*ms_in_1(t_command *node, char **args, int *i);
/* when << and it uses here_doc */
t_command	*ms_in_2(t_command *node, char **args, int *i);

// EXECUTE

/* Runs over cmds and executes builtins. If it isn't a builtin, 
executes the cmd. Waits for all child processes to finish 
and updates g_status based on their exit status. */
int			builtin_or_cmd(t_prompt *prompt, t_list *cmd, int	*terminate);
/* Handling the exit of the program with a status code based on the arguments */
int			ms_exit(t_list *cmd, int *terminate);
/* Changes the currend working directory and update the related env vars */
int			ms_cd(t_prompt *p);
/* Minishell implementation of export builtin */
int			ms_export(t_prompt *p);
/* Minishell implementation of unset builtin */
int			ms_unset(t_prompt	*p);
/* Say the path of the current directory */
int			ms_pwd(void);
/* Minishell implementation of echo builtin */
int			ms_echo(t_list *cmd);
/* Executes a command in a child process with pipes, ensuring file handling.*/
void		*exec_cmd(t_prompt *prompt, t_list *cmd);
/* Check and return 1 if a command is a builtin */
int			is_builtin(t_command *cmd);
/* Check errors and if there is a command to exec call ms_exec */
void		*ms_fork_check(t_prompt	*prompt, t_list *cmd, int fd[2]);
/* Executes the command, echo or pwd or env that is running in the node */
void		ms_child_builtin(t_prompt *t_prompt, t_command *node,
				int lenght, t_list *cmd);

#endif