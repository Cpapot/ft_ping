/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:34:29 by cpapot            #+#    #+#             */
/*   Updated: 2024/06/16 20:21:35 by cpapot           ###   ########.fr       */
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
	char			*targetIP;
	bool			verbose;
	int				sequence;
	t_memlist		*allocatedData;
	char			error[ERROR_BUFFSIZE];
} t_pingdata;

void	ping_printerror(bool printhelp, t_pingdata *data, int socket);
int		parseParameter(int argc, char **argv, t_pingdata *data);


#endif
