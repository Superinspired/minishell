/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:23:21 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/03 13:23:22 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "slib.h"
#include <readline/history.h>
#include <readline/readline.h>

#ifndef DIRECT_IO
#define DIRECT_IO 0
#endif

typedef struct s_environment   t_environment;
typedef struct s_hashmap       t_hashmap;
typedef struct s_hashmap_entry t_hashmap_entry;
typedef struct s_input         t_input;
typedef struct s_exec          t_exec;
typedef struct s_parser        t_parser;
typedef struct s_lexer         t_lexer;
typedef struct s_linker        t_linker;
typedef struct s_prompt        t_prompt;
typedef struct s_shell         t_shell;
typedef struct s_token         t_token;
typedef struct s_tokenizer     t_tokenizer;

struct s_hashmap_entry
{
	char *key;
	char *val;
};

t_hashmap_entry *hashmap_entry_create(const char *const key, const char *const value);
int64_t          hashmap_entry_compare(uintptr_t a, uintptr_t b);
t_hashmap_entry *hashmap_entry_destroy(t_hashmap_entry *self);

struct s_hashmap
{
	uint64_t  capacity;
	uint64_t  count;
	t_vector *bucket;
};

bool hashmap_is_empty(t_hashmap *self);
bool hashmap_put(t_hashmap *self, const char *const key, const char *const value);
char      *hashmap_del(t_hashmap *self, char *key);
char      *hashmap_get(t_hashmap *self, char *key);
t_hashmap *hashmap_create(const uint64_t capacity);
t_hashmap *hashmap_destroy(t_hashmap *self);
t_hashmap *hashmap_destroy_entries(t_hashmap *self);

struct s_shell
{
	bool           is_dirty;
	char         **argv;
	char         **envp;
	int64_t        argc;
	t_environment *env;
	t_input       *input;
	t_tokenizer   *tokenizer;
	t_lexer       *lexer;
	t_linker      *linker;
	t_prompt      *prompt;
};

t_shell *shell_create(int32_t argc, char **argv, char **envp);
bool     shell_run(t_shell *shell);
bool     shell_clear(t_shell *shell);
t_shell *shell_destroy(t_shell *self);

struct s_environment
{
	t_vector  *keys;
	t_hashmap *vars;
	bool       is_dirty;
};

t_environment *environment_create(char **envp);
t_environment *environment_build(t_environment *self, char **envp);
int64_t        enviroment_compare(uintptr_t a, uintptr_t b);
bool           enviroment_put(t_environment *self, char *variable, char *value);
char          *enviroment_get(t_environment *self, char *variable);
bool           enviroment_rem(t_environment *self, char *variable);
t_environment *environment_destroy(t_environment *self);

struct s_linker
{
	t_environment *env;
	char         **paths;
	char          *input;
	char          *output;
	bool           is_dirty;
};

t_linker *linker_create(t_environment *env);
t_linker *linker_init(t_linker *self, char *additional_dir);
bool      linker_resolve_exe(t_linker *self, char *exe);
bool      linker_resolve_path(t_linker *self, char *path);
char     *linker_resolve(t_linker *self, char *maybe_path, char flag);
t_linker *linker_clear(t_linker *self);
char     *linker_make_path(t_linker *self, char *root, char *maybe_path);
t_linker *linker_destroy(t_linker *self);

struct s_prompt
{
	t_environment *env;
	char          *prompt;
	bool           is_dirty;
};

t_prompt *prompt_create(t_environment *env);
char     *prompt_get(t_prompt *self);
t_prompt *prompt_clear(t_prompt *self);
t_prompt *prompt_destroy(t_prompt *self);

struct s_input
{
	bool           is_dirty;
	int64_t        index;
	char          *line;
	char         **argv;
	int64_t        argc;
	t_environment *env;
	t_prompt      *prompt;
};

t_input *input_create(t_environment *env, t_prompt *prompt, int64_t argc, char **argv);
t_input *input_clear(t_input *self);
char    *input_get(t_input *self);
t_input *input_destroy(t_input *self);

