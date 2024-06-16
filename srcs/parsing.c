/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:56:18 by cpapot            #+#    #+#             */
/*   Updated: 2024/06/16 16:32:36 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*resolve_host(const char *host, t_memlist **data);


bool	isFlags(char *str)
{
	if (str != NULL)
	{
		if (str[0] == '-')
			return true;
	}
	return false;
}

int		parseParameter(int argc, char **argv, t_pingdata *data)
{
	t_memlist	*allocatedData = NULL;

	for (size_t i = 1; i != argc; i++)
	{
		if (isFlags(argv[i]))
		{
			
		}
		else if (data->targetIP == -1)
		{
			data->targetIP = resolve_host(argv[i], allocatedData);
		}
	}
}
