#include "ft_nm.h"

static t_ex_ret	ft_nm(size_t size, void *ptr, char *filename)
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
		return (handle_magic_64(size, ptr, filename, MAGIC));
	}
	else if (magic_number == MH_CIGAM)
	{
		ft_printf("CIGAM 32 bits\n");
	}
	else if (magic_number == MH_CIGAM_64)
	{
		ft_printf("CIGAM 64 bits\n");
		// return (handle_magic_64(size, ptr, filename, CIGAM));
	}
	else
	{
		ft_dprintf(2, "Wrong magic number : %x\n", magic_number);
	}
	return (FAILURE);
}

t_ex_ret	process_single_file(char *filename, t_bool multi_display)
{
	int			fd;
	void		*ptr;
	struct stat buf;
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
		return (ft_ret_err2(filename, VALID_OBJ_ERR));

	// check ici si archive (.a) :
	// if archive
	//	boucler sur les files dans l'archives
	//		ft_nm(buf.st_size, ptr, filename, archive);
	// else
	//	affichage du name (si multi_display == true)
	//	ft_nm(buf.st_size, ptr, filename, NULL);
	if (multi_display == TRUE)
		ft_printf("\n%s\n", filename);
	ret = ft_nm(buf.st_size, ptr, filename);

	// ou archivage dans nm = on appelle nm en récursive:
	// on remplit g_filename
	// puis on appelle nm avec un param pour savoir si on est en archive ou non (pour le display)
	// dans nm, le premier truc qu'on fait une fois qu'on sait dans quel type de bin on est : afficher le nom si besoin
	// du coup, multi_display peut passer en variable globale

	if (munmap(ptr, buf.st_size) < 0)
		return (ft_ret_err2(filename, "Munmap error"));
	if (close(fd) == -1)
		return (ft_ret_err2(filename, "Close error"));
	return (ret);
}
