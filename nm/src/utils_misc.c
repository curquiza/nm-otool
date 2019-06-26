/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 13:28:24 by curquiza          #+#    #+#             */
/*   Updated: 2019/06/26 13:28:25 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char		toggle_char(char c)
{
	if (ft_isalpha(c))
		return (c ^ TOGGLE_CASE);
	return (c);
}

t_bool		is_external_symbol(char c)
{
	return (c == 'u' || c == 'a' || c == 'p' || c == 'i' || c == 'c'
		|| c == 't' || c == 'd' || c == 'b' || c == 's');
}

t_bool		is_undefined_symb(char c)
{
	return (c == 'U' || c == 'u');
}

t_bool		is_archi_x86_64(cpu_type_t cpu_type)
{
	return (cpu_type == CPU_TYPE_X86_64);
}
