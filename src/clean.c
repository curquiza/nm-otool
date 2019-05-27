#include "ft_nm.h"

void	clean_magic64(t_bin_file *file)
{
	free(file->symbols);
	file->symbols = NULL;
}
