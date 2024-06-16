/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:34:32 by cpapot            #+#    #+#             */
/*   Updated: 2024/06/16 17:21:25 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int main(int argc, char **argv)
{
	t_pingdata	data;

	data.allocatedData	= NULL;
	data.targetIP		= NULL;
	ft_bzero(data.error, sizeof(data.error));

	if (parseParameter(argc, argv, &data) != 0)
		ping_printerror(true, &data);

}
