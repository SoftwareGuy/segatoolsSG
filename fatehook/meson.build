shared_library(
    'fatehook',
    name_prefix : '',
    include_directories : inc,
    implicit_include_directories : false,
    vs_module_defs : 'fatehook.def',
    c_pch : '../precompiled.h',
    dependencies : [
        capnhook.get_variable('hook_dep'),
        capnhook.get_variable('hooklib_dep'),
    ],
    link_with : [
        aimeio_lib,
        amex_lib,
        board_lib,
        fateio_dll,
        hooklib_lib,		
        platform_lib,
        util_lib,
    ],
    sources : [
        'config.c',
        'config.h',
        'dllmain.c',
        'MinHook.h',
    ],
)
