/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:03:45 by egomez            #+#    #+#             */
/*   Updated: 2024/04/22 19:03:47 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_cmd   *cmd(t_token **token)
{
    t_cmd   *commands;
    t_token *tmp;
    t_arg	*last;
    t_cmd   *current;

    commands = NULL;
    tmp = *token;
    if (tmp)
    {
        current = cmd_new();
        cmd_add_back(&commands, current);
    }
    while (tmp)
    {
        if (tmp->type == WORD)
        {
            lstadd_back(&current->arguments, lstnew(tmp->val));
            last = &tmp->type;
        }
        else if (tmp->type == PIPE)
        {
            current = cmd_new();
            cmd_add_back(&commands, current);
        }
        else
        {
            token_add_back(&current->redirections, token_new(tmp->next->val, tmp->type));
			last = &tmp->type;
            tmp = tmp->next;
        }
        tmp = tmp->next;
    }
    return (commands);
}