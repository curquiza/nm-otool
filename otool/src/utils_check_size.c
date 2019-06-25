/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check_size.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 13:24:29 by curquiza          #+#    #+#             */
/*   Updated: 2019/06/25 13:24:30 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	*check_and_move(t_bin_file *file, void *dest, uint64_t needed_size)
{
	if ((uint64_t)(dest + needed_size - file->ptr) > file->size)
		return (NULL);
	return (dest);
}
