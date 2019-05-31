#include "ft_nm.h"

static char	*get_archi_name(cpu_type_t cpu_type)
{
	if (cpu_type == CPU_TYPE_I386)
		return ("i386");
	else if (cpu_type == CPU_TYPE_POWERPC)
		return ("ppc");
	else if (cpu_type == CPU_TYPE_POWERPC64)
		return ("ppc64");
	return ("?");
}

t_ex_ret	handle_fat32(char *filename, uint64_t size, void *ptr,
				enum e_endian endian)
{
	struct fat_header	*header;
	uint32_t			nb_arch;
	struct fat_arch		*arch;

	header = (struct fat_header*)ptr;
	nb_arch = swap_uint32_if(header->nfat_arch, endian);
	ft_printf("nb arch: %d\n", nb_arch);
	arch = ptr + sizeof(struct fat_header);
	while (nb_arch--)
	{
		// ft_printf("size = %d\n", swap_uint32_if(arch->size, endian));
		// ft_printf("offset = %d\n", swap_uint32_if(arch->offset, endian));
		ft_printf("\n%s (for architecture %s):\n", filename, get_archi_name(swap_uint32_if(arch->cputype, endian)));
		ft_nm(swap_uint32_if(arch->size, endian), ptr + swap_uint32_if(arch->offset, endian), filename);
		arch++;
	}
	return (SUCCESS);
}
