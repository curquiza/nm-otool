#include "ft_nm.h"

static void		get_sections_indexes(t_bin_file *file, struct segment_command_64 *seg, uint8_t current_sect_index)
{
	uint32_t					i;
	struct section_64			*section;

	section = (struct section_64 *)((void *)seg + sizeof(*seg)); //check size
	i = 0;
	while (i < seg->nsects)
	{
		if (ft_strcmp(section->sectname, SECT_TEXT) == 0)
			file->text_index = current_sect_index + i;
		else if (ft_strcmp(section->sectname, SECT_DATA) == 0)
			file->data_index = current_sect_index + i;
		else if (ft_strcmp(section->sectname, SECT_BSS) == 0)
			file->bss_index = current_sect_index + i;
		i++;
		section = (struct section_64 *) ((void *)section + sizeof(struct section_64)); //check size
	}
}

static void		get_file_info(t_bin_file *file)
{
	uint32_t					i;
	uint8_t						section_index;
	struct load_command			*lc;
	struct mach_header_64		*header;
	struct segment_command_64	*seg;

	header = (struct mach_header_64 *)file->ptr;
	lc = file->ptr + sizeof(*header); //check size
	section_index = 1;
	i = 0;
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
			file->symtab_lc = (struct symtab_command *)lc; //check size
		else if (lc->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64 *)lc;
			get_sections_indexes(file, seg, section_index);
			section_index += seg->nsects;
		}
		i++;
		lc = (void *)lc + lc->cmdsize; //check size
	}
}

t_ex_ret		init_magic64(t_bin_file *file, void *ptr, size_t size)
{
	file->ptr = ptr;
	file->size = size;
	get_file_info(file);
	if (!(file->symbols = (t_symbol *)ft_memalloc(file->symtab_lc->nsyms * sizeof(*file->symtab_lc))))
		return (FAILURE);
	return (SUCCESS);
}
