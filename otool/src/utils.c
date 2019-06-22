#include "ft_otool.h"

t_bool		is_archi_x86_64(cpu_type_t cpu_type)
{
	return (cpu_type == CPU_TYPE_X86_64);
}
