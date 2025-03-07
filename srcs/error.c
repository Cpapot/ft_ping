/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 16:56:21 by cpapot            #+#    #+#             */
/*   Updated: 2025/03/07 20:24:05 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

void ping_printerror(bool printhelp, t_pingdata *data, int socket)
{
	ft_printf_fd(2, "ft_ping : %s\n", data->error);
	if (printhelp)
		ft_printf_fd(2, INFO_HELP);
	if (socket != -1)
		close(socket);
	stock_free(&data->allocatedData);
	exit(1);
}

const char *get_icmp_error_message(struct icmphdr *icmp)
{
	switch (icmp->type)
	{
	case ICMP_DEST_UNREACH:
		switch (icmp->code)
		{
		case ICMP_NET_UNREACH:
			return "Network unreachable";
		case ICMP_HOST_UNREACH:
			return "Host unreachable";
		case ICMP_PORT_UNREACH:
			return "Port unreachable";
		default:
			return "Destination unreachable";
		}
	case ICMP_TIME_EXCEEDED:
		return "Time to live exceeded";
	case ICMP_PARAMETERPROB:
		return "Parameter problem";
	case ICMP_REDIRECT:
		return "Redirect";
	default:
		return "Unknown ICMP error";
	}
}

void ping_printerror_data(struct icmphdr *icmp)
{
	struct ip *ip = (struct ip *)((unsigned char *)icmp + sizeof(struct icmphdr));
	size_t hlen = ip->ip_hl << 2;
	unsigned char *cp = (unsigned char *)ip + sizeof(*ip);

	printf("IP Hdr Dump:\n ");
	for (size_t j = 0; j < sizeof(*ip); ++j)
		printf("%02x%s", *((unsigned char *)ip + j), (j % 2) ? " " : "");
	printf(PR_PING_VERB_ERR, ip->ip_v, ip->ip_hl, ip->ip_tos);
	char dest_buffer[INET_ADDRSTRLEN];
	ft_strlcpy(dest_buffer, inet_ntoa(*((struct in_addr *)&ip->ip_dst)), INET_ADDRSTRLEN);
	char src_buffer[INET_ADDRSTRLEN];
	ft_strlcpy(src_buffer, inet_ntoa(*((struct in_addr *)&ip->ip_src)), INET_ADDRSTRLEN);
	printf(PR_PING_VERB_DATA, (ip->ip_len > 0x2000) ? ntohs(ip->ip_len) : ip->ip_len,
		   ntohs(ip->ip_id),
		   (ntohs(ip->ip_off) & 0xe000) >> 13,
		   ntohs(ip->ip_off) & 0x1fff,
		   ip->ip_ttl,
		   ip->ip_p,
		   ntohs(ip->ip_sum),
		   src_buffer,
		   dest_buffer);
	while (hlen-- > sizeof(*ip))
		printf("%02x", *cp++);
	cp = (unsigned char *)ip + sizeof(*ip);
	int type = *cp;
	int code = *(cp + 1);
	printf(PR_PING_ICMP_ERR, type, code,
		   ntohs(ip->ip_len) - hlen - 1,
		   *(cp + 4) * 256 + *(cp + 5),
		   *(cp + 6) * 256 + *(cp + 7));
}
