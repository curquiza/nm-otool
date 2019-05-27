#include "ft_nm.h"

char	to_lower(char c)
{
    return (c ^ TOGGLE_CASE);
}

t_bool	is_external_symbol(char c)
{
	return (c == 'u' || c == 'a' || c == 'p' || c == 'i' || c == 'c'
		|| c == 't' || c == 'd' || c == 'b' || c == 's');
}

t_ex_ret	ret_malloc_err(void)
{
	ft_dprintf(2, "Error: impossible to malloc");
	return (FAILURE);
}

t_ex_ret	ret_usage(void)
{
	ft_dprintf(2, "Usage: ./ft_nm [-gjnpruU] binary_file \n");
	ft_dprintf(2, "  -g : display only global (external) symbols\n");
	ft_dprintf(2, "  -n : sort numerically rather than alphabetically\n");
	ft_dprintf(2, "  -p : don't sort; display in symbol-table order\n");
	ft_dprintf(2, "  -r : sort in reverse order\n");
	return (FAILURE);
}
