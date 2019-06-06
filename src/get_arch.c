#include "ft_nm.h"

char	*get_archi_name(cpu_type_t cpu_type, cpu_subtype_t cpu_subtype)
{
	if (cpu_type == CPU_TYPE_I386)
		return ("i386");
	else if (cpu_type == CPU_TYPE_POWERPC)
		return ("ppc");
	else if (cpu_type == CPU_TYPE_POWERPC64)
		return ("ppc64");
	else if (cpu_type == CPU_TYPE_ARM64)
		return ("arm64");
	else if (cpu_type == CPU_TYPE_ARM  && cpu_subtype == CPU_SUBTYPE_ARM_V7)
		return ("armv7");
	else if (cpu_type == CPU_TYPE_ARM  && cpu_subtype == CPU_SUBTYPE_ARM_V7S)
		return ("armv7s");
	return ("");
}
