/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 15:46:01 by cpapot            #+#    #+#             */
/*   Updated: 2024/06/16 16:44:28 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connection.h"

char	*resolve_host(const char *host, t_memlist *data)
{
	struct addrinfo		hints, *res;
	struct sockaddr_in	*addr;
	char				*result;

	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	if (getaddrinfo(host, NULL, &hints, &res) != 0)
		return NULL;

	addr = (struct sockaddr_in *)res->ai_addr;
	result = stock_malloc(sizeof(char) * strlen(inet_ntoa(addr->sin_addr)), &data);
	strcpy(result, inet_ntoa(addr->sin_addr));
	freeaddrinfo(res);
	return result;
}
