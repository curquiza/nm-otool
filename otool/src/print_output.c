#include "ft_otool.h"

static void	print_compacted(t_bin_file *file, size_t i)
{
	size_t	cpt;
	void	*offset;

	// offset = check_and_move(file, (void *)file->ptr + file->text_offset + i, sizeof(uint8_t);
	// if (offset == NULL)
	// 	return (ft_ret_err2(file->filename, FILE_END_ERR));
	cpt = 0;
	while (cpt < 16)
	{
		offset = (void *)file->ptr + file->text_offset + i + cpt;
		if (offset >= (void *)file->ptr + file->text_offset + file->text_size)
			return ;
		ft_printf("%-9.8x", *(uint32_t *)offset); // check size
		cpt += 4;
	}
}

static void	print_spaced(t_bin_file *file, size_t i)
{
	size_t	cpt;
	void	*offset;

	// offset = check_and_move(file, (void *)file->ptr + file->text_offset + i, sizeof(uint8_t);
	// if (offset == NULL)
	// 	return (ft_ret_err2(file->filename, FILE_END_ERR));
	cpt = 0;
	while (cpt < 16)
	{
		offset = (void *)file->ptr + file->text_offset + i + cpt;
		if (offset >= (void *)file->ptr + file->text_offset + file->text_size)
			return ;
		ft_printf("%-3.2hhx", *(uint8_t *)offset); // check size
		cpt++;
	}
}

void		print_output(t_bin_file *file, enum e_value value_type)
{
	size_t	i;

	ft_printf("%s:\n", file->filename);
	ft_printf("%s\n", TITLE);
	i = 0;
	while (i < file->text_size)
	{
		if (value_type == VALUE_64)
			ft_printf("%.16llx\t", file->text_address + i);
		else
			ft_printf("%.8llx\t", file->text_address + i);

		// if (file->cpu_type == CPU_TYPE_POWERPC
		// 	|| file->cpu_type == CPU_TYPE_POWERPC64)
		// 	print_compacted(file, i);
		// else
		if (file->cpu_type == CPU_TYPE_X86 || file->cpu_type == CPU_TYPE_X86_64
			|| file->cpu_type == CPU_TYPE_I386)
			print_spaced(file, i);
		else
			print_compacted(file, i);
		ft_putchar('\n');
		i += 16;
	}
}
