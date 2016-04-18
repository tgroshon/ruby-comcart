require "mkmf"

# have_library("comcart","comcart_init")

extension_name = 'comcart'
dir_config(extension_name)
create_makefile(extension_name)
