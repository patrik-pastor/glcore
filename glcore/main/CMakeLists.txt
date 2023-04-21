add_executable(main
        ${THIRD_PARTY_DIRECTORY}/glad/glad.c

        ${THIRD_PARTY_DIRECTORY}/imgui/imgui.cpp
        ${THIRD_PARTY_DIRECTORY}/imgui/imgui_draw.cpp
        ${THIRD_PARTY_DIRECTORY}/imgui/imgui_tables.cpp
        ${THIRD_PARTY_DIRECTORY}/imgui/imgui_widgets.cpp
        ${THIRD_PARTY_DIRECTORY}/imgui/imgui_demo.cpp
        ${THIRD_PARTY_DIRECTORY}/imgui/backends/imgui_impl_glfw.cpp
        ${THIRD_PARTY_DIRECTORY}/imgui/backends/imgui_impl_opengl3.cpp

        ../core/window.cpp
        ../core/linux_window.cpp
        ../core/application.cpp
        ../core/layer.cpp
        ../core/layer_stack.cpp
        ../core/input.cpp

        ../events/event.cpp
        ../events/application_event.cpp
        ../events/key_event.cpp
        ../events/mouse_event.cpp

        ../renderer/orthographic_camera.cpp
        ../renderer/orthographic_camera_controller.cpp
        ../renderer/shader.cpp

        ../utils/random.cpp

        ../imgui/imgui_layer.cpp

        example_layers/first_example.cpp

        main.cpp)
target_include_directories(main PRIVATE ${THIRD_PARTY_DIRECTORY}/imgui)
target_link_libraries(main PRIVATE glfw)

add_library(glcore
        ${THIRD_PARTY_DIRECTORY}/glad/glad.c

        ${THIRD_PARTY_DIRECTORY}/imgui/imgui.cpp
        ${THIRD_PARTY_DIRECTORY}/imgui/imgui_draw.cpp
        ${THIRD_PARTY_DIRECTORY}/imgui/imgui_tables.cpp
        ${THIRD_PARTY_DIRECTORY}/imgui/imgui_widgets.cpp
        ${THIRD_PARTY_DIRECTORY}/imgui/imgui_demo.cpp
        ${THIRD_PARTY_DIRECTORY}/imgui/backends/imgui_impl_glfw.cpp
        ${THIRD_PARTY_DIRECTORY}/imgui/backends/imgui_impl_opengl3.cpp

        ../core/window.cpp
        ../core/linux_window.cpp
        ../core/application.cpp
        ../core/layer.cpp
        ../core/layer_stack.cpp
        ../core/input.cpp

        ../events/event.cpp
        ../events/application_event.cpp
        ../events/key_event.cpp
        ../events/mouse_event.cpp

        ../renderer/orthographic_camera.cpp
        ../renderer/orthographic_camera_controller.cpp
        ../renderer/shader.cpp

        ../utils/random.cpp

        ../imgui/imgui_layer.cpp)
target_include_directories(glcore PRIVATE ${THIRD_PARTY_DIRECTORY}/imgui)
target_link_libraries(glcore PRIVATE glfw)
