/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file32_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 13:27:27 by curquiza          #+#    #+#             */
/*   Updated: 2019/06/26 13:27:28 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void		get_one_symbol(t_bin_file *file, struct nlist *nlist,
					char *string_table, size_t i)
{
	uint32_t		n_value;

	file->symbols[i].name = check_and_move(file, string_table
			+ swap_uint32_if(nlist[i].n_un.n_strx, file->endian),
			sizeof(*file->symbols[i].name));
	if (!file->symbols[i].name)
		file->symbols[i].name = BAD_STRING_INDEX;
	n_value = swap_uint32_if(nlist[i].n_value, file->endian);
	file->symbols[i].type_char = get_type_char(n_value, nlist[i].n_type,
		nlist[i].n_sect, file);
	file->symbols[i].value = n_value;
}

static t_ex_ret	get_symbols_output(t_bin_file *file)
{
	size_t			i;
	char			*string_table;
	struct nlist	*nlist;
	uint32_t		nsyms;

	nsyms = swap_uint32_if(file->symtab_lc->nsyms, file->endian);
	nlist = (struct nlist *)check_and_move(file, (void *)file->ptr
		+ swap_uint32_if(file->symtab_lc->symoff, file->endian),
		sizeof(*nlist) * nsyms);
	if (!nlist)
		return (ft_ret_err2(file->filename, MALF_OBJ_ERR));
	string_table = check_and_move(file,
		file->ptr + swap_uint32_if(file->symtab_lc->stroff, file->endian),
		sizeof(*string_table));
	if (!string_table)
		return (ft_ret_err2(file->filename, MALF_OBJ_ERR));
	i = 0;
	while (i < nsyms)
	{
		get_one_symbol(file, nlist, string_table, i);
		i++;
	}
	return (SUCCESS);
}

t_ex_ret		handle_32(uint64_t size, void *ptr, char *filename,
					enum e_endian endian)
{
	t_bin_file	file;

	ft_bzero(&file, sizeof(file));
	file.filename = filename;
	file.ptr = ptr;
	file.size = size;
	file.endian = endian;
	if (init_32(&file) == FAILURE)
		return (FAILURE);
	if (file.symtab_lc)
	{
		if (get_symbols_output(&file) == FAILURE)
		{
			clean(&file);
			return (FAILURE);
		}
		sort_symbols(&file);
		print_symbols_output(file.symbols,
			swap_uint32_if(file.symtab_lc->nsyms, file.endian), VALUE_32);
		clean(&file);
	}
	return (SUCCESS);
}
