/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 16:53:01 by cpapot            #+#    #+#             */
/*   Updated: 2025/03/07 17:21:54 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PING_ERROR_H
# define PING_ERROR_H

# define INFO_HELP "Try 'ft_ping -?' for more information.\n"
# define PR_PING_VERB_ERR "\nVr HL TOS  Len   ID Flg  off TTL Pro  cks      Src\tDst\tData\n %1x  %1x  %02x"
# define PR_PING_VERB_DATA " %04x %04x   %1x %04x  %02x  %02x %04x %s  %s "
# define PR_PING_ICMP_ERR "\nICMP: type %u, code %u, size %lu, id 0x%04x, seq 0x%04x\n"

# include "ft_ping.h"

#endif
