/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:59:40 by maamine           #+#    #+#             */
/*   Updated: 2024/06/17 18:09:59 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <linux/limits.h>

bool	is_builtins(const char	*s);
int		handle_builtins(t_cmd *cmd, t_env *env);
int		pwd(void);
int		echo(t_cmd *cmd);
int		cd(t_cmd *cmd, t_env *env);

#endif
