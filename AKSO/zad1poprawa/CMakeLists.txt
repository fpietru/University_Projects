cmake_minimum_required(VERSION 3.16)
project(MooreAutomaton C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wno-implicit-fallthrough -fPIC -g -O0")

# Flagi linkera z --wrap do przechwytywania alokacji pamięci
set(MEMORY_WRAP_FLAGS "-Wl,--wrap=malloc;-Wl,--wrap=calloc;-Wl,--wrap=realloc;-Wl,--wrap=reallocarray;-Wl,--wrap=free;-Wl,--wrap=strdup;-Wl,--wrap=strndup")

# Dodaj bibliotekę współdzieloną
add_library(ma SHARED
        ma.c
        memory_tests.c
)

# Dodaj flagi linkera do biblioteki
target_link_options(ma PRIVATE ${MEMORY_WRAP_FLAGS})

# Testy: ma_tests (linkowane z libma)
add_executable(ma_tests
        ma_tests.c
)

# Dołącz katalog nagłówków do testów
target_include_directories(ma_tests PRIVATE ${CMAKE_SOURCE_DIR})

# Linkuj testy z biblioteką
target_link_libraries(ma_tests
        ma
)

# Ustaw rpath, żeby ma_tests widziało libma.so bez instalacji
set_target_properties(ma_tests PROPERTIES
        BUILD_RPATH "${CMAKE_BINARY_DIR}"
        INSTALL_RPATH "${CMAKE_BINARY_DIR}"
)
