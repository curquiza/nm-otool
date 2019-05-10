#include "ft_nm.h"

t_ex_ret	ft_nm(size_t size, void *ptr)
{
	uint32_t	magic_number;

	magic_number = *(uint32_t *)ptr;
	if (magic_number == MH_MAGIC)
	{
		ft_printf("MAGIC 32 bits\n");
	}
	else if (magic_number == MH_MAGIC_64)
	{
		ft_printf("MAGIC 64 bits\n");
		return (handle_magic_64(size, ptr));
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

int		main(int ac, char **av)
{
	int			fd;
	void		*ptr;
	struct stat buf;
	t_ex_ret	ret;

	ptr = NULL;

	if (ac != 2)
	{
		fprintf(stderr, "usage: nm binary_file [...]\n");
		return (FAILURE);
	}

	if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		fprintf(stderr, "open: error\n");
		return (FAILURE);
	}

	if ((fstat(fd, &buf)) < 0)
	{
		fprintf(stderr, "fstat: error\n");
		return (FAILURE);
	}

	if ((ptr = mmap(ptr, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		fprintf(stderr, "mmap: error\n");
		return (FAILURE);
	}

	ret = ft_nm(buf.st_size, ptr);

	if (munmap(ptr, buf.st_size) < 0)
	{
		fprintf(stderr, "munmap: error\n");
		return (FAILURE);
	}

	//close !!

	return (ret);
}

// TODO:
// - gerer les binaires compilés avec -g : N_STAB dans n_type ?
