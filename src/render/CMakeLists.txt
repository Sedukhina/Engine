add_library(Render STATIC "IRenderer.h" "InputCallback.h" "OpenGL/OpenGLRenderer.h" "OpenGL/OpenGLRenderer.cpp" "Renderer.h" "RendererInputComponent.h" "RendererInputComponent.cpp")
target_include_directories(Render PUBLIC "${CURRENT_SOURCE_DIR}")

find_package(glfw3 REQUIRED)
target_include_directories(Render PRIVATE ${glfw3_INCLUDE_DIRS})
target_link_libraries(Render PUBLIC glfw)

find_package(GLEW REQUIRED)
target_include_directories(Render PRIVATE ${GLEW_INCLUDE_DIRS})
target_link_libraries(Render PUBLIC GLEW::GLEW)

install(TARGETS Render EXPORT Render LIBRARY DESTINATION ${CMAKE_BINARY_DIR}/lib)
export(TARGETS Render FILE ${CMAKE_BINARY_DIR}/render/RenderConfig.cmake)
file(WRITE ${CMAKE_BINARY_DIR}/render/RenderConfig.cmake "")
