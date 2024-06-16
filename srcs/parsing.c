/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:56:18 by cpapot            #+#    #+#             */
/*   Updated: 2024/06/16 17:58:38 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*resolve_host(const char *host, t_memlist *data);
void	help_flag(t_pingdata	*data);

int		checkFlags(char *flags_line, t_pingdata *data)
{
	for (int i = 0; flags_line[i]; i++)
	{
		if (!isInString(flags_line[i], VALIDFLAGS))
			return parser_set_error(INVALID_FLAG, flags_line[i], data);
		switch (flags_line[i])
		{
		case 'v':
			data->verbose = true;
			break;

		case '?':
			help_flag(data);
			break;
		}
	}
	return 0;
}

int		parseParameter(int argc, char **argv, t_pingdata *data)
{
	int		addressIndex = 0;

	for (int i = 1; i != argc; i++)
	{
		if (isFlags(argv[i]))
		{
			if (checkFlags(ft_stsubstr(argv[i], 1, ft_strlen(argv[i]) - 1, &data->allocatedData), data))
				return INVALID_FLAG;
		}
		else if (addressIndex == 0)
			addressIndex = i;
	}
	if (addressIndex == 0)
		return parser_set_error(NO_HOST, 0, data);
	data->targetIP = resolve_host(argv[addressIndex], data->allocatedData);
	if (data->targetIP == NULL)
		return parser_set_error(UNKNOWN_HOST, 0, data);
	return SUCCES;
}
