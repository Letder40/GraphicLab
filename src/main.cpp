#include <cstdlib>
#ifdef CLANG_COMPLETE_ONLY
    #define GL_GLEXT_PROTOTYPES
    #include <GL/gl.h>
    #include <GL/glext.h>
#else
    #include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>
#include <cstdio>

const float vertices[] = {
    0.5f,  0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f,
   -0.5f,  0.5f, 0.0f,
};

const uint32_t indices[] = {
    0, 1, 3,
    1, 2, 3
};

struct VertexArray {
    uint32_t id = 0;

    VertexArray() { glGenVertexArrays(1, &id); };
    ~VertexArray() { glDeleteVertexArrays(1, &id); };

    void bind() { glBindVertexArray(id); };
};

struct GLBuffer {
    uint32_t id = 0;
    GLenum type = 0;

    GLBuffer(GLenum type, size_t size, const void* data, GLenum usage) {
        this->type = type;
        glGenBuffers(1, &id);
        glBindBuffer(type, id);
        glBufferData(type, size, data, usage);
    }

    ~GLBuffer() { glDeleteBuffers(1, &id); };

    void bind() { glBindBuffer(type, id); };
};

struct Shaders {
    const char* vertex_shader_src = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;

    void main() {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    }
    )";

    const char* fragment_shader_src = R"(
    #version 330 core
    out vec4 FragColor;

    void main() {
        FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    }
    )";

    const char* fragment_shader2_src = R"(
    #version 330 core
    out vec4 FragColor;

    void main() {
        FragColor = vec4(0.0f, 0.0f, 0.8f, 1.0f);
    }
    )";
};

struct ShaderProgram {
    uint32_t id = 0;

    ShaderProgram(const char* vert_src, const char* frag_src) {
        id = glCreateProgram();
        auto compile = [](const char* src, GLenum type) -> uint32_t {
            uint32_t shader = glCreateShader(type);    
            glShaderSource(shader, 1, &src, nullptr);
            glCompileShader(shader);

            int success;
            char log[512];
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

            if (!success) {
                glGetShaderInfoLog(shader, 512, nullptr, log);
                fprintf(stderr, "ERROR::SHADER::COMPILATION_FAILLED\n%s\n", log);
            }

            return shader;
        };
        
        uint32_t vert = compile(vert_src, GL_VERTEX_SHADER);
        uint32_t frag = compile(frag_src, GL_FRAGMENT_SHADER);

        glAttachShader(id, vert);
        glAttachShader(id, frag);
        glLinkProgram(id);

        glDeleteShader(vert);
        glDeleteShader(frag);
    };

    ~ShaderProgram() { glDeleteProgram(id); }

    void use() const { glUseProgram(id); }
};

class Window {
    GLFWwindow* window;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
        (void)window;
    }

    public:
    Window() {
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow* window = glfwCreateWindow(800, 600, "test", NULL, NULL);
        if (!window) {
            fprintf(stderr, "Error: Failled to create a windows\n");
            glfwTerminate();
            exit(1);
        }

        glfwMakeContextCurrent(window);

        glViewport(0, 0, 800, 600);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        this->window = window;
    }

    ~Window() { glfwTerminate(); };

    int should_close() { return glfwWindowShouldClose(window); };

    void swap_buffers() { glfwSwapBuffers(window); };

    void poll_events() { glfwPollEvents(); };

    void process_input() {
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }
};

int main () {
    Window window;

#ifndef CLANG_COMPLETE_ONLY
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return -1;
    }
#endif

    // OpenGL Objects
    VertexArray vao;
    vao.bind();

    GLBuffer vbo(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    GLBuffer ebo(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Shaders
    Shaders shaders;
    ShaderProgram shader_program(shaders.vertex_shader_src, shaders.fragment_shader_src);
    ShaderProgram shader_program2(shaders.vertex_shader_src, shaders.fragment_shader2_src);

    while (!window.should_close()) {
        window.process_input();
        
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        vao.bind();
        shader_program.use();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        shader_program2.use();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(sizeof(uint32_t) * 3));

        window.poll_events();
        window.swap_buffers();
    }

    glfwTerminate();
}
