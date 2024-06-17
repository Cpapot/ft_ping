/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:07:20 by cpapot            #+#    #+#             */
/*   Updated: 2024/06/17 17:22:34 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "timer.h"

void	init_variance(t_variance *data)
{
	data->n = 0;
	data->sum = 0.0;
	data->sum_sqr = 0.0;
}

void	add_variance_sample(t_variance *data, long sample)
{
	data->n++;
	data->sum += sample;
	data->sum_sqr += sample * sample;
}

long	compute_stddev(t_variance *data)
{
	if (data->n == 0)
		return 0;
	long avg = data->sum / data->n;
	return sqrtl((data->sum_sqr / data->n) - (avg * avg));
}
