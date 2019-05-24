#include "ft_nm.h"

static void	bubble_sort(t_symbol *symbols, uint32_t symb_count, t_bool (*comp)(t_symbol *symb1, t_symbol *symb2))
{
	uint32_t	i;
	t_symbol	tmp;

	i = 0;
	while (i < symb_count - 1)
	{
		if (comp(symbols + i, symbols + i + 1) == TRUE)
		{
			tmp = symbols[i] ;
			symbols[i] = symbols[i + 1];
			symbols[i + 1] = tmp;
			i = 0;
			continue ;
		}
		i++;
	}

}

// t_bool	value_sort_comp(t_symbol *symb1, t_symbol *symb2)
// {
//	// sort by name sinon
// 	return (symb1->value > symb2->value);
// }

static t_bool	default_sort_comp(t_symbol *symb1, t_symbol *symb2)
{
	return (ft_strcmp(symb1->name, symb2->name) > 0);
}

void	sort_symbols(t_bin_file *file)
{
	//check options

	bubble_sort(file->symbols, file->symtab_lc->nsyms, &default_sort_comp);
}


