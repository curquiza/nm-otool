#include "ft_nm.h"

char	to_lower(char c)
{
    return (c ^ TOGGLE_CASE);
}

t_ex_ret	ret_malloc_err(void)
{
	ft_dprintf(2, "Error: impossible to malloc");
	return (FAILURE);
}

t_ex_ret	ret_usage(void)
{
	ft_dprintf(2, "Usage: ./ft_nm [-gjnpruU] binary_file \n");
	return (FAILURE);
}
