#include "ft_nm.h"

void		print_symbols_output(t_symbol *symbols, size_t sym_count)
{
	size_t	i;

	i = 0;
	while (i < sym_count)
	{
		if (symbols[i].type_char == '-')
			;
		else if (symbols[i].type_char == 'U' || symbols[i].type_char == 'u')
			ft_printf("%18c %s\n", symbols[i].type_char, symbols[i].name);
		else
			ft_printf("%.16llx %c %s\n", symbols[i].value, symbols[i].type_char, symbols[i].name);
		i++;
}
	}
