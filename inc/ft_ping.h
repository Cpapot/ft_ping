/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:34:29 by cpapot            #+#    #+#             */
/*   Updated: 2024/06/16 15:46:24 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTPING_H
# define FTPING_H

# include "../libft/includes/libft.h"
# include <unistd.h>
# include <stdio.h>

typedef struct s_pingdata
{
	char	*targetIP;
	bool	verbose;

} t_pingdata;

#endif
