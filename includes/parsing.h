/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:43:07 by egomez            #+#    #+#             */
/*   Updated: 2024/04/18 18:43:10 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include <stdio.h>
#include <libft.h>

typedef enum    arg_type
{
    WORD,
    PIPE,
    L_REDIRECT,
    R_REDIRECT,
} t_arg ;

typedef struct s_token
{
    t_arg        type;
    char            *val;
    struct s_token         *next;
}   t_token;

t_token	*token_new(char	*val, t_arg type);
t_token	*token_last(t_token *lst);
void	token_add_back(t_token **lst, t_token *new);

# endif