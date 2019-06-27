/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 13:27:56 by curquiza          #+#    #+#             */
/*   Updated: 2019/06/26 13:27:57 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char	*get_archi_name(cpu_type_t cpu_type, cpu_subtype_t cpu_subtype)
{
	if (cpu_type == CPU_TYPE_I386)
		return ("i386");
	else if (cpu_type == CPU_TYPE_POWERPC)
		return ("ppc");
	else if (cpu_type == CPU_TYPE_POWERPC64)
		return ("ppc64");
	else if (cpu_type == CPU_TYPE_ARM64)
		return ("arm64");
	else if (cpu_type == CPU_TYPE_ARM && cpu_subtype == CPU_SUBTYPE_ARM_V7)
		return ("armv7");
	else if (cpu_type == CPU_TYPE_ARM && cpu_subtype == CPU_SUBTYPE_ARM_V7S)
		return ("armv7s");
	return ("");
}
