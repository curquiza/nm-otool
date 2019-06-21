#include "ft_nm.h"

void	clean(t_bin_file *file)
{
	free(file->symbols);
	file->symbols = NULL;
}
