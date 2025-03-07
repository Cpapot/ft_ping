/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:34:29 by cpapot            #+#    #+#             */
/*   Updated: 2025/03/07 19:51:33 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTPING_H
# define FTPING_H

# include "../libft/includes/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <netinet/ip_icmp.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <arpa/inet.h>

# define ERROR_BUFFSIZE		1024
# define PR_DATA			"%d bytes from %s: icmp_seq=%d ttl=%d time=%.3Lf ms\n"
# define PR_DATA_ERR		"%d bytes from %s: %s\n"
# define PR_PING			"PING %s (%s): 56 data bytes\n"
# define PR_PING_VERB		"PING %s (%s): 56 data bytes, id 0x%04x = %u\n"
# define PR_STAT			"--- %s ft_ping statistics ---\n%d packets transmitted, %d packets received, %d%% packet loss\n"
# define PR_ROUND_TRIP		"round-trip min/avg/max/stddev = %.3Lf/%.3Lf/%.3Lf/%.3Lf ms\n"

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

const char	*get_icmp_error_message(struct icmphdr *icmp);
void		ping_printerror(bool printhelp, t_pingdata *data, int socket);
void		ping_printerror_data(struct icmphdr *icmp);
int			parseParameter(int argc, char **argv, t_pingdata *data);
int			setup_timer(t_pingdata *data);
void		init_timer(void);
long double	stop_timer(void);
void		get_timer_result(t_pingdata *data, long double	*result);


#endif
