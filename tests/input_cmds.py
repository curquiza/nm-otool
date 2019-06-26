INPUT_CMDS = [
    { 'cmd': 'nm/ft_nm tests/input/32_exe_hard',                     'error': False,  'output': '32_exe_hard.output' },
    { 'cmd': 'nm/ft_nm tests/input/64_bundle',                       'error': False,  'output': '64_bundle.output' },
    { 'cmd': 'nm/ft_nm tests/input/64_exe_easy',                     'error': False,  'output': '64_exe_easy.output' },
    { 'cmd': 'nm/ft_nm tests/input/64_exe_hard',                     'error': False,  'output': '64_exe_hard.output' },
    { 'cmd': 'nm/ft_nm tests/input/64_exe_medium',                   'error': False,  'output': '64_exe_medium.output' },
    { 'cmd': 'nm/ft_nm tests/input/64_lib_dynamic_hard',             'error': False,  'output': '64_lib_dynamic_hard.output' },
    { 'cmd': 'nm/ft_nm tests/input/64_lib_dynamic_medium',           'error': False,  'output': '64_lib_dynamic_medium.output' },
    # { 'cmd': 'nm/ft_nm tests/input/MachO-OSX-ppc-and-i386-bash',     'error': False,  'output': 'MachO-OSX-ppc-and-i386-bash.output'},
    { 'cmd': 'nm/ft_nm tests/input/MachO-OSX-x64-ls',                'error': False,  'output': 'MachO-OSX-x64-ls.output' },
    { 'cmd': 'nm/ft_nm tests/input/MachO-OSX-x86-ls',                'error': False,  'output': 'MachO-OSX-x86-ls.output' },
    { 'cmd': 'nm/ft_nm tests/input/MachO-iOS-arm1176JZFS-bash',      'error': False,  'output': 'MachO-iOS-arm1176JZFS-bash.output' },
    { 'cmd': 'nm/ft_nm tests/input/MachO-iOS-armv7s-Helloworld',     'error': False,  'output': 'MachO-iOS-armv7s-Helloworld.output' },
    { 'cmd': 'nm/ft_nm tests/input/fat_hard',                        'error': False,  'output': 'fat_hard.output' },
    # { 'cmd': 'nm/ft_nm tests/input/lib_archive_medium',              'error': False,  'output': 'lib_archive_medium.output' },
    { 'cmd': 'nm/ft_nm tests/input/object_easy',                     'error': False,  'output': 'object_easy.output' },
    { 'cmd': 'nm/ft_nm tests/input/object_medium',                   'error': False,  'output': 'object_medium.output' },
    { 'cmd': 'nm/ft_nm tests/input/test_32',                         'error': False,  'output': 'test_32.output' },
    { 'cmd': 'nm/ft_nm tests/input/test_64',                         'error': False,  'output': 'test_64.output' },
    { 'cmd': 'nm/ft_nm tests/input/MachO-OSX-ppc-openssl-1.0.1h',    'error': False,  'output': 'MachO-OSX-ppc-openssl-1.0.1h.output' },
    { 'cmd': 'nm/ft_nm tests/input/global',                          'error': False,  'output': 'global.output' },

    { 'cmd': 'nm/ft_nm -r tests/input/object_medium',                'error': False, 'output': 'reverse_1.output' },
    { 'cmd': 'nm/ft_nm -r tests/input/64_exe_hard',                  'error': False, 'output': 'reverse_2.output' },
    { 'cmd': 'nm/ft_nm -p tests/input/test_64',                      'error': False, 'output': 'opt_p_1.output' },
    { 'cmd': 'nm/ft_nm -n tests/input/test_64',                      'error': False, 'output': 'opt_n_1.output' },
    { 'cmd': 'nm/ft_nm -u tests/input/basic_64',                     'error': False, 'output': 'opt_u_1.output' },
    { 'cmd': 'nm/ft_nm -U tests/input/basic_64',                     'error': False, 'output': 'opt_big_u_1.output' },

    { 'cmd': 'nm/ft_nm -n -r tests/input/64_bundle',                 'error': False, 'output': 'multi_opt_1.output' },
    { 'cmd': 'nm/ft_nm -gn tests/input/basic_64',                    'error': False, 'output': 'multi_opt_2.output' },
    { 'cmd': 'nm/ft_nm -jgn tests/input/basic_64',                   'error': False, 'output': 'multi_opt_3.output' },
]


# test multi fichier
# tests options mixees
