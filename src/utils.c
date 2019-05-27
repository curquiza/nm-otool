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
