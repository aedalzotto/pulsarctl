project('pulsarctl', 'cpp', version: '1.0.0', default_options : ['cpp_std=c++17'])

# Define source files
src_files = ['src/main.cpp', 'src/Pulsar.cpp', 'src/Cmdline.cpp']

# Define the target executable
pulsarctl = executable(
    'pulsarctl', src_files,
    include_directories: ['src/include'],
    dependencies: [
        dependency('hidapi'), 
        dependency('argparse')
    ],
	install : true,
)

# Install udev rules file
install_data('60-pulsar.rules', install_dir: '/etc/udev/rules.d/')
