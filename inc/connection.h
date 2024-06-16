/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 15:46:06 by cpapot            #+#    #+#             */
/*   Updated: 2024/06/16 20:29:08 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECTION_H
# define CONNECTION_H

# include "ft_ping.h"

# include <stdlib.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/ip_icmp.h>
#include <netinet/ip.h>
# include <netinet/in.h>
# include <string.h>

typedef struct s_network_data
{
	int					socket;
	char				packet[64];
	struct sockaddr_in	addr;
	struct sockaddr_in	r_addr;
	socklen_t			addr_len;
	struct icmphdr		*icmp;
}	t_network_data;

t_network_data	*setup_connection(t_pingdata *data);
void			update_data(t_pingdata *data, t_network_data *net_data);
unsigned short	checksum(void *b, int len);

#endif
