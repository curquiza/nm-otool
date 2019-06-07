#include "ft_nm.h"

t_ex_ret	activate_opt(char opt_letter)
{
	char		*opt;
	uint32_t	opt_mask;

	if (!(opt = ft_strchr(OPTIONS, opt_letter)))
	{
		ft_dprintf(2, "Error: -%c: Invalid option\n", opt_letter);
		return (FAILURE);
	}
	opt_mask = (1 << (opt - OPTIONS));
	g_flags |= opt_mask;
	return (SUCCESS);
}

t_bool		opt_is_activated(char opt_letter)
{
	char		*opt;
	uint32_t	opt_mask;

	if (!(opt = ft_strchr(OPTIONS, opt_letter)))
		return (FALSE);
	opt_mask = (1 << (opt - OPTIONS));
	return ((g_flags & opt_mask) == opt_mask);
}
