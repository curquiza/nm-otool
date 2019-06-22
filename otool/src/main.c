#include "ft_otool.h"

static t_ex_ret	process_single_file(char *filename)
{
	int			fd;
	void		*ptr;
	struct		stat buf;
	t_ex_ret	ret;

	ptr = NULL;
	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		if (errno == EACCES)
			return (ft_ret_err2(filename, PERM_ERR));
		if (errno == ENOENT)
			return (ft_ret_err2(filename, NO_FILE_ERR));
		return (ft_ret_err2(filename, "Open error"));
	}
	if ((fstat(fd, &buf)) < 0)
		return (ft_ret_err2(filename, "Fstat error"));
	if (S_ISDIR(buf.st_mode))
		return (ft_ret_err2(filename, IS_DIR_ERR));
	if ((ptr = mmap(ptr, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
		== MAP_FAILED)
		return (ft_ret_err2(filename, NOT_OBJ_ERR));
	ret = ft_otool(buf.st_size, ptr, filename, NULL);
	if (munmap(ptr, buf.st_size) < 0)
		return (ft_ret_err2(filename, "Munmap error"));
	if (close(fd) == -1)
		return (ft_ret_err2(filename, "Close error"));
	return (ret);
}

int			main(int argc, char **argv)
{
	g_multi_display = FALSE;
	g_title_display_inhib = FALSE;
	if (argc < 2)
		return (ret_usage());
	return (process_single_file(argv[1]));
}

// TODO :
// - multi display
// - pour chaque fichier, reset g_title_display_inhib à FALSE
