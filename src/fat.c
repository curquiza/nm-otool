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

static t_ex_ret	if_same_arch_process(t_bin_file *file)
{
	struct fat_header	*header;
	uint32_t			arch_nb;
	struct fat_arch		*arch;

	// header = (struct fat_header*)file->ptr;
	if (!(header = (struct fat_header*)check_and_move(file, file->ptr,
			sizeof(*header))))
		return (ft_ret_err2(file->filename, VALID_OBJ_ERR));
	arch_nb = swap_uint32_if(header->nfat_arch, file->endian);
	// arch = file->ptr + sizeof(struct fat_header);
	arch = (struct fat_arch *)check_and_move(file, file->ptr + sizeof(struct fat_header), sizeof(*arch));
	if (!arch)
		return (ft_ret_err2(file->filename, FILE_END_ERR));
	while (arch_nb--)
	{
		if (is_archi_x86_64(swap_uint32_if(arch->cputype, file->endian)))
			return (ft_nm(swap_uint32_if(arch->size, file->endian),
					file->ptr + swap_uint32_if(arch->offset, file->endian),
					file->filename));
		arch = (struct fat_arch *)check_and_move(file, arch + 1, sizeof(*arch));
		if (!arch)
			return (ft_ret_err2(file->filename, FILE_END_ERR));
	}
	return (-1);
}

static t_ex_ret not_same_arch_process(t_bin_file *file)
{
	struct fat_header	*header;
	uint32_t			arch_nb;
	struct fat_arch		*arch;
	cpu_type_t			cpu_type;
	cpu_subtype_t		cpu_subtype;

	// header = (struct fat_header*)file->ptr;
	if (!(header = (struct fat_header*)check_and_move(file, file->ptr,
			sizeof(*header))))
		return (ft_ret_err2(file->filename, VALID_OBJ_ERR));
	arch_nb = swap_uint32_if(header->nfat_arch, file->endian);
	arch = (struct fat_arch *)check_and_move(file, file->ptr + sizeof(struct fat_header), sizeof(*arch));
	if (!arch)
		return (ft_ret_err2(file->filename, FILE_END_ERR));
	while (arch_nb--)
	{
		cpu_type = swap_uint32_if(arch->cputype, file->endian);
		cpu_subtype = swap_uint32_if(arch->cpusubtype, file->endian);
		ft_printf("\n%s (for architecture %s):\n",
			file->filename, get_archi_name(cpu_type, cpu_subtype));

		if (!check_and_move(file, file->ptr + swap_uint32_if(arch->offset, file->endian), 1))
			return (ft_ret_err2(file->filename, FILE_END_ERR));

		if (ft_nm(swap_uint32_if(arch->size, file->endian),
			file->ptr + swap_uint32_if(arch->offset, file->endian),
			file->filename) == FAILURE)
			return (FAILURE);
		arch = (struct fat_arch *)check_and_move(file, arch + 1, sizeof(*arch));
		if (!arch)
			return (ft_ret_err2(file->filename, FILE_END_ERR));
	}
	return (SUCCESS);
}

t_ex_ret	handle_fat32(char *filename, uint64_t size, void *ptr,
				enum e_endian endian)
{
	t_bin_file			file;
	t_ex_ret			ret;

	file.filename = filename;
	file.size = size;
	file.ptr = ptr;
	file.endian = endian;
	ret = if_same_arch_process(&file);
	if (ret == FAILURE || ret == SUCCESS)
		return (ret);
	return (not_same_arch_process(&file));
}
