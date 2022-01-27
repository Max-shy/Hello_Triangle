#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>
//注册回调函数，用于调整窗口大小
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);


//准备顶点着色器
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//准备片段着色器
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor; \n"
"void main(){\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); \n"
"}\0";


int main() {
    //实例化GLFW窗口
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //创建窗口对象
    GLFWwindow* window = glfwCreateWindow(800, 600, "learnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //注册回调函数，用于调整窗口大小
    //我们还可以将我们的函数注册到其它很多的回调函数中。
    //比如说，我们可以创建一个回调函数来处理手柄输入变化，处理错误消息等。
    //我们会在创建窗口之后，渲染循环初始化之前注册这些回调函数。
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    ////设置渲染窗口，即视口（Viewport）,设置窗口的维度
    //glViewport(0, 0, 800, 600);

    //创建顶点着色器对象
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);//参数为顶点着色器
    //将着色器源码附加给着色器对象
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//'1'指字符串数量
    glCompileShader(vertexShader);//编译着色器对象
    //验证着色器是否编译成功
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //创建片段着色器
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //创建着色器程序（使用刚才编译的着色器我们必须把它们链接(Link)为一个着色器程序对象）
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    //将着色器连接到着色器程序中
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    //验证链接着色器程序是否失败
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINK::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //着色器对象链接到程序对象以后，删除着色器对象
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //标准化坐标，创建三角形顶点坐标数组
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    //创建顶点缓冲对象（Vertex buffer object）
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    //创建顶点数组对象(Vertex Array Object, VAO)
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    //绑定VAO
    glBindVertexArray(VAO);

    //确定缓冲类型
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //将 顶点数据 复制到 缓冲内存 当中
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //解析顶点数据
    // 第一个参数指定我们要配置的顶点属性。
    // 第二个参数指定顶点属性的大小。
    // 第三个参数指定数据的类型
    // 第四个定义我们是否希望数据被标准化
    // 第五个参数为步长，连续的顶点属性组之间的间隔
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //?
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    


    //渲染循环(Render Loop)
    while (!glfwWindowShouldClose(window)) {
        //检查用户是否按下了返回键(Esc)
        processInput(window);

        //渲染指令（调用glClear函数来清空屏幕的颜色缓冲）
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //渲染程序，绘制物体
        //激活程序对象(调用之后，每个着色器调用和渲染调用都会使用这个程序对象)
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);



        //检查有没有触发什么事件、更新窗口状态，并调用对应的回调函数
        glfwSwapBuffers(window);
        //交换颜色缓冲
        glfwPollEvents();
    }

    //删除对象
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}



//注册回调函数，用于调整窗口大小
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

//输入函数,若输入escape，退出窗口
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}