typedef enum e_token_kind
{
	KIND_AMPERSAND,
	KIND_APPEND,
	KIND_ARG,
	KIND_ASSIGNMENT,
	KIND_BLTN,
	KIND_CMD,
	KIND_DQUOTE,
	KIND_ERR,
	KIND_FILE,
	KIND_HERE_DOC,
	KIND_ID,
	KIND_LRDIR,
	KIND_NO_KIND,
	KIND_PATH,
	KIND_AND,
	KIND_OR,
	KIND_PIPE,
	KIND_QUOTE,
	KIND_RRDIR,
	KIND_SCOLON,
	KIND_SPC,
	KIND_VAR,

} t_token_kind;
struct s_token
{
	t_token_kind kind;
	uint64_t     len;
	uintptr_t    extra;
	char        *ptr;
};

t_token     *token_create(char *ptr);
void         token_print(t_token *token);
char        *token_get_str(t_token *self);
t_token_kind token_get_kind(t_token *self);
uintptr_t    token_get_extra(t_token *self);
void         token_set_str(t_token *self, char *str);
void         token_set_kind(t_token *self, t_token_kind kind);
void         token_set_extra(t_token *self, uintptr_t extra);
t_token     *token_destroy(t_token *self);

struct s_tokenizer
{
	t_vector *output;
	char     *input;
	char     *delim;
	bool      is_dirty;
};

t_tokenizer *tokenizer_create();
t_vector    *tokenizer_tokenize(t_tokenizer *self, char *input, char *delim);
t_vector    *tokenizer_get(t_tokenizer *self);
t_tokenizer *tokenizer_clear(t_tokenizer *self);
t_tokenizer *tokenizer_destroy(t_tokenizer *self);

struct s_lexer
{
	t_environment *env;
	t_tokenizer   *tokenizer;
	t_linker      *linker;
	t_vector      *token_vector;
	bool           is_dirty;
};

t_lexer *lexer_create(t_environment *env, t_tokenizer *tokenizer, t_linker *linker);
t_vector *lexer_get(t_lexer *self);
t_vector *lexer_lex(t_lexer *self, t_vector *input);

void lexer_identify_all_whitespaces(t_lexer *self, t_vector *it);
void lexer_identify_all_quotes(t_lexer *self, t_vector *it);
void lexer_identify_all_redirect(t_lexer *self, t_vector *it);
void lexer_identify_all_boolean(t_lexer *self, t_vector *it);
void lexer_identify_all_terminals(t_lexer *self, t_vector *it);

void lexer_identify_all_variables(t_lexer *self, t_vector *it);
void lexer_identify_all_identifiers(t_lexer *self, t_vector *it);
void lexer_identify_all_keywords(t_lexer *self, t_vector *it);
void lexer_identify_all_assignments(t_lexer *self, t_vector *it);
void lexer_identify_all_files(t_lexer *self, t_vector *it);

void lexer_identify_all_paths(t_lexer *self, t_vector *it);
void lexer_identify_all_commands(t_lexer *self, t_vector *it);
void lexer_identify_all_builtins(t_lexer *self, t_vector *it);
void lexer_identify_all_arguments(t_lexer *self, t_vector *it);
void lexer_identify_all_operators(t_lexer *self, t_vector *it);

t_lexer *lexer_clear(t_lexer *self);
t_lexer *lexer_destroy(t_lexer *self);

void dbg_shell_print(t_shell *shell);
void dbg_environment_print(t_environment *env);
void dbg_prompt_print(t_prompt *prompt);
void dbg_input_print(t_input *input);
void dbg_tokenizer_print(t_tokenizer *tokenizer);
void dbg_token_print(t_token *token);
void dbg_lexer_print(t_lexer *lexer);
void dbg_shell_print_verbose(t_shell *shell);
void dbg_environment_print_verbose(t_environment *env);
void dbg_prompt_print_verbose(t_prompt *prompt);
void dbg_input_print_verbose(t_input *input);
void dbg_tokenizer_print_verbose(t_tokenizer *tokenizer);
void dbg_token_print_verbose(t_token *token);
void dbg_lexer_print_verbose(t_lexer *lexer);

char **simple_split(const char *const source, const int32_t ch);

#endif
