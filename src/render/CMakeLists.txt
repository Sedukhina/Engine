add_library(Render STATIC "IRenderer.h" "InputCallback.h" "OpenGL/OpenGLRenderer.h" "OpenGL/OpenGLRenderer.cpp" "Renderer.h" "RendererInputComponent.h" "RendererInputComponent.cpp" "OpenGL/ShaderProgram.h" "OpenGL/ShaderProgram.cpp")
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


set(SHADERS_DIR ${CMAKE_BINARY_DIR}/render/Shaders/OGL_Shaders)
target_include_directories(Render PUBLIC ${SHADERS_DIR})
file(GLOB shaders "OpenGL/Shaders/*.vert" "OpenGL/Shaders/*.frag")

foreach(file ${shaders})
    message(STATUS "Copying resource ${file}")
    file(COPY ${file} DESTINATION ${SHADERS_DIR})
endforeach()

