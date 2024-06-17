/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:23:43 by cpapot            #+#    #+#             */
/*   Updated: 2024/06/17 17:57:44 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMER_H
# define TIMER_H

# include "ft_ping.h"
# include <time.h>
# include <sys/time.h>
# include <math.h>

enum	e_time_info
{
	MIN_DEL = 0,
	MAX_DEL,
	AVG_DEL,
	DEV_DEL
};

typedef struct s_variance
{
	int				n;
	long double		sum;
	long double		sum_sqr;
} t_variance;

typedef struct s_time_data
{
	long double		actual_delay;
	long double		min_delay;
	long double		max_delay;
	t_variance		variance_data;
	long double		total_delay;
} t_time_data;

void	init_variance(t_variance *data);
void	add_variance_sample(t_variance *data, long sample);
long	compute_stddev(t_variance *data);


#endif
