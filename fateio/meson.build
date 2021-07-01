fateio_dll = shared_library(
	'fateio',
	name_prefix : '',
	include_directories : inc,
	implicit_include_directories : false,
	vs_module_defs : 'fategoio.def',
	c_pch : '../precompiled.h',
	dependencies : [
		xinput_lib,
	],
	link_with : [
		util_lib,
	],
	sources : [
		'fateio.c',
		'fateio.h',
	],
)
