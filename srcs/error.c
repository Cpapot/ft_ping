/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 16:56:21 by cpapot            #+#    #+#             */
/*   Updated: 2024/06/17 17:38:44 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

void	ping_printerror(bool printhelp, t_pingdata *data, int socket)
{
	ft_printf_fd(2, "ft_ping : %s\n", data->error);
	if (printhelp)
		ft_printf_fd(2, INFO_HELP);
	if (socket != -1)
		close(socket);
	stock_free(&data->allocatedData);
	exit(1);
}
