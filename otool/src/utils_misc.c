#include "ft_otool.h"

t_ex_ret	ret_malloc_err(void)
{
	ft_dprintf(2, "Error: impossible to malloc");
	return (FAILURE);
}

t_ex_ret	ret_usage(void)
{
	ft_dprintf(2, "Usage: ./ft_otool binary_file [...] \n");
	return (FAILURE);
}

t_bool		is_archi_x86_64(cpu_type_t cpu_type)
{
	return (cpu_type == CPU_TYPE_X86_64);
}
