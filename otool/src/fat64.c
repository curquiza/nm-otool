/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 13:23:58 by curquiza          #+#    #+#             */
/*   Updated: 2019/06/25 13:23:59 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static t_ex_ret	exec_same_arch(t_bin_file *file, struct fat_arch_64 *arch)
{
	uint64_t	size;
	uint64_t	offset;

	size = swap_uint64_if(arch->size, file->endian);
	offset = swap_uint32_if(arch->offset, file->endian);
	if (!check_and_move(file, file->ptr + offset, size))
		return (ft_ret_err2(file->filename, MALF_OBJ_ERR));
	return (ft_otool(size, file->ptr + offset, file->filename, NULL));
}

static t_ex_ret	if_same_arch_process(t_bin_file *file)
{
	struct fat_header	*header;
	uint32_t			arch_nb;
	struct fat_arch_64	*arch;

	if (!(header = (struct fat_header*)check_and_move(file, file->ptr,
			sizeof(*header))))
		return (ft_ret_err2(file->filename, NOT_OBJ_ERR));
	arch_nb = swap_uint32_if(header->nfat_arch, file->endian);
	arch = (struct fat_arch_64 *)check_and_move(file,
		file->ptr + sizeof(struct fat_header), sizeof(*arch));
	if (!arch)
		return (ft_ret_err2(file->filename, MALF_OBJ_ERR));
	while (arch_nb--)
	{
		if (is_archi_x86_64(swap_uint32_if(arch->cputype, file->endian)))
			return (exec_same_arch(file, arch));
		arch = (struct fat_arch_64 *)check_and_move(file, arch + 1,
			sizeof(*arch));
		if (!arch)
			return (ft_ret_err2(file->filename, MALF_OBJ_ERR));
	}
	return (-1);
}

static t_ex_ret	exec_diff_arch(t_bin_file *file, struct fat_arch_64 *arch)
{
	cpu_type_t		cpu_type;
	cpu_subtype_t	cpu_subtype;
	uint64_t		size;
	uint64_t		offset;

	size = swap_uint64_if(arch->size, file->endian);
	offset = swap_uint64_if(arch->offset, file->endian);
	cpu_type = swap_uint32_if(arch->cputype, file->endian);
	cpu_subtype = swap_uint32_if(arch->cpusubtype, file->endian);
	ft_printf("%s (architecture %s):\n",
		file->filename, get_archi_name(cpu_type, cpu_subtype));
	g_title_display_inhib = TRUE;
	if (!check_and_move(file, file->ptr + offset, size))
		return (ft_ret_err2(file->filename, MALF_OBJ_ERR));
	if (ft_otool(size, file->ptr + offset, file->filename, NULL) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static t_ex_ret	not_same_arch_process(t_bin_file *file)
{
	struct fat_header	*header;
	uint32_t			arch_nb;
	struct fat_arch_64	*arch;

	if (!(header = (struct fat_header*)check_and_move(file, file->ptr,
			sizeof(*header))))
		return (ft_ret_err2(file->filename, NOT_OBJ_ERR));
	arch_nb = swap_uint32_if(header->nfat_arch, file->endian);
	arch = (struct fat_arch_64 *)check_and_move(file,
		file->ptr + sizeof(struct fat_header), sizeof(*arch));
	if (!arch)
		return (ft_ret_err2(file->filename, MALF_OBJ_ERR));
	while (arch_nb--)
	{
		if (exec_diff_arch(file, arch) == FAILURE)
			return (FAILURE);
		arch = (struct fat_arch_64 *)check_and_move(file, arch + 1, \
			sizeof(*arch));
		if (!arch)
			return (ft_ret_err2(file->filename, MALF_OBJ_ERR));
	}
	return (SUCCESS);
}

t_ex_ret		handle_fat64(char *filename, uint64_t size, void *ptr,
				enum e_endian endian)
{
	t_bin_file			file;
	t_ex_ret			ret;

	file.filename = filename;
	file.size = size;
	file.ptr = ptr;
	file.endian = endian;
	ret = if_same_arch_process(&file);
	if (ret == FAILURE || ret == SUCCESS)
		return (ret);
	return (not_same_arch_process(&file));
}
