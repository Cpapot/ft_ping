/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:34:32 by cpapot            #+#    #+#             */
/*   Updated: 2024/06/16 16:32:31 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int main(int argc, char **argv)
{
	t_pingdata	data;

	data.targetIP = -1;

	parseParameter(argc, argv, &data);

}
