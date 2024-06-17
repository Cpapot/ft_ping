/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:34:32 by cpapot            #+#    #+#             */
/*   Updated: 2024/06/17 18:40:36 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include "connection.h"

void	main_loop(t_pingdata *data, t_network_data *net_data)
{
	update_data(data, net_data);
	init_timer();

	if (sendto(net_data->socket, net_data->packet, sizeof(net_data->packet), 0, (struct sockaddr *)&(net_data->addr), sizeof(net_data->addr)) <= 0) {
		perror("sendto");
		close(net_data->socket);
		exit(1);
	}
	data->p_transmitted++;

	//refaire les secus pour gerer le paquet loss (ne pas exit)
	if (recvfrom(net_data->socket, net_data->packet, sizeof(net_data->packet), 0, (struct sockaddr *)&(net_data->r_addr), &(net_data->addr_len)) <= 0) {
		//perror("recvfrom");
		//close(net_data->socket);
		//exit(1);
	}
	else
		data->p_received++;

	long double	delay = stop_timer();
	struct iphdr *ip_hdr = (struct iphdr *)net_data->packet;
	net_data->icmp = (struct icmphdr *)(net_data->packet + (sizeof(struct iphdr)));
	if (net_data->icmp->type == ICMP_ECHOREPLY)
		printf("64 bytes from %s: icmp_seq=%d ttl=%d time=%.3Lf ms\n", data->targetIP, data->sequence - 1, ip_hdr->ttl, delay);
	else
		printf("Received ICMP packet with type %d code %d\n", net_data->icmp->type, net_data->icmp->code);
	sleep(1);

}

//TODO GERER DIVIDE PAR 0 SI AUCUNE REQUETE NE SONT PASSEE
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

	if (setup_timer(&data))
		ping_printerror(false, &data, net_data->socket);

	ft_printf("PING %s (%s): 56 data bytes\n", data.address, data.targetIP);
	while (42)
	{
		main_loop(&data, net_data);
		if (data.sequence == 10)
			break;
	}
	long double	result[4];
	get_timer_result(&data, result);
	printf("--- %s ft_ping statistics ---\n", data.address);
	printf("%d packets transmitted, %d packets received, %d%% packet loss\n", data.p_transmitted, data.p_received, (100 - ((100 * data.p_received) / data.p_transmitted)));
	printf("round-trip min/avg/max/stddev = %.3Lf/%.3Lf/%.3Lf/%.3Lf ms\n", result[0], result[2], result[1], result[3]);
	close(net_data->socket);
	stock_free(&data.allocatedData);
	return 0;
}
