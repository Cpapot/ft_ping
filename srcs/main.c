/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:34:32 by cpapot            #+#    #+#             */
/*   Updated: 2024/06/17 14:58:28 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include "connection.h"

int main(int argc, char **argv)
{
	t_pingdata		data;
	t_network_data	*net_data;

	data.allocatedData	= NULL;
	data.targetIP		= NULL;
	ft_bzero(data.error, sizeof(data.error));

	if (parseParameter(argc, argv, &data) != 0)
		ping_printerror(true, &data, -1);

	net_data = setup_connection(&data);
	if (net_data == NULL)
		ping_printerror(false, &data, -1);

	while (42)
	{
		update_data(&data, net_data);

		if (sendto(net_data->socket, net_data->packet, sizeof(net_data->packet), 0, (struct sockaddr *)&(net_data->addr), sizeof(net_data->addr)) <= 0) {
			perror("sendto");
			close(net_data->socket);
			return 1;
		}


		if (recvfrom(net_data->socket, net_data->packet, sizeof(net_data->packet), 0, (struct sockaddr *)&(net_data->r_addr), &(net_data->addr_len)) <= 0) {
			perror("recvfrom");
			close(net_data->socket);
			return 1;
		}

		struct iphdr *ip_hdr = (struct iphdr *)net_data->packet;
		net_data->icmp = (struct icmphdr *)(net_data->packet + (sizeof(struct iphdr)));
		if (net_data->icmp->type == ICMP_ECHOREPLY)
			printf("Received ICMP echo reply from %s TTL: %d\n", data.targetIP, ip_hdr->ttl);
		else
			printf("Received ICMP packet with type %d code %d\n", net_data->icmp->type, net_data->icmp->code);
		sleep(1);
	}
	close(net_data->socket);
	return 0;
}
