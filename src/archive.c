#include "ft_nm.h"

static uint32_t	ft_padding_ar_mac(char *ar_name)
{
	uint32_t	ar_name_size;

	if ((ft_strncmp(ar_name, AR_EFMT1, ft_strlen(AR_EFMT1))) == 0)
		ar_name_size = ft_atoi(ar_name + ft_strlen(AR_EFMT1));
	else
		ar_name_size = 0;
	return (ar_name_size);
}

static t_ex_ret	exec_all_objetcs(t_bin_file *file, struct ranlib *symtab, uint32_t symtab_size)
{
	struct ar_hdr		*obj_header;
	char				*obj_name;
	uint32_t			obj_size;
	uint32_t			string_table_size;

	if (check_and_move(file, (void*)symtab + symtab_size, sizeof(string_table_size)) == NULL)
		return (ft_ret_err2(file->filename, FILE_END_ERR));
	string_table_size = *(uint32_t*)((void*)symtab + symtab_size);
	obj_header = check_and_move(file, (void*)symtab + symtab_size + sizeof(uint32_t) + string_table_size, sizeof(*obj_header));
	while (obj_header)
	{
		if (check_and_move(file, obj_header + 1, sizeof(*obj_name)) == NULL)
			return (ft_ret_err2(file->filename, FILE_END_ERR));
		obj_name = (char *)(obj_header + 1);
		obj_size = ft_atoi(obj_header->ar_size);
		if (check_and_move(file, (void *)obj_name, obj_size) == NULL)
			return (ft_ret_err2(file->filename, FILE_END_ERR));
		if (ft_nm(obj_size, (void *)obj_name + ft_padding_ar_mac(obj_header->ar_name), obj_name, file->filename) == FAILURE)
			return (FAILURE);
		obj_header = check_and_move(file, (void *)obj_header + sizeof(*obj_header) + obj_size, sizeof(*obj_header));
	}
	return (SUCCESS);
}

t_ex_ret	 handle_archive(char *filename, uint64_t size, void *ptr)
{
	struct ar_hdr		*header;
	struct ranlib		*symtab;
	uint32_t			symtab_size;
	t_bin_file			file;

	file.filename = filename;
	file.size = size;
	file.ptr = ptr;
	// header = (struct ar_hdr*)(ptr + SARMAG);
	header = (struct ar_hdr*)check_and_move(&file, ptr + SARMAG, sizeof(*header));
	if (!header)
		return (ft_ret_err2(filename, FILE_END_ERR));
	symtab_size = *(uint32_t*)((void*)(header + 1) + ft_padding_ar_mac(header->ar_name));
	// symtab_size = *(uint32_t*)((void*)(header + 1) + ft_padding_ar_mac(header->ar_name));
	if (check_and_move(&file, header + 1, sizeof(symtab_size)) == NULL)
		return (ft_ret_err2(filename, FILE_END_ERR));
	// symtab = (struct ranlib*) ((void*)(header + 1) + ft_padding_ar_mac(header->ar_name) + sizeof(uint32_t));
	symtab = (struct ranlib*)check_and_move(&file, (void*)(header + 1) + ft_padding_ar_mac(header->ar_name) + sizeof(uint32_t), sizeof(*symtab));
	if (symtab == NULL)
		return (ft_ret_err2(filename, FILE_END_ERR));
	return (exec_all_objetcs(&file, symtab, symtab_size));
}
