#include "ft_nm.h"

static t_ex_ret	process_single_bin_file(char *filename)
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

static t_ex_ret	process_all_files(int argc, char **argv, int first_file_index)
{
	t_ex_ret	ret;
	t_bool		display_name;

	ret = SUCCESS;
	display_name = (first_file_index == (argc - 1)) ? FALSE : TRUE;
	while (first_file_index < argc)
	{
		if (display_name == TRUE)
			ft_printf("\n%s:\n", argv[first_file_index]);
		if ((ret = process_single_bin_file(argv[first_file_index]) == FAILURE))
			ret = FAILURE;
		first_file_index++;
	}
	return (ret);
}

static int	get_all_options(int argc, char **argv)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (*argv[i] != '-')
			return (i);
		if (ft_strcmp(argv[i], "--") == 0)
			return (i + 1);
		(argv[i])++;
		while (*argv[i])
		{
			if (activate_opt(*argv[i]) == FAILURE)
				return (-1);
			(argv[i])++;
		}
		i++;
	}
	return (i);
}

static t_ex_ret process_all_arguments(int argc, char **argv)
{
	int		first_file_index;

	if ((first_file_index = get_all_options(argc, argv)) == -1)
		return (FAILURE);
	return (process_all_files(argc, argv, first_file_index));
}

int		main(int argc, char **argv)
{
	g_flags = 0;
	if (argc < 2)
		return (ret_usage());
	return (process_all_arguments(argc, argv));
}
