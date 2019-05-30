#include "ft_nm.h"

static t_ex_ret		get_sections_indexes(t_bin_file *file,
						struct segment_command_64 *seg,
						uint8_t current_sect_index)
{
	uint32_t					i;
	struct section_64			*section;
	uint32_t					seg_nsects;

	// section = (struct section_64 *)((void *)seg + sizeof(*seg)); //check size
	// section = (struct section_64 *)check_and_move(file, (void *)seg + sizeof(*seg), sizeof(*section));
	// if (!section)
	// 	return (ft_ret_err2(file->filename, VALID_OBJ_ERR));
	seg_nsects = swap_uint32_if(seg->nsects, file->endian);
	i = 0;
	while (i < seg_nsects)
	{
		section = (struct section_64 *)check_and_move(file,
			(void *)seg + sizeof(*seg) + i * sizeof(*section),
			sizeof(*section));
		if (!section)
			return (ft_ret_err2(file->filename, VALID_OBJ_ERR));
		if (ft_strcmp(section->sectname, SECT_TEXT) == 0)
			file->text_index = current_sect_index + i;
		else if (ft_strcmp(section->sectname, SECT_DATA) == 0)
			file->data_index = current_sect_index + i;
		else if (ft_strcmp(section->sectname, SECT_BSS) == 0)
			file->bss_index = current_sect_index + i;
		i++;
		// section = (struct section_64 *) ((void *)section + sizeof(*section)); //check size
		// section = (struct section_64 *)check_and_move(file, (void *)section + sizeof(*section), sizeof(*section));
		// if (!section)
		// 	return (ft_ret_err2(file->filename, VALID_OBJ_ERR));
	}
	return (SUCCESS);
}

static t_ex_ret		get_info_from_lc(t_bin_file *file, struct load_command *lc,
						uint8_t *section_index)
{
	struct segment_command_64	*seg;
	uint32_t					lc_cmd;

	lc_cmd = swap_uint32_if(lc->cmd, file->endian);
	if (lc_cmd == LC_SYMTAB)
	{
		// file->symtab_lc = (struct symtab_command *)lc; //check size
		file->symtab_lc = (struct symtab_command *)check_and_move(file, lc, sizeof(*lc)); //check size
		if (!file->symtab_lc)
			return (ft_ret_err2(file->filename, VALID_OBJ_ERR));
	}
	else if (lc_cmd == LC_SEGMENT_64)
	{
		// seg = (struct segment_command_64 *)lc;
		seg = (struct segment_command_64 *)check_and_move(file, lc, sizeof(*seg));
		if (!seg)
			return (ft_ret_err2(file->filename, VALID_OBJ_ERR));
		if (get_sections_indexes(file, seg, *section_index) == FAILURE)
			return (FAILURE);
		*section_index += swap_uint32_if(seg->nsects, file->endian);
	}
	return (SUCCESS);
}

static t_ex_ret		get_file_info(t_bin_file *file)
{
	uint32_t					i;
	uint8_t						section_index;
	struct load_command			*lc;
	struct mach_header_64		*header;
	uint32_t					header_ncmds;

	// header = (struct mach_header_64 *)file->ptr;
	header = (struct mach_header_64 *)check_and_move(file, file->ptr,
		sizeof(*header));
	// lc = file->ptr + sizeof(*header);
	lc = (struct load_command *)check_and_move(file,
		file->ptr + sizeof(*header), sizeof(*lc));
	if (!header || !lc)
		return (ft_ret_err2(file->filename, VALID_OBJ_ERR));
	section_index = 1;
	header_ncmds = swap_uint32_if(header->ncmds, file->endian);
	i = 0;
	while (i < header_ncmds)
	{
		if (swap_uint32_if(lc->cmdsize, file->endian) % 8 != 0)
			return (ft_ret_err2(file->filename, CMDSIZE_ERR));
		if (get_info_from_lc(file, lc, &section_index) == FAILURE)
			return (FAILURE);
		i++;
		// lc = (void *)lc + lc->cmdsize; //check size)
		lc = (struct load_command *)check_and_move(file,
			(void *)lc + swap_uint32_if(lc->cmdsize, file->endian),
			sizeof(*lc)); //check size
		if (i < header_ncmds && !lc) // sinon on peut depasser la taille du fichier sans que ce soit important car fin de boucle
			return (ft_ret_err2(file->filename, VALID_OBJ_ERR));
	}
	return (SUCCESS);
}

t_ex_ret			init_64(t_bin_file *file)
{
	if (get_file_info(file) == FAILURE)
		return (FAILURE);
	if (file->symtab_lc)
	{
		if (!(file->symbols = (t_symbol *)ft_memalloc(file->symtab_lc->nsyms
				* sizeof(*file->symtab_lc))))
			return (ret_malloc_err());
	}
	return (SUCCESS);
}
