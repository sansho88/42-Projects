# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.20
cmake_policy(SET CMP0009 NEW)

# MLX_SRC at CMakeLists.txt:8 (file)
file(GLOB NEW_GLOB LIST_DIRECTORIES true "/Users/tgriffit/projects/FDF/minilibx_macos/*.c")
set(OLD_GLOB
  "/Users/tgriffit/projects/FDF/minilibx_macos/font.c"
  "/Users/tgriffit/projects/FDF/minilibx_macos/mlx_int_str_to_wordtab.c"
  "/Users/tgriffit/projects/FDF/minilibx_macos/mlx_rgb.c"
  "/Users/tgriffit/projects/FDF/minilibx_macos/mlx_shaders.c"
  "/Users/tgriffit/projects/FDF/minilibx_macos/mlx_xpm.c"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/Users/tgriffit/projects/FDF/cmake-build-debug/CMakeFiles/cmake.verify_globs")
endif()

# MLX_SRC at CMakeLists.txt:8 (file)
file(GLOB NEW_GLOB LIST_DIRECTORIES true "/Users/tgriffit/projects/FDF/minilibx_macos/*.h")
set(OLD_GLOB
  "/Users/tgriffit/projects/FDF/minilibx_macos/mlx.h"
  "/Users/tgriffit/projects/FDF/minilibx_macos/mlx_int.h"
  "/Users/tgriffit/projects/FDF/minilibx_macos/mlx_new_window.h"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/Users/tgriffit/projects/FDF/cmake-build-debug/CMakeFiles/cmake.verify_globs")
endif()