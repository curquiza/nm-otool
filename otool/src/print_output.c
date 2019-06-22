#include "ft_otool.h"

static t_ex_ret	print_compacted(t_bin_file *file, size_t i)
{
	size_t	cpt;
	void	*offset;

	cpt = 0;
	while (cpt < 16)
	{
		offset = (void *)file->ptr + file->text_offset + i + cpt;
		if (check_and_move(file, offset, sizeof(uint32_t)) == NULL)
			return (ft_ret_err2(file->filename, FILE_END_ERR));
		if (offset >= (void *)file->ptr + file->text_offset + file->text_size)
			return (SUCCESS);
		ft_printf("%-9.8x", swap_uint32_if(*(uint32_t *)offset, file->endian));
		cpt += 4;
	}
	return (SUCCESS);
}

static t_ex_ret	print_spaced(t_bin_file *file, size_t i)
{
	size_t	cpt;
	void	*offset;

	cpt = 0;
	while (cpt < 16)
	{
		offset = (void *)file->ptr + file->text_offset + i + cpt;
		if (check_and_move(file, offset, sizeof(uint8_t)) == NULL)
			return (ft_ret_err2(file->filename, FILE_END_ERR));
		if (offset >= (void *)file->ptr + file->text_offset + file->text_size)
			return (SUCCESS);
		ft_printf("%-3.2hhx", (uint8_t)swap_uint32_if(*(uint32_t *)offset,
			file->endian));
		cpt++;
	}
	return (SUCCESS);
}

t_ex_ret		print_output(t_bin_file *file, enum e_value value_type)
{
	size_t	i;

	if (g_fat_title_display == FALSE)
		ft_printf("%s:\n", file->filename);
	ft_printf("%s\n", TITLE);
	i = 0;
	while (i < file->text_size)
	{
		if (value_type == VALUE_64)
			ft_printf("%.16llx\t", file->text_address + i);
		else
			ft_printf("%.8llx\t", file->text_address + i);
		if (file->cpu_type == CPU_TYPE_X86 || file->cpu_type == CPU_TYPE_X86_64
			|| file->cpu_type == CPU_TYPE_I386)
		{
			if (print_spaced(file, i) == FAILURE)
				return (FAILURE);
		}
		else if (print_compacted(file, i) == FAILURE)
			return (FAILURE);
		ft_putchar('\n');
		i += 16;
	}
	return (SUCCESS);
}
