#include "ft_nm.h"

t_ex_ret	ret_malloc_err(void)
{
	ft_dprintf(2, "Error: impossible to malloc");
	return (FAILURE);
}

t_ex_ret	ret_usage(void)
{
	ft_dprintf(2, "Usage: ./ft_nm [-gjnpruU] binary_file [...] \n");
	ft_dprintf(2, "  -g : display only global (external) symbols\n");
	ft_dprintf(2, "  -j : just display the symbol names (no value or type)\n");
	ft_dprintf(2, "  -n : sort numerically rather than alphabetically\n");
	ft_dprintf(2, "  -p : don't sort; display in symbol-table order\n");
	ft_dprintf(2, "  -r : sort in reverse order\n");
	ft_dprintf(2, "  -u : display only undefined symbols\n");
	ft_dprintf(2, "  -U : don't display undefined symbols\n");
	return (FAILURE);
}
