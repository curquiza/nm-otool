#include "ft_nm.h"

static char	*get_archi_name(cpu_type_t cpu_type, cpu_subtype_t cpu_subtype)
{
	// ft_printf("archi = %d\n", cpu_type);
	// ft_printf("sub archi = %d\n", cpu_subtype);

	if (cpu_type == CPU_TYPE_I386)
		return ("i386");
	else if (cpu_type == CPU_TYPE_POWERPC)
		return ("ppc");
	else if (cpu_type == CPU_TYPE_POWERPC64)
		return ("ppc64");
	else if (cpu_type == CPU_TYPE_X86_64)
		return ("x86_64");
	else if (cpu_type == CPU_TYPE_ARM64)
		return ("arm64");
	else if (cpu_type == CPU_TYPE_ARM  && cpu_subtype == CPU_SUBTYPE_ARM_V7)
		return ("armv7");
	else if (cpu_type == CPU_TYPE_ARM  && cpu_subtype == CPU_SUBTYPE_ARM_V7S)
		return ("armv7s");
	return ("");
}

static t_ex_ret	if_same_arch_process(void *ptr, enum e_endian endian, char *filename)
{
	struct fat_header	*header;
	uint32_t			arch_nb;
	struct fat_arch		*arch;

	header = (struct fat_header*)ptr;
	arch_nb = swap_uint32_if(header->nfat_arch, endian);
	arch = ptr + sizeof(struct fat_header);
	while (arch_nb--)
	{
		if (is_archi_x86_64(swap_uint32_if(arch->cputype, endian)) == TRUE)
			return (ft_nm(swap_uint32_if(arch->size, endian),
						ptr + swap_uint32_if(arch->offset, endian), filename));
		arch++;
	}
	return (-1);
}

static t_ex_ret not_same_arch_process(void *ptr, enum e_endian endian, char *filename)
{
	struct fat_header	*header;
	uint32_t			arch_nb;
	struct fat_arch		*arch;
	cpu_type_t			cpu_type;
	cpu_subtype_t		cpu_subtype;

	header = (struct fat_header*)ptr;
	arch_nb = swap_uint32_if(header->nfat_arch, endian);
	arch = ptr + sizeof(struct fat_header);
	while (arch_nb--)
	{
		cpu_type = swap_uint32_if(arch->cputype, endian);
		cpu_subtype = swap_uint32_if(arch->cpusubtype, endian);
		ft_printf("\n%s (for architecture %s):\n",
			filename, get_archi_name(cpu_type, cpu_subtype));
		if (ft_nm(swap_uint32_if(arch->size, endian),
			ptr + swap_uint32_if(arch->offset, endian), filename) == FAILURE)
			return (FAILURE);
		arch++;
	}
	return (SUCCESS);
}

t_ex_ret	handle_fat32(char *filename, uint64_t size, void *ptr,
				enum e_endian endian)
{

	t_ex_ret			ret;

	(void)size;
	ret = if_same_arch_process(ptr, endian, filename);
	if (ret == FAILURE || ret == SUCCESS)
		return (ret);
	return (not_same_arch_process(ptr, endian, filename));
}
