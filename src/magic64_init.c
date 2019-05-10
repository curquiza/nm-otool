#include "ft_nm.h"

static uint32_t		get_sections_in_segment(t_file64 *file, struct load_command *lc, uint32_t section_index)
{
	uint32_t					i;
	struct segment_command_64	*seg;
	struct section_64			*first_section;

	seg = (struct segment_command_64 *)lc; //check size
	first_section = (struct section_64 *)((void *)lc + sizeof(*seg)); //check size
	i = 0;
	while (i < seg->nsects && (i + section_index) < file->section_count)
	{
		file->sections[i + section_index] = (void *)first_section + i * sizeof(struct section_64); //check size
		i++;
	}
	return (i);
}

static void		get_file_info(t_file64 *file)
{
	uint32_t				i;
	uint32_t				section_index;
	struct load_command		*lc;

	lc = file->ptr + sizeof(*file->header); //check size
	section_index = 0;
	i = 0;
	while (i < file->header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
			file->symtab_lc = (struct symtab_command *)lc; //check size
		else if (lc->cmd == LC_SEGMENT_64)
			section_index += get_sections_in_segment(file, lc, section_index);
		i++;
		lc = (void *)lc + lc->cmdsize; //check size
	}
}

static uint32_t	get_section_count(t_file64 *file)
{
	struct load_command			*lc;
	struct segment_command_64	*seg;
	uint32_t					i;
	uint32_t					count;

	lc = file->ptr + sizeof(*file->header); //check size
	count = 0;
	i = 0;
	while (i < file->header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64 *)lc; //check size
			count += seg->nsects;
		}
		i++;
		lc = (void *)lc + lc->cmdsize; //check size
	}
	return (count);
}

// static void	print_sections_table(t_file64 *file)
// {
// 	uint32_t i;

// 	i = 0;
// 	ft_printf("---------------\n");
// 	ft_printf("---------------\n");
// 	ft_printf("section count = %d\n", file->section_count);
// 	while (i < file->section_count)
// 	{
// 		ft_printf("------------\n");
// 		ft_printf("i = %d\n", i);
// 		ft_printf("section name = %s\n", file->sections[i]->sectname);
// 		i++;
// 	}
// 	ft_printf("---------------\n");
// 	ft_printf("---------------\n");
// }

t_ex_ret		init_magic64(t_file64 *file, void *ptr, size_t size)
{
	file->ptr = ptr;
	file->size = size;
	file->header = (struct mach_header_64 *)ptr; //check size
	file->section_count = get_section_count(file);
	if (!(file->sections = (struct section_64 **)ft_memalloc(sizeof(*file->sections) * file->section_count)))
		return (FAILURE);
	get_file_info(file);
	// print_sections_table(file);
	return (SUCCESS);
}
