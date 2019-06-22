#include "ft_otool.h"

static void	display_name(char *filename, char *archive_name)
{
	if (!archive_name && g_multi_display == TRUE)
		ft_printf("%s:\n", filename);
	else if (archive_name)
		ft_printf("%s(%s):\n", archive_name, filename);
}

t_ex_ret	ft_otool(uint64_t size, void *ptr, char *filename, char *archive_name)
{
	uint32_t	magic_number;

	display_name(filename, archive_name);
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
		// ft_printf("FAT_MAGIC 32\n");
		return (handle_fat32(filename, size, ptr, MAGIC));
	}
	else if (magic_number == FAT_MAGIC_64)
	{
		return (handle_fat64(filename, size, ptr, MAGIC));
		// ft_printf("FAT_MAGIC 64\n");
	}
	else if (magic_number == FAT_CIGAM)
	{
		// ft_printf("FAT_CIGAM 32\n");
		return (handle_fat32(filename, size, ptr, CIGAM));
	}
	else if (magic_number == FAT_CIGAM_64)
	{
		// ft_printf("FAT_CIGAM 64\n");
		return (handle_fat64(filename, size, ptr, CIGAM));
	}
	else if (ft_strncmp((char *)ptr, ARMAG, SARMAG) == 0)
	{
		// ft_printf("ARCHIVE\n");
		return (handle_archive(filename, size, ptr));
	}
	else
	{
		ft_dprintf(2, "Unknown magic number : %x\n", magic_number);
	}
	return (FAILURE);
}
