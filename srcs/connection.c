/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 15:46:01 by cpapot            #+#    #+#             */
/*   Updated: 2025/03/07 20:48:34 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connection.h"

char *resolve_host(const char *host)
{
	struct addrinfo hints, *res;
	struct sockaddr_in *addr;
	char *result;

	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	if (getaddrinfo(host, NULL, &hints, &res) != 0)
		return NULL;

	addr = (struct sockaddr_in *)res->ai_addr;
	result = inet_ntoa(addr->sin_addr);
	freeaddrinfo(res);
	return result;
}

unsigned short checksum(void *b, int len)
{
	unsigned short *buf = b;
	unsigned int sum = 0;
	unsigned short result;

	for (sum = 0; len > 1; len -= 2)
		sum += *buf++;
	if (len == 1)
		sum += *(unsigned char *)buf;
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	result = ~sum;
	return result;
}

void update_data(t_pingdata *data, t_network_data *net_data)
{
	ft_bzero(&net_data->packet, sizeof(net_data->packet));
	net_data->icmp = (struct icmphdr *)net_data->packet;
	net_data->icmp->type = ICMP_ECHO;
	net_data->icmp->code = 0;
	net_data->icmp->un.echo.id = htons(getpid());
	net_data->icmp->un.echo.sequence = htons(data->sequence++);
	net_data->icmp->checksum = 0;
	net_data->icmp->checksum = checksum(net_data->packet, sizeof(struct icmphdr));

	// TTL minimum pour provoquer une erreur Time Exceeded
	// int ttl = 1;
	// setsockopt(net_data->socket, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl));
}

t_network_data *setup_connection(t_pingdata *data)
{
	t_network_data *net_data;

	net_data = stock_malloc(sizeof(t_network_data), &data->allocatedData);
	if (net_data == NULL)
		return sprintf(data->error, "malloc, %s", strerror(errno)), NULL;
	net_data->socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (net_data->socket < 0)
		return sprintf(data->error, "sockect, %s", strerror(errno)), NULL;

	net_data->icmp = (struct icmphdr *)net_data->packet;
	net_data->addr_len = sizeof(net_data->r_addr);

	ft_bzero(&net_data->addr, sizeof(net_data->addr));
	net_data->addr.sin_family = AF_INET;
	net_data->addr.sin_addr.s_addr = inet_addr(data->targetIP);

	net_data->tv_out.tv_sec = RECV_TIMEOUT;
	net_data->tv_out.tv_usec = 0;
	setsockopt(net_data->socket, SOL_SOCKET, SO_RCVTIMEO, (const char *)&net_data->tv_out, sizeof(net_data->tv_out));

	data->sequence = 0;
	data->p_received = 0;
	data->p_transmitted = 0;
	return net_data;
}
