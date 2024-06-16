/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 17:48:15 by cpapot            #+#    #+#             */
/*   Updated: 2024/06/16 17:59:22 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include "help.h"

void	help_flag(t_pingdata	*data)
{
	ft_printf(HELP_PRINT);
	stock_free(&data->allocatedData);
	exit(0);
}
