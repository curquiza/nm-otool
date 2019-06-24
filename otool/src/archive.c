#include "ft_otool.h"

static uint32_t	ft_padding_ar_mac(char *ar_name)
{
	uint32_t	ar_name_size;

	if ((ft_strncmp(ar_name, AR_EFMT1, ft_strlen(AR_EFMT1))) == 0)
		ar_name_size = ft_atoi(ar_name + ft_strlen(AR_EFMT1));
	else
		ar_name_size = 0;
	return (ar_name_size);
}

static t_ex_ret	exec_all_objetcs(t_bin_file *file, struct ranlib *symtab,
					uint32_t symtab_size, uint32_t string_table_size)
{
	struct ar_hdr		*obj_header;
	char				*obj_name;
	uint32_t			obj_size;

	obj_header = check_and_move(file, (void*)symtab
		+ symtab_size + sizeof(uint32_t)
		+ string_table_size, sizeof(*obj_header));
	g_title_display_inhib = TRUE;
	ft_printf("Archive : %s\n", file->filename);
	while (obj_header)
	{
		if (check_and_move(file, obj_header + 1, sizeof(*obj_name)) == NULL)
			return (ft_ret_err2(file->filename, MALF_OBJ_ERR));
		obj_name = (char *)(obj_header + 1);
		obj_size = ft_atoi(obj_header->ar_size);
		if (check_and_move(file, (void *)obj_name, obj_size) == NULL)
			return (ft_ret_err2(file->filename, MALF_OBJ_ERR));
		if (ft_otool(obj_size, (void *)obj_name
				+ ft_padding_ar_mac(obj_header->ar_name),
				obj_name, file->filename) == FAILURE)
			return (FAILURE);
		obj_header = check_and_move(file, (void *)obj_header
			+ sizeof(*obj_header) + obj_size, sizeof(*obj_header));
	}
	return (SUCCESS);
}

t_ex_ret		handle_archive(char *filename, uint64_t size, void *ptr)
{
	struct ar_hdr		*header;
	struct ranlib		*symtab;
	uint32_t			symtab_size;
	t_bin_file			file;
	uint32_t			string_table_size;

	file.filename = filename;
	file.size = size;
	file.ptr = ptr;
	if (!(header = (struct ar_hdr*)check_and_move(&file, ptr + SARMAG,
		sizeof(*header))))
		return (SUCCESS);
	symtab_size = *(uint32_t*)((void*)(header + 1)
		+ ft_padding_ar_mac(header->ar_name));
	if (check_and_move(&file, header + 1, sizeof(symtab_size)) == NULL)
		return (ft_ret_err2(filename, MALF_OBJ_ERR));
	symtab = (struct ranlib*)check_and_move(&file, (void*)(header + 1)
		+ ft_padding_ar_mac(header->ar_name)
		+ sizeof(uint32_t), sizeof(*symtab));
	if (symtab == NULL
		|| check_and_move(&file, (void*)symtab + symtab_size,
			sizeof(string_table_size)) == NULL)
		return (ft_ret_err2(file.filename, MALF_OBJ_ERR));
	string_table_size = *(uint32_t*)((void*)symtab + symtab_size);
	return (exec_all_objetcs(&file, symtab, symtab_size, string_table_size));
}
