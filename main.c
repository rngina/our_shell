/*
cc -Wall -Wextra -Werror cd_builtin.c        check_files.c   env_builtin.c  exit_builtin.c    get_next_line.c        main.c    pipes_managing.c  signals.c        utils.c 
built_in.c  check_cmd_access.c  echo_builtin.c  execution.c    export_builtin.c  get_next_line_utils.c  minishell.h  now_execute.c    pwd_builtin.c     unset_builtin.c  utils_more.c
*/

#include "minishell.h"

#include <stdlib.h> // For malloc

void free_list(t_list *list) {
    while (list) {
        t_list *temp = list;
        list = list->next;

        // Free argv
        char **argv = temp->argv;
        while (*argv) {
            free(*argv);
            argv++;
        }
        free(temp->argv);

        // Free cmd
        free(temp->cmd);

        // Free env
        char **env = temp->env;
        while (*env) {
            free(*env);
            env++;
        }
        free(temp->env);

        // Free inf
        t_inf *inf = temp->inf;
        while (inf) {
            t_inf *temp_inf = inf;
            inf = inf->next;
            free(temp_inf->file);
            free(temp_inf);
        }

        // Free outf
        t_outf *outf = temp->outf;
        while (outf) {
            t_outf *temp_outf = outf;
            outf = outf->next;
            free(temp_outf->file);
            free(temp_outf);
        }

        free(temp);
    }
}


// Function to create and initialize a new t_inf structure
t_inf *create_inf(char flag, char *file, t_inf *next) {
    t_inf *new_inf = (t_inf *)malloc(sizeof(t_inf));
    if (!new_inf) {
        // Handle allocation failure
        return NULL;
    }
    new_inf->flag = flag;
    new_inf->file = file;
    new_inf->next = next;
    return new_inf;
}

// Function to create and initialize a new t_outf structure
t_outf *create_outf(char flag, char *file, t_outf *next) {
    t_outf *new_outf = (t_outf *)malloc(sizeof(t_outf));
    if (!new_outf) {
        // Handle allocation failure
        return NULL;
    }
    new_outf->flag = flag;
    new_outf->file = file;
    new_outf->next = next;
    return new_outf;
}

// Function to create and initialize a new t_list structure
t_list *create_list1(int list_id, char *cmd, char **argv, char **env, t_list *next) {
    t_list *new_list = (t_list *)malloc(sizeof(t_list));
    if (!new_list) {
        // Handle allocation failure
        return NULL;
    }
    new_list->list_id = list_id;
    new_list->cmd = cmd;
    new_list->argv = argv;
    new_list->env = env;
    new_list->inf = NULL;
    //create_inf('n', "hello", NULL); // No additional information for echo
    new_list->outf = NULL;
    //create_outf('n', NULL, NULL); // No output file for grep
    new_list->next = next;

    return new_list;
}

t_list *create_list2(int list_id, char *cmd, char **argv, char **env, t_list *next) {
    t_list *new_list = (t_list *)malloc(sizeof(t_list));
    if (!new_list) {
        // Handle allocation failure
        return NULL;
    }
    new_list->list_id = list_id;
    new_list->cmd = cmd;
    new_list->argv = argv;
    new_list->env = env;
    new_list->inf = NULL;
    //create_inf('n', NULL, NULL); // No additional information for echo
    new_list->outf = NULL;
    //create_outf('n', NULL, NULL); // No output file for grep
    new_list->next = next;

    return new_list;
}

void	freeing_main(t_list *list)
{
//	printf("%s\n", list->env[0]);
	free(list->argv[0]);
//	free(argums_b[0]);
	free(list->argv);
//	free(argums_b);
	free(list);
	//free(b_list);
}

int main(int argc, char **argv, char **og_env) {
    char **env = duplicate_env(og_env);
   char **argums = (char **)malloc(1 * sizeof(char *));
    char **argums_b = (char **)malloc(1 * sizeof(char *));
    argums[0] =  NULL;
 //   argums[0] = ft_strdup("arg=gjl");
  //  argums[1] = NULL;
    argums_b[0] = NULL;
 // argums_b[0] = "-w";
   //ft_strdup("-w");
  //argums_b[1] = NULL;
    // Allocate and initialize t_list structure for echo command
    t_list *a_list = create_list1(1, "cat", argums/*argv*/, env, NULL);

    // Allocate and initialize t_list structure for grep command
  t_list *b_list = create_list2(2, "ls", argums_b /*argv*/, env, NULL);

    // Link the command sequence (echo | grep)
   a_list->next = b_list;

    // Now you have the complete structure for the command sequence "echo "hello" | grep "hello""
    // You can use these structures as needed in your program
    execute(a_list);
    //builtin("export", argums, env);
    //ft_env(env);
    free_dup_env(env);
	//free(argums[0]);
//	free(argums_b[0]);
	//free(argums);
//	free(argums_b);
	free(a_list);
	//free(b_list);
    return 0;
}

/*
typedef struct s_inf
{
	char			flag; // 'h' 'c' 'n' if nothing given
	char			*file; // if 'h' them its a limiter //NULL if nothing given
	struct s_inf	*next;
}			t_inf;

typedef struct s_outf
{
	char			flag; // 'a' 'c' 'n' if nothing given
	char			*file; //NULL if nothing given
	struct s_outf	*next;
}			t_outf;

typedef struct s_list
{
	int				list_id;
	char			*cmd;
	char			**argv;
	char			**env;
	t_inf			*inf;
	t_outf			*outf;
	struct s_list	*next;
}				t_list;
*/