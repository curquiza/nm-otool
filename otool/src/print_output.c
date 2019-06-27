/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 13:24:25 by curquiza          #+#    #+#             */
/*   Updated: 2019/06/25 13:24:26 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void		print_compacted(t_bin_file *file, size_t i)
{
	size_t	cpt;
	void	*offset;

	cpt = 0;
	while (cpt < 16)
	{
		offset = (void *)file->ptr + file->text_offset + i + cpt;
		if (offset >= (void *)file->ptr + file->text_offset + file->text_size)
			return ;
		ft_printf("%-9.8x", swap_uint32_if(*(uint32_t *)offset, file->endian));
		cpt += 4;
	}
}

static void		print_spaced(t_bin_file *file, size_t i)
{
	size_t	cpt;
	void	*offset;

	cpt = 0;
	while (cpt < 16)
	{
		offset = (void *)file->ptr + file->text_offset + i + cpt;
		if (offset >= (void *)file->ptr + file->text_offset + file->text_size)
			return ;
		ft_printf("%-3.2hhx", (uint8_t)swap_uint32_if(*(uint32_t *)offset,
			file->endian));
		cpt++;
	}
}

static t_ex_ret	check_malformed_obj(t_bin_file *file)
{
	void	*offset;

	offset = (void *)file->ptr + file->text_offset + (file->text_size - 1);
	if (check_and_move(file, offset, sizeof(uint8_t)) == NULL)
		return (ft_ret_err2(file->filename, MALF_OBJ_ERR));
	return (SUCCESS);
}

t_ex_ret		print_output(t_bin_file *file, enum e_value value_type)
{
	size_t	i;

	if (check_malformed_obj(file) == FAILURE)
		return (FAILURE);
	if (g_title_display_inhib == FALSE && g_multi_display == FALSE)
		ft_printf("%s:\n", file->filename);
	ft_printf("%s\n", TITLE);
	i = 0;
	while (i < file->text_size)
	{
		if (value_type == VALUE_64)
			ft_printf("%.16llx\t", file->text_address + i);
		else
			ft_printf("%.8llx\t", file->text_address + i);
		if (file->cpu_type == CPU_TYPE_X86 || file->cpu_type == CPU_TYPE_X86_64
			|| file->cpu_type == CPU_TYPE_I386)
			print_spaced(file, i);
		else
			print_compacted(file, i);
		ft_putchar('\n');
		i += 16;
	}
	return (SUCCESS);
}
