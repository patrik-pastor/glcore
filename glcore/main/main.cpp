#include <iostream>

#include <glcore/core/application.hpp>
#include <glcore/main/example_layers/first_example.hpp>

int main() {
    glcore::Application app;
    app.PushLayer(new glcore::FirstExample);
    app.Run();
}
