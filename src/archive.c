#include "ft_nm.h"

static uint32_t	ft_padding_ar_mac(char *ar_name)
{
	uint32_t	ar_name_size;

	if ((ft_strncmp(ar_name, AR_EFMT1, ft_strlen(AR_EFMT1))) == 0)
	{
		ar_name_size = ft_atoi(ar_name + ft_strlen(AR_EFMT1));
		// printf("ar name size: %d\n", ar_name_size);
	}
	else
		ar_name_size = 0;
	return (ar_name_size);
}

t_ex_ret	 handle_archive(char *filename, uint64_t size, void *ptr)
{
	struct ar_hdr		*header;
	uint32_t		symtab_size;
	struct ranlib		*symtab;
	t_bin_file			file;
	uint32_t			obj_size;

	file.filename = filename;
	file.size = size;
	file.ptr = ptr;

	header = (struct ar_hdr*)(ptr + SARMAG);
	symtab_size = *(uint32_t*)((void*)(header + 1) + ft_padding_ar_mac(header->ar_name));
	// nsyms = symtab_size / sizeof(struct ranlib);
	symtab = (struct ranlib*) ((void*)(header + 1) + ft_padding_ar_mac(header->ar_name) + sizeof(uint32_t));

	// char	 *string_table;
	uint32_t	string_table_size;

	string_table_size = *(uint32_t*)((void*)symtab + symtab_size);
	// string_table = (void*)symtab + symtab_size + sizeof(uint32_t);

	struct ar_hdr		*object_header;
	char				*object_name;

	object_header = check_and_move(&file, (void*)symtab + symtab_size + sizeof(uint32_t) + string_table_size, sizeof(*object_header));

	while (object_header)
	{
		object_name = (char *)(object_header + 1);
		obj_size = ft_atoi(object_header->ar_size);
		// ft_printf("object name: %s\n", object_name);
		ft_nm(obj_size, (void *)object_name + ft_padding_ar_mac(object_header->ar_name), object_name, filename);
		// object_header = check_and_move(&file, (void *)object_name + ft_strlen(object_name) + ft_padding_ar_mac(object_header->ar_name) + obj_size, sizeof(*object_header));
		object_header = check_and_move(&file, (void *)object_header + sizeof(*object_header) + obj_size, sizeof(*object_header));


		// /!\ checker que ya de la place pour le fichier .o aussi !
	}

	return (SUCCESS);
}
