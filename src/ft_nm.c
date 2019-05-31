#include "ft_nm.h"

t_ex_ret	ft_nm(uint64_t size, void *ptr, char *filename)
{
	uint32_t	magic_number;

	magic_number = *(uint32_t *)ptr;
	if (magic_number == MH_MAGIC)
	{
		// ft_printf("MAGIC 32 bits\n");
		return (handle_32(size, ptr, filename, MAGIC));
	}
	else if (magic_number == MH_MAGIC_64)
	{
		// ft_printf("MAGIC 64 bits\n");
		return (handle_64(size, ptr, filename, MAGIC));
	}
	else if (magic_number == MH_CIGAM)
	{
		// ft_printf("CIGAM 32 bits\n");
		return (handle_32(size, ptr, filename, CIGAM));
	}
	else if (magic_number == MH_CIGAM_64)
	{
		// ft_printf("CIGAM 64 bits\n");
		return (handle_64(size, ptr, filename, CIGAM));
	}
	else if (magic_number == FAT_MAGIC)
	{
		ft_printf("FAT_MAGIC 32\n");
		handle_fat32(filename, size, ptr, MAGIC);
	}
	else if (magic_number == FAT_MAGIC_64)
	{
		ft_printf("FAT_MAGIC 64\n");
	}
	else if (magic_number == FAT_CIGAM)
	{
		ft_printf("FAT_CIGAM 32\n");
		handle_fat32(filename, size, ptr, CIGAM);
	}
	else if (magic_number == FAT_CIGAM_64)
	{
		ft_printf("FAT_CIGAM 64\n");
	}
	else
	{
		ft_dprintf(2, "Wrong magic number : %x\n", magic_number);
	}
	return (FAILURE);
}
