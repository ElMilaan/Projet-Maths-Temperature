cmake_minimum_required(VERSION 3.15)
project(Temperature)

# Définir le standard C++ à utiliser
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Choix du compilateur selon le système
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "Utilisation du compilateur GCC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message(STATUS "Utilisation du compilateur MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(STATUS "Utilisation du compilateur Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

# Activer les messages de debug pour CMake
set(CMAKE_VERBOSE_MAKEFILE ON)

# Créer une liste des fichiers sources
set(SOURCES
    src/source.cpp
    src/scene.cpp
    src/temperature.cpp
    src/fileSC.cpp
    src/fenetre.cpp
    src/radiateur.cpp
    src/main.cpp
)

# Vérifier l'existence des fichiers
foreach(SOURCE ${SOURCES})
    if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE})
        message(FATAL_ERROR "Le fichier source ${SOURCE} n'existe pas!")
    endif()
endforeach()

# Créer l'exécutable
add_executable(${PROJECT_NAME} ${SOURCES})

# Ajouter le répertoire des headers
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/headers
)
