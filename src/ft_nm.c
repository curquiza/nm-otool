#include "ft_nm.h"

t_ex_ret	ft_nm(size_t size, void *ptr, char *filename)
{
	uint32_t	magic_number;

	magic_number = *(uint32_t *)ptr;
	if (magic_number == MH_MAGIC)
	{
		ft_printf("MAGIC 32 bits\n");
	}
	else if (magic_number == MH_MAGIC_64)
	{
		// ft_printf("MAGIC 64 bits\n");
		return (handle_magic_64(size, ptr, filename));
	}
	else if (magic_number == MH_CIGAM)
	{
		ft_printf("CIGAM 32 bits\n");
	}
	else if (magic_number == MH_CIGAM_64)
	{
		ft_printf("CIGAM 64 bits\n");
	}
	else
	{
		ft_dprintf(2, "Wrong magic number\n");
	}
	return (FAILURE);
}
