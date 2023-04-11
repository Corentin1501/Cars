cmake_minimum_required(VERSION 3.5)

project(Cars)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Ajouter le chemin d'installation de Qt5 dans CMAKE_PREFIX_PATH
set(CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/cmake/Qt5" ${CMAKE_PREFIX_PATH})

# Trouver les composants Qt5 requis
find_package(Qt5 REQUIRED COMPONENTS Widgets OpenGL)

add_executable(${PROJECT_NAME}
    "main.cpp"
    # ajouter vos fichier sources et en-tÃªte
    # ...

# si ressources :
#    tp1.qrc

# si traductions :
#    ${QM_FILES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::OpenGL)
