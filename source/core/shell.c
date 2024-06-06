/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:29:40 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/03 13:29:41 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_shell *shell_create(int32_t argc, char **argv, char **envp)
{
	t_shell *self;

	self = (t_shell *) memory_alloc(sizeof(t_shell));
	if (!self)
		return (NULL);
	self->argc = argc;
	self->argv = argv;
	self->envp = envp;
	self->env = environment_create(envp);
	self->prompt = prompt_create(self->env);
	self->input = input_create(self->env, self->prompt, argc, argv);
	self->tokenizer = tokenizer_create();
	self->linker = linker_create(self->env);
	self->lexer = lexer_create(self->env, self->tokenizer, self->linker);
	return (self);
}

bool shell_run(t_shell *shell)
{
	char     *line;
	t_vector *token_vector;

	line = input_get(shell->input);
	if (!line)
		return (false);
	print("%s\n", line);
	token_vector = tokenizer_tokenize(shell->tokenizer, line, " \n\'\"");
	token_vector = lexer_lex(shell->lexer, token_vector);

	you need to chose so this is why it doesn't compile
	//IF YOU WANT TO GET INFORMATIONS BUT NOT TOO MUCH

	// dbg_shell_print(shell);

	//IF YOU WANT TO GET EVEN MORE INFORMATIONS UNCOMMENT

	// dbg_shell_print_verbose(shell);

	shell->is_dirty = true;
	return (true);
}

bool shell_clear(t_shell *shell)
{
	prompt_clear(shell->prompt);
	input_clear(shell->input);
	tokenizer_clear(shell->tokenizer);
	lexer_clear(shell->lexer);
	linker_clear(shell->linker);
	shell->is_dirty = false;
	return (true);
}

t_shell *shell_destroy(t_shell *self)
{
	if (self)
	{
		if (self->env)
			environment_destroy(self->env);
		if (self->prompt)
			prompt_destroy(self->prompt);
		if (self->input)
			input_destroy(self->input);
		if (self->tokenizer)
			tokenizer_destroy(self->tokenizer);
		if (self->lexer)
			lexer_destroy(self->lexer);
		if (self->linker)
			linker_destroy(self->linker);
		memory_dealloc(self);
	}
	return (NULL);
}
