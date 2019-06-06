#include "ft_nm.h"

static int     ft_padding_ar_mac(char *ar_name)
{
    int     ar_name_size;

    if ((ft_strncmp(ar_name, AR_EFMT1, ft_strlen(AR_EFMT1))) == 0)
    {
        ar_name_size = ft_atoi(ar_name + ft_strlen(AR_EFMT1));
        printf("ar name size: %d\n", ar_name_size);
    }
    else
        ar_name_size = 0;
    return (ar_name_size);
}

t_ex_ret     handle_archive(char *filename, uint64_t size, void *ptr)
{
    struct ar_hdr       *header;
    char                *long_name;
    unsigned int        symtab_size;
    unsigned int        nb_items;
    struct ranlib       *obj;

    (void)filename;
    (void)size;

    header = (struct ar_hdr*)(ptr + SARMAG);
    printf("sizeof ar_hdr: %lu\n", sizeof(struct ar_hdr));

    write(1, "\n", 1);
    write(1, header->ar_name, 16);
    write(1, header->ar_date, 12);
    write(1, "\n", 1);
    write(1, header->ar_uid, 6);
    write(1, "\n", 1);
    write(1, header->ar_gid, 6);
    write(1, "\n", 1);
    write(1, header->ar_mode, 8);
    write(1, "\n", 1);
    write(1, header->ar_size, 10);
    write(1, "\n", 1);
    write(1, header->ar_fmag, 2);
    write(1, "\n", 1);

    long_name = (char*)(header + 1);
    printf("longname: %s\n", long_name);

    symtab_size = *(unsigned int*)((void*)(header + 1) + ft_padding_ar_mac(header->ar_name));
    printf("size of symble table: %d\n", symtab_size);

    nb_items = symtab_size / sizeof(struct ranlib);
    printf("nb items: %d\n", nb_items);

    obj = (struct ranlib*) ((void*)(header + 1) + ft_padding_ar_mac(header->ar_name) + sizeof(unsigned int));
    printf("ran_strx: %d\n", obj->ran_un.ran_strx);
    printf("ran_off: %u\n", obj->ran_off);
    printf("object name: %s\n", ptr + obj->ran_un.ran_strx);

    return (0);
}
