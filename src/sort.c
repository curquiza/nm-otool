#include "ft_nm.h"


static t_ex_ret	run_merge_sort(t_symbol *tab, int start1, int end1, int end2,
					t_bool (*comp)(t_symbol *symb1, t_symbol *symb2))
{
	t_symbol	*tmp;
	int		cpt1;
	int		cpt2;
	int		i;

	cpt1 = start1;
	cpt2 = end1 + 1;
	if (!(tmp = (t_symbol *)ft_memalloc(sizeof(*tmp) * (end1 - start1 + 1))))
		return (ret_malloc_err());
	ft_memmove(tmp, tab + start1, (end1 - start1 + 1) * sizeof(*tmp));
	i = start1;
	while (i <= end2)
	{
		if (cpt1 == end1 + 1)
			break ;
		else if (cpt2 == end2 + 1)
			tab[i] = tmp[cpt1++ - start1];
		else if (comp(tmp + cpt1 - start1, tab + cpt2) == FALSE)
			tab[i] = tmp[cpt1++ - start1];
		else
			tab[i] = tab[cpt2++];
		i++;
	}
	free(tmp);
	return (SUCCESS);
}

static t_ex_ret	merge_sort(t_symbol *tab, int start_index, int end_index,
					t_bool (*comp)(t_symbol *symb1, t_symbol *symb2))
{
	int		middle;

	middle = (end_index + start_index) / 2;
	if (start_index != end_index)
	{
		if (merge_sort(tab, start_index, middle, comp) == FAILURE
			|| merge_sort(tab, middle + 1, end_index, comp) == FAILURE
			|| run_merge_sort(tab, start_index, middle, end_index, comp)
				== FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}


// static void	bubble_sort(t_symbol *symbols, uint32_t symb_count, t_bool (*comp)(t_symbol *symb1, t_symbol *symb2))
// {
// 	uint32_t	i;
// 	t_symbol	tmp;

// 	i = 0;
// 	while (i < symb_count - 1)
// 	{
// 		if (comp(symbols + i, symbols + i + 1) == TRUE)
// 		{
// 			tmp = symbols[i] ;
// 			symbols[i] = symbols[i + 1];
// 			symbols[i + 1] = tmp;
// 			i = 0;
// 			continue ;
// 		}
// 		i++;
// 	}
// }

static void		reverse_symb_tab(t_symbol *tab, int tab_count)
{
	int			i;
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

t_ex_ret	sort_symbols(t_bin_file *file)
{
	if (opt_is_activated('p') == TRUE)
		return (SUCCESS);
	if (merge_sort(file->symbols, 0, file->symtab_lc->nsyms - 1,
			&alpha_sort_comp) == FAILURE)
		return (FAILURE);
	if (opt_is_activated('n') == TRUE)
	{
		if (merge_sort(file->symbols, 0, file->symtab_lc->nsyms - 1,
				&value_sort_comp) == FAILURE)
			return (FAILURE);
	}
	if (opt_is_activated('r') == TRUE)
	{
		reverse_symb_tab(file->symbols, file->symtab_lc->nsyms);
	}
	return (SUCCESS);
}


