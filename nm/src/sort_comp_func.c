#include "ft_nm.h"

t_bool	value_sort_comp(t_symbol *symb1, t_symbol *symb2)
{
	return (symb1->value > symb2->value);
}

t_bool	alpha_sort_comp(t_symbol *symb1, t_symbol *symb2)
{
	int cmp_ret;

	cmp_ret = ft_strcmp(symb1->name, symb2->name);
	if (cmp_ret == 0)
		return (value_sort_comp(symb1, symb2));
	return (cmp_ret > 0);
}
