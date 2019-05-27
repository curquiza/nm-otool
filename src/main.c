#include "ft_nm.h"

t_ex_ret	ft_nm(size_t size, void *ptr, char *filename)
{
	uint32_t	magic_number;

	magic_number = *(uint32_t *)ptr;
	if (magic_number == MH_MAGIC)
	{
		ft_printf("MAGIC 32 bits\n");
	}
	else if (magic_number == MH_MAGIC_64)
	{
		// ft_printf("MAGIC 64 bits\n");
		return (handle_magic_64(size, ptr, filename));
	}
	else if (magic_number == MH_CIGAM)
	{
		ft_printf("CIGAM 32 bits\n");
	}
	else if (magic_number == MH_CIGAM_64)
	{
		ft_printf("CIGAM 64 bits\n");
	}
	else
	{
		ft_dprintf(2, "Wrong magic number\n");
	}
	return (FAILURE);
}

static t_ex_ret	process_bin_file(char *filename)
{
	int			fd;
	void		*ptr;
	struct stat buf;
	t_ex_ret	ret;

	ptr = NULL;
	if ((fd = open(filename, O_RDONLY)) < 0)
		return (ft_ret_err2(filename, "open error"));
	if ((fstat(fd, &buf)) < 0)
		return (ft_ret_err2(filename, "fstat error"));
	if ((ptr = mmap(ptr, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
		== MAP_FAILED)
		return (ft_ret_err2(filename, "mmap error"));
	ret = ft_nm(buf.st_size, ptr, filename);
	if (munmap(ptr, buf.st_size) < 0)
		return (ft_ret_err2(filename, "munmap error"));
	if (close(fd) == -1)
		return (ft_ret_err2(filename, "close error"));
	return (ret);
}

int		main(int ac, char **av)
{
	g_flags = 0;
	if (ac != 2)
	{
		fprintf(stderr, "Usage: ./ft_nm binary_file [...]\n");
		return (FAILURE);
	}
	if (process_bin_file(av[1]) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
