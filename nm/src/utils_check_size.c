/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check_size.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 13:28:18 by curquiza          #+#    #+#             */
/*   Updated: 2019/06/26 13:28:19 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	*check_and_move(t_bin_file *file, void *dest, uint64_t needed_size)
{
	if ((uint64_t)(dest + needed_size - file->ptr) > file->size)
		return (NULL);
	return (dest);
}
