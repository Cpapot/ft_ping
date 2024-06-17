/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:34:29 by cpapot            #+#    #+#             */
/*   Updated: 2024/06/17 18:01:22 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTPING_H
# define FTPING_H

# include "../libft/includes/libft.h"
# include <unistd.h>
# include <stdio.h>

# define ERROR_BUFFSIZE		1024

typedef struct s_pingdata
{
	char			*address;
	char			*targetIP;
	bool			verbose;
	int				sequence;
	int				p_transmitted;
	int				p_received;
	t_memlist		*allocatedData;
	char			error[ERROR_BUFFSIZE];
} t_pingdata;

void	ping_printerror(bool printhelp, t_pingdata *data, int socket);
int		parseParameter(int argc, char **argv, t_pingdata *data);
int		setup_timer(t_pingdata *data);
void	init_timer(void);
long double	stop_timer(void);
long double	*get_timer_result(t_pingdata *data);


#endif
