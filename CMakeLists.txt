# Defina a versão mínima do CMake
cmake_minimum_required(VERSION 3.15)

# Defina o nome do projeto
project(conway-s-game-of-life C)

# Defina o diretório de saída para os binários compilados
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

# Ativar o CMake para buscar dependências automaticamente
include(FetchContent)

# Baixar a SDL3 do repositório do GitHub
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG release-3.2.8  # Versão desejada da SDL3
)

# Baixar e configurar SDL3
FetchContent_MakeAvailable(SDL3)

# Adicionar os diretórios de cabeçalhos (incluindo a pasta 'src')
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${SDL3_SOURCE_DIR}/include)

# Adicionar os arquivos de código-fonte
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.c")

# Criar o executável com o código-fonte
add_executable(conway_game_of_life ${SOURCES})

# Linkar a SDL3 ao seu projeto
target_link_libraries(conway_game_of_life PRIVATE SDL3::SDL3)

# Defina as flags de compilação
set_target_properties(conway_game_of_life PROPERTIES
    C_STANDARD 99
)
