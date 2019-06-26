/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_symb_output.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 13:28:06 by curquiza          #+#    #+#             */
/*   Updated: 2019/06/26 13:28:07 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static t_bool	no_display_needed(char type_char)
{
	return ((type_char == '-')
		|| (opt_is_activated('g') && is_external_symbol(type_char))
		|| (opt_is_activated('u') && !is_undefined_symb(type_char))
		|| (opt_is_activated('U') && is_undefined_symb(type_char)));
}

static void		basic_print(char type_char, char *name, uint64_t value,
					enum e_value value_type)
{
	if (is_undefined_symb(type_char))
	{
		if (value_type == VALUE_64)
			ft_printf("%18c %.538s", type_char, name);
		else
			ft_printf("%10c %.538s", type_char, name);
		ft_putchar('\n');
	}
	else
	{
		if (value_type == VALUE_64)
			ft_printf("%.16llx %c %.538s\n", value,
				type_char, name);
		else
			ft_printf("%.8llx %c %.538s\n", value,
				type_char, name);
	}
}

void			print_symbols_output(t_symbol *symbols, size_t sym_count,
					enum e_value value_type)
{
	size_t	i;

	i = 0;
	while (i < sym_count)
	{
		if (no_display_needed(symbols[i].type_char) == TRUE)
			;
		else if (opt_is_activated('j') || opt_is_activated('u'))
			ft_printf("%.538s\n", symbols[i].name);
		else
			basic_print(symbols[i].type_char, symbols[i].name, symbols[i].value,
				value_type);
		i++;
	}
}
