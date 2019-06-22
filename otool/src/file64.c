#include "ft_otool.h"

static t_ex_ret		get_text_info(t_bin_file *file,
						struct segment_command_64 *seg)
{
	uint32_t			i;
	struct section_64	*section;
	uint32_t			seg_nsects;

	seg_nsects = swap_uint32_if(seg->nsects, file->endian);
	i = 0;
	while (i < seg_nsects)
	{
		section = (struct section_64 *)check_and_move(file,
			(void *)seg + sizeof(*seg) + i * sizeof(*section),
			sizeof(*section));
		if (!section)
			return (ft_ret_err2(file->filename, FILE_END_ERR));
		if (ft_strcmp(section->sectname, SECT_TEXT) == 0)
		{
			file->text_offset = swap_uint32_if(section->offset, file->endian);
			file->text_address = swap_uint64_if(section->addr, file->endian);
			file->text_size = swap_uint64_if(section->size, file->endian);
		}
		i++;
	}
	return (SUCCESS);
}

static t_ex_ret		get_info_from_lc(t_bin_file *file, struct load_command *lc)
{
	struct segment_command_64	*seg;
	uint32_t					lc_cmd;

	lc_cmd = swap_uint32_if(lc->cmd, file->endian);
	if (lc_cmd == LC_SEGMENT_64)
	{
		seg = (struct segment_command_64 *)check_and_move(file, lc,
			sizeof(*seg));
		if (!seg)
			return (ft_ret_err2(file->filename, FILE_END_ERR));
		if (get_text_info(file, seg) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

static t_ex_ret		init_lc_and_header_info(t_bin_file *file,
						uint32_t *header_ncmds,
						struct load_command	**lc)
{
	struct mach_header_64	*header;

	header = (struct mach_header_64 *)check_and_move(file, file->ptr,
		sizeof(*header));
	if (!header)
		return (ft_ret_err2(file->filename, NOT_OBJ_ERR));
	*lc = (struct load_command *)check_and_move(file,
		file->ptr + sizeof(*header), sizeof(**lc));
	if (!*lc)
		return (ft_ret_err2(file->filename, FILE_END_ERR));
	*header_ncmds = swap_uint32_if(header->ncmds, file->endian);
	file->cpu_type = swap_uint32_if(header->cputype, file->endian);
	return (SUCCESS);
}

static t_ex_ret		init_64(t_bin_file *file)
{
	uint32_t			i;
	struct load_command	*lc;
	uint32_t			header_ncmds;

	if (init_lc_and_header_info(file, &header_ncmds, &lc) == FAILURE)
		return (FAILURE);
	i = 0;
	while (i < header_ncmds)
	{
		if (get_info_from_lc(file, lc) == FAILURE)
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

t_ex_ret			handle_64(uint64_t size, void *ptr, char *filename,
						enum e_endian endian)
{
	t_bin_file	file;

	ft_bzero(&file, sizeof(file));
	file.filename = filename;
	file.ptr = ptr;
	file.size = size;
	file.endian = endian;
	if (init_64(&file) == FAILURE)
		return (FAILURE);
	return (print_output(&file, VALUE_64));
}
