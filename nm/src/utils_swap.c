/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_swap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 13:28:36 by curquiza          #+#    #+#             */
/*   Updated: 2019/06/26 13:28:41 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static uint32_t	swap_uint32(uint32_t n)
{
	int		swap;

	swap = ((n >> 24) & 0xFF)
		| ((n >> 8) & 0xFF00)
		| ((n << 8) & 0xFF0000)
		| ((n << 24) & 0xFF000000);
	return (swap);
}

uint32_t		swap_uint32_if(uint32_t n, enum e_endian endian)
{
	if (endian == MAGIC)
		return (n);
	else
		return (swap_uint32(n));
}

static uint64_t	swap_uint64(uint64_t n)
{
	uint64_t	swap;

	swap = ((n >> 56) & 0xff)
		| ((n >> 40) & 0xFF00)
		| ((n >> 24) & 0xFF0000)
		| ((n >> 8) & 0xFF000000)
		| ((n << 8) & 0xFF00000000)
		| ((n << 24) & 0xFF0000000000)
		| ((n << 40) & 0xFF000000000000)
		| ((n << 56) & 0xFF00000000000000);
	return (swap);
}

uint64_t		swap_uint64_if(uint64_t n, enum e_endian endian)
{
	if (endian == MAGIC)
		return (n);
	else
		return (swap_uint64(n));
}
