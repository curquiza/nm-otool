/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 13:28:10 by curquiza          #+#    #+#             */
/*   Updated: 2019/06/26 13:28:11 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static t_ex_ret	run_merge_sort(t_symbol *tab, t_sort *data,
						t_bool (*comp)(t_symbol *symb1, t_symbol *symb2))
{
	t_symbol	*tmp;
	uint32_t	i;

	data->cpt1 = data->start1;
	data->cpt2 = data->end1 + 1;
	if (!(tmp = (t_symbol *)ft_memalloc(sizeof(*tmp)
		* (data->end1 - data->start1 + 1))))
		return (FAILURE);
	ft_memmove(tmp, tab + data->start1, (data->end1 - data->start1 + 1)
		* sizeof(*tmp));
	i = data->start1;
	while (i <= data->end2)
	{
		if (data->cpt1 == data->end1 + 1)
			break ;
		else if (data->cpt2 == data->end2 + 1)
			tab[i++] = tmp[data->cpt1++ - data->start1];
		else if (comp(tmp + data->cpt1 - data->start1, tab + data->cpt2)
			== FALSE)
			tab[i++] = tmp[data->cpt1++ - data->start1];
		else
			tab[i++] = tab[data->cpt2++];
	}
	free(tmp);
	return (SUCCESS);
}

static t_ex_ret	merge_sort(t_symbol *tab, uint32_t start_index,
						uint32_t end_index,
						t_bool (*comp)(t_symbol *symb1, t_symbol *symb2))
{
	t_sort		data;
	uint32_t	middle;

	data.start1 = start_index;
	data.end1 = (end_index + start_index) / 2;
	data.end2 = end_index;
	middle = (end_index + start_index) / 2;
	if (start_index != end_index)
	{
		if (merge_sort(tab, start_index, middle, comp) == FAILURE \
				|| merge_sort(tab, middle + 1, end_index, comp) == FAILURE \
				|| run_merge_sort(tab, &data, comp) \
				== FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

static void		reverse_symb_tab(t_symbol *tab, uint32_t tab_count)
{
	uint32_t	i;
	t_symbol	tmp;

	i = 0;
	while (i < tab_count / 2)
	{
		tmp = tab[i];
		tab[i] = tab[tab_count - 1 - i];
		tab[tab_count - 1 - i] = tmp;
		i++;
	}
}

t_ex_ret		sort_symbols(t_bin_file *file)
{
	uint32_t	nsyms;

	if (opt_is_activated('p') == TRUE)
		return (SUCCESS);
	nsyms = swap_uint32_if(file->symtab_lc->nsyms, file->endian);
	if (merge_sort(file->symbols, 0, nsyms - 1, &alpha_sort_comp) == FAILURE)
		return (FAILURE);
	if (opt_is_activated('n') == TRUE)
	{
		if (merge_sort(file->symbols, 0, nsyms - 1, &value_sort_comp)
			== FAILURE)
			return (FAILURE);
	}
	if (opt_is_activated('r') == TRUE)
		reverse_symb_tab(file->symbols, nsyms);
	return (SUCCESS);
}
