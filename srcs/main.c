/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:34:32 by cpapot            #+#    #+#             */
/*   Updated: 2025/03/09 20:31:52 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include "connection.h"
#include <signal.h>

bool loop = true;

void handler(int signal)
{
	(void)signal;
	loop = false;
}

void close_ping(t_pingdata *data, t_network_data *net_data, int status)
{
	close(net_data->socket);
	stock_free(&data->allocatedData);
	exit(status);
}

void main_loop(t_pingdata *data, t_network_data *net_data)
{
	update_data(data, net_data);
	init_timer();

	if (sendto(net_data->socket, net_data->packet, sizeof(net_data->packet), 0,
			   (struct sockaddr *)&(net_data->addr), sizeof(net_data->addr)) <= 0)
	{
		perror("sendto");
		close_ping(data, net_data, 1);
	}
	data->p_transmitted++;
	int ret = recvfrom(net_data->socket, net_data->packet, sizeof(net_data->packet), 0,
					   (struct sockaddr *)&(net_data->r_addr), &(net_data->addr_len));
	if (ret <= 0)
	{
		sleep(1);
		return;
	}

	long double delay = stop_timer();
	struct iphdr *ip_hdr = (struct iphdr *)net_data->packet;
	net_data->icmp = (struct icmphdr *)(net_data->packet + (sizeof(struct iphdr)));

	if (net_data->icmp->type == ICMP_ECHOREPLY || net_data->icmp->type == ICMP_ECHO)
	{
		data->p_received++;
		printf(PR_DATA, ntohs(ip_hdr->tot_len) - (ip_hdr->ihl << 2), data->targetIP, data->sequence - 1, ip_hdr->ttl, delay);
	}
	else
	{
		printf(PR_DATA_ERR, ntohs(ip_hdr->tot_len) - (ip_hdr->ihl << 2), data->targetIP, get_icmp_error_message(net_data->icmp));
		if (data->verbose && net_data->icmp)
			ping_printerror_data(net_data->icmp);
	}
	sleep(1);
}

int main(int argc, char **argv)
{
	t_pingdata data;
	t_network_data *net_data;
	long double result[4];

	data.verbose = false;
	data.allocatedData = NULL;
	data.targetIP = NULL;
	ft_bzero(data.error, sizeof(data.error));

	if (parseParameter(argc, argv, &data) != 0)
		ping_printerror(true, &data, -1);

	signal(SIGINT, handler);

	net_data = setup_connection(&data);
	if (net_data == NULL)
		ping_printerror(false, &data, -1);

	if (setup_timer(&data))
		ping_printerror(false, &data, net_data->socket);

	if (!data.verbose)
		printf(PR_PING, data.address, data.targetIP);
	else
		printf(PR_PING_VERB, data.address, data.targetIP, getpid(), getpid());

	while (loop)
		main_loop(&data, net_data);

	get_timer_result(&data, result);
	printf(PR_STAT, data.address, data.p_transmitted, data.p_received,
		   (100 - ((100 * data.p_received) / data.p_transmitted)));

	if (data.p_received != 0)
		printf(PR_ROUND_TRIP, result[0], result[2], result[1], result[3]);

	close(net_data->socket);
	stock_free(&data.allocatedData);
	return 0;
}
