#include "ft_nm.h"

static t_ex_ret		get_sections_indexes(t_bin_file *file,
						struct segment_command *seg,
						uint8_t current_sect_index)
{
	uint32_t			i;
	struct section		*section;
	uint32_t			seg_nsects;

	seg_nsects = swap_uint32_if(seg->nsects, file->endian);
	i = 0;
	while (i < seg_nsects)
	{
		section = (struct section *)check_and_move(file,
			(void *)seg + sizeof(*seg) + i * sizeof(*section),
			sizeof(*section));
		if (!section)
			return (ft_ret_err2(file->filename, FILE_END_ERR));
		if (ft_strcmp(section->sectname, SECT_TEXT) == 0)
			file->text_index = current_sect_index + i;
		else if (ft_strcmp(section->sectname, SECT_DATA) == 0)
			file->data_index = current_sect_index + i;
		else if (ft_strcmp(section->sectname, SECT_BSS) == 0)
			file->bss_index = current_sect_index + i;
		i++;
	}
	return (SUCCESS);
}

static t_ex_ret		get_info_from_lc(t_bin_file *file, struct load_command *lc,
						uint8_t *section_index)
{
	struct segment_command	*seg;
	uint32_t				lc_cmd;

	lc_cmd = swap_uint32_if(lc->cmd, file->endian);
	if (lc_cmd == LC_SYMTAB)
	{
		file->symtab_lc = (struct symtab_command *)check_and_move(file, lc,
			sizeof(*lc)); //check size
		if (!file->symtab_lc)
			return (ft_ret_err2(file->filename, FILE_END_ERR));
	}
	else if (lc_cmd == LC_SEGMENT)
	{
		seg = (struct segment_command *)check_and_move(file, lc, sizeof(*seg));
		if (!seg)
			return (ft_ret_err2(file->filename, FILE_END_ERR));
		if (get_sections_indexes(file, seg, *section_index) == FAILURE)
			return (FAILURE);
		*section_index += swap_uint32_if(seg->nsects, file->endian);
	}
	return (SUCCESS);
}

static t_ex_ret		init_lc_and_ncmds(t_bin_file *file, uint32_t *header_ncmds,
						struct load_command	**lc)
{
	struct mach_header	*header;

	header = (struct mach_header *)check_and_move(file, file->ptr,
		sizeof(*header));
	if (!header)
		return (ft_ret_err2(file->filename, VALID_OBJ_ERR));
	*lc = (struct load_command *)check_and_move(file,
		file->ptr + sizeof(*header), sizeof(**lc));
	if (!*lc)
		return (ft_ret_err2(file->filename, FILE_END_ERR));
	*header_ncmds = swap_uint32_if(header->ncmds, file->endian);
	return (SUCCESS);
}

static t_ex_ret		get_file_info(t_bin_file *file)
{
	uint32_t					i;
	struct load_command			*lc;
	uint32_t					header_ncmds;
	uint8_t						section_index;

	if (init_lc_and_ncmds(file, &header_ncmds, &lc) == FAILURE)
		return (FAILURE);
	section_index = 1;
	i = 0;
	while (i < header_ncmds)
	{
		// if (swap_uint32_if(lc->cmdsize, file->endian) % 8 != 0)
		// 	return (ft_ret_err2(file->filename, CMDSIZE_ERR));
		if (get_info_from_lc(file, lc, &section_index) == FAILURE)
			return (FAILURE);
		i++;
		lc = (struct load_command *)check_and_move(file,
			(void *)lc + swap_uint32_if(lc->cmdsize, file->endian),
			sizeof(*lc));
		if (i < header_ncmds && !lc)
			return (ft_ret_err2(file->filename, FILE_END_ERR));
	}
	return (SUCCESS);
}

t_ex_ret			init_32(t_bin_file *file)
{
	if (get_file_info(file) == FAILURE)
		return (FAILURE);
	if (file->symtab_lc)
	{
		if (!(file->symbols = (t_symbol *)
			ft_memalloc(swap_uint32_if(file->symtab_lc->nsyms, file->endian)
				* sizeof(*file->symtab_lc))))
			return (ret_malloc_err());
	}
	return (SUCCESS);
}
