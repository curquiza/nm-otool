#include "ft_nm.h"

static t_ex_ret	process_all_files(int argc, char **argv, int first_file_index)
{
	t_ex_ret	ret;

	ret = SUCCESS;
	g_multi_display = (first_file_index == (argc - 1)) ? FALSE : TRUE;
	while (first_file_index < argc)
	{
		if (process_single_file(argv[first_file_index]) == FAILURE)
			ret = FAILURE;
		first_file_index++;
	}
	return (ret);
}

static int		get_all_options(int argc, char **argv)
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

static t_ex_ret	process_all_arguments(int argc, char **argv)
{
	int		first_file_index;

	if ((first_file_index = get_all_options(argc, argv)) == -1)
		return (FAILURE);
	return (process_all_files(argc, argv, first_file_index));
}

int				main(int argc, char **argv)
{
	g_flags = 0;
	if (argc < 2)
		return (ret_usage());
	return (process_all_arguments(argc, argv));
}

// TODO
// - a.out si 0 file trouvé
// - makefile
// - otool
