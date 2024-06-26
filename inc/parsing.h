/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:56:38 by cpapot            #+#    #+#             */
/*   Updated: 2024/06/16 17:44:46 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "ft_ping.h"

/*				parser	error				*/
# define ERR_MISSHOST	"missing host operand"
# define ERR_UNKNHOST	"unknown host"
# define ERR_INVFLAG	"invalid option -- \'%c\'"

# define VALIDFLAGS		"?v"

enum	e_parsing_return {
	SUCCES = 0,
	NO_HOST = 1,
	INVALID_FLAG = 2,
	UNKNOWN_HOST = 3
};

bool	isInString(char a, char *str);
bool	isFlags(char *str);
int		parser_set_error(int error_code, char invalidFlag, t_pingdata *data);

#endif
