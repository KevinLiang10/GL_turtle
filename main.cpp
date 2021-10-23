#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "turtle.h"
#include <iostream>

void processInput(GLFWwindow *window);

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

int main()
{
    Turtle turtle = Turtle(800,600,"syz");
    // render loop
    // -----------
    // build and compile our shader program
    // ------------------------------------
    // 创建一个顶点着色器 对象
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //把着色器源码附近到着色器去对象上
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    //编译着色器源码
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    //创建片段着色器


    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //把片段着色器源码附近到着色器对象上
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    //编译着色器源码
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    //创建一个 着色器程序对象，用于链接所有的着色器程序
    int shaderProgram = glCreateProgram();
    //附加顶点着色器
    glAttachShader(shaderProgram, vertexShader);
    //附加片段着色器
    glAttachShader(shaderProgram, fragmentShader);
    //链接着色器
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
 
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
         0.5f, -0.5f, 0.0f, // right
         0.0f,  0.5f, 0.0f  // top
    };
 
    unsigned int VBO, VAO;
    //使用一个缓冲ID生成一个顶点数组对象
    glGenVertexArrays(1, &VAO);
    //使用glGenBuffers函数和一个缓冲ID生成一个VBO对象：
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    //绑定顶点数组对象
    glBindVertexArray(VAO);
    //绑定顶点缓冲对象
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    /**
     使用顶点数据初始化 顶点缓冲对象
     GL_STATIC_DRAW ：数据不会或几乎不会改变。
     GL_DYNAMIC_DRAW：数据会被改变很多。
     GL_STREAM_DRAW ：数据每次绘制时都会改变。
     */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    /**
        设置顶点属性指针  =》 从顶点缓冲对象中 获取 顶点数据
        1，第一个参数，与顶点着色器 layout  location = 0  相对应  所以为 0
        2，第二参数：顶点数组每个数据都是一个vec3  总共三个  所以  是 3
        3，第三个参数：每个数据都是 float 类型    所以是  GL_FLOAT
        4，第四个参数： 数据是否需要标准化，标准化的时候 是：（-1，1）这里不需要标准化 （0，1） 所以是：GL_FALSE
        5，第五个参数：步长(Stride)，它告诉我们在连续的顶点属性组之间的间隔，因为下组位置是在 3个float 之后  所以是  3 * sizeof(float)
        6，第六个参数：类型是void*，所以需要我们进行这个奇怪的强制类型转换。它表示位置数据在缓冲中起始位置的偏移量(Offset)。由于位置数据在数组的开头，所以这里是0。我们会在后面详细解释这个参数。
        获取数据规则是：每个顶点属性从一个VBO管理的内存中获得它的数据，而具体是从哪个VBO（程序中可以有多个VBO）获取则是通过在调用glVertexAttribPointer时绑定到GL_ARRAY_BUFFER的VBO决定的。由于在调用glVertexAttribPointer之前绑定的是先前定义的VBO对象，顶点属性0现在会链接到它的顶点数据。
     */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //启用顶点数据，因起始位置是0  所以传 0
    glEnableVertexAttribArray(0);
 
    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
 
    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
 
 
    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
 
    // render loop
    // -----------
    while (!glfwWindowShouldClose(turtle.window))
    {
        // input
        // -----
        processInput(turtle.window);
 
        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
 
        // draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        /**
         1，第一个参数：图元的类型   三角形
         2，第二参数：顶点数组的起始索引，为 0
         3，第三个参数：总共绘制的顶点数：为3
         */
        glDrawArrays(GL_TRIANGLES, 0, 3);
//         glBindVertexArray(0); // no need to unbind it every time
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        //交互缓冲 防止闪烁
        glfwSwapBuffers(turtle.window);
        //事件监听
        glfwPollEvents();
    }
 
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    //删除顶点数组对象
    glDeleteVertexArrays(1, &VAO);
    //删除顶点缓冲对象
    glDeleteBuffers(1, &VBO);
    //删除着色器程序
    glDeleteProgram(shaderProgram);
 
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

