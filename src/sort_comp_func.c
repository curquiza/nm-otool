#include "ft_nm.h"

t_bool	value_sort_comp(t_symbol *symb1, t_symbol *symb2)
{
	return (symb1->value > symb2->value);
}

t_bool	alpha_sort_comp(t_symbol *symb1, t_symbol *symb2)
{
	return (ft_strcmp(symb1->name, symb2->name) > 0);
}
