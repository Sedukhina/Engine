file(GLOB_RECURSE CORE_SRC "*.h" "*.cpp")
add_library(Core SHARED ${CORE_SRC})

find_package(glm REQUIRED)
target_include_directories(Core PRIVATE ${glm_INCLUDE_DIRS})
target_link_libraries(Core PUBLIC glm::glm)

find_package(assimp CONFIG REQUIRED)
target_include_directories(Core PRIVATE ${assimp_INCLUDE_DIRS})
target_link_libraries(Core PRIVATE assimp::assimp)

find_package(stb REQUIRED)
target_include_directories(Core PRIVATE ${stb_INCLUDE_DIRS})
#target_link_libraries(Core PRIVATE stb)


target_include_directories(Core PUBLIC "${CURRENT_SOURCE_DIR}")
install(TARGETS Core EXPORT Core LIBRARY DESTINATION ${CMAKE_BINARY_DIR}/lib)
export(TARGETS Core FILE ${CMAKE_BINARY_DIR}/core/CoreConfig.cmake)
file(WRITE ${CMAKE_BINARY_DIR}/core/CoreConfig.cmake "")