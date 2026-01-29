project('huffman', 'cpp',
    default_options : ['cpp_std=c++23'])

subdir('src')
#sources defined in ./src
include = include_directories('headers')
executable('huffman', sources: sources, include_directories: include)