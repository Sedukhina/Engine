set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(Core SHARED "Logger.h" "Logger.cpp" "Level.cpp" "core.h" "Input/InputController.h" "Input/InputController.cpp" "Object.h"  "BVH.h" "AssetManager/Mesh.h" "AssetManager/Asset.h"  "PhysicalPrimitives/Primitive.h" "PhysicalPrimitives/AABB.h" "PhysicalPrimitives/Box.h" "ObjectComponent.h"  "Input/InputScheme.h" "Input/InputScheme.cpp" "Input/InputComponent.h" "Camera.h" "Camera.cpp" "Player.h" "GameState.h" "GameState.cpp" "GetGameState.h" "GetGameState.cpp" "GlobalConstants.h" "GlobalConstants.cpp")
#file(GLOB CORE_SRC "*.h" "*.cpp")
#add_library(Core SHARED ${CORE_SRC})

find_package(glm REQUIRED)
target_include_directories(Core PRIVATE ${glm_INCLUDE_DIRS})
target_link_libraries(Core PUBLIC glm::glm)

find_package(assimp CONFIG REQUIRED)
target_include_directories(Core PRIVATE ${assimp_INCLUDE_DIRS})
target_link_libraries(main PRIVATE assimp::assimp)

target_include_directories(Core PUBLIC "${CURRENT_SOURCE_DIR}")
install(TARGETS Core EXPORT Core LIBRARY DESTINATION ${CMAKE_BINARY_DIR}/lib)
export(TARGETS Core FILE ${CMAKE_BINARY_DIR}/core/CoreConfig.cmake)
file(WRITE ${CMAKE_BINARY_DIR}/core/CoreConfig.cmake "")