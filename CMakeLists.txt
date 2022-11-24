cmake_minimum_required(VERSION 3.20)
project(ece_city_1_f C)

set(CMAKE_C_STANDARD 99)

add_executable(ece_city_1_f main.c menu.h menu.c jeu.c jeu.h construction.c construction.h eva.c eva.h)



message("LIBRARIES =${CMAKE_APPLE_SILICON_PROCESSOR}")
IF(WIN32)
    target_link_libraries(ece_city_1_f -lmingw32 -lallegro-5.0.10-monolith-md-debug)
ELSE()
    INCLUDE_DIRECTORIES(/opt/homebrew/Cellar/allegro/5.2.7.0/include)
    LINK_DIRECTORIES(/opt/homebrew/Cellar/allegro/5.2.7.0/lib)
    file(GLOB LIBRARIES "/opt/homebrew/Cellar/allegro/5.2.7.0/lib/*dylib")
    message("LIBRARIES=${LIBRARIES}")
    TARGET_LINK_LIBRARIES(ece_city_1_f ${LIBRARIES})


    set(CMAKE_OSX_ARCHITECTURES "x86_64")
    INCLUDE_DIRECTORIES(/usr/local/Cellar/allegro/5.2.7.0/include)
    LINK_DIRECTORIES(/usr/local/Cellar/allegro/5.2.7.0/lib)
    file(GLOB LIBRARIES "/usr/local/Cellar/allegro/5.2.7.0/lib/*.dylib")
    message("LIBRARIES = ${LIBRARIES}")
    TARGET_LINK_LIBRARIES(ece_city_1_f ${LIBRARIES})
ENDIF(WIN32)