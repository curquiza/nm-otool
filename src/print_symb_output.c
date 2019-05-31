#include "ft_nm.h"

void		print_symbols_output(t_symbol *symbols, size_t sym_count,
				enum e_value value_type)
{
	size_t	i;

	i = 0;
	while (i < sym_count)
	{
		if (symbols[i].type_char == '-')
			;
		else if (opt_is_activated('g')
			&& is_external_symbol(symbols[i].type_char))
			;
		else if (opt_is_activated('u')
			&& !is_undefined_symb(symbols[i].type_char))
			;
		else if (opt_is_activated('U')
			&& is_undefined_symb(symbols[i].type_char))
			;
		else if (opt_is_activated('j') || opt_is_activated('u'))
			ft_printf("%.538s\n", symbols[i].name);
		else if (is_undefined_symb(symbols[i].type_char)
			|| symbols[i].type_char == 'I')
		{
			if (value_type == VALUE_64)
				ft_printf("%18c %.538s", symbols[i].type_char, symbols[i].name);
			else
				ft_printf("%10c %.538s", symbols[i].type_char, symbols[i].name);
			if (symbols[i].type_char == 'I' && ft_strcmp(symbols[i].name, BAD_STRING_INDEX) == 0)
				ft_putstr(" (indirect for ?)");
			ft_putchar('\n');
		}
		else
		{
			if (value_type == VALUE_64)
				ft_printf("%.16llx %c %.538s\n", symbols[i].value,
					symbols[i].type_char, symbols[i].name);
			else
				ft_printf("%.8llx %c %.538s\n", symbols[i].value,
					symbols[i].type_char, symbols[i].name);
		}
		i++;
	}
}
