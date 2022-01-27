#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>
//ע��ص����������ڵ������ڴ�С
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);


//׼��������ɫ��
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//׼��Ƭ����ɫ��
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor; \n"
"void main(){\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); \n"
"}\0";


int main() {
    //ʵ����GLFW����
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //�������ڶ���
    GLFWwindow* window = glfwCreateWindow(800, 600, "learnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //ע��ص����������ڵ������ڴ�С
    //���ǻ����Խ����ǵĺ���ע�ᵽ�����ܶ�Ļص������С�
    //����˵�����ǿ��Դ���һ���ص������������ֱ�����仯������������Ϣ�ȡ�
    //���ǻ��ڴ�������֮����Ⱦѭ����ʼ��֮ǰע����Щ�ص�������
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //��ʼ��GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    ////������Ⱦ���ڣ����ӿڣ�Viewport��,���ô��ڵ�ά��
    //glViewport(0, 0, 800, 600);

    //����������ɫ������
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);//����Ϊ������ɫ��
    //����ɫ��Դ�븽�Ӹ���ɫ������
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//'1'ָ�ַ�������
    glCompileShader(vertexShader);//������ɫ������
    //��֤��ɫ���Ƿ����ɹ�
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //����Ƭ����ɫ��
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //������ɫ������ʹ�øղű������ɫ�����Ǳ������������(Link)Ϊһ����ɫ���������
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    //����ɫ�����ӵ���ɫ��������
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    //��֤������ɫ�������Ƿ�ʧ��
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINK::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //��ɫ���������ӵ���������Ժ�ɾ����ɫ������
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //��׼�����꣬���������ζ�����������
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    //�������㻺�����Vertex buffer object��
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    //���������������(Vertex Array Object, VAO)
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    //��VAO
    glBindVertexArray(VAO);

    //ȷ����������
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //�� �������� ���Ƶ� �����ڴ� ����
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //������������
    // ��һ������ָ������Ҫ���õĶ������ԡ�
    // �ڶ�������ָ���������ԵĴ�С��
    // ����������ָ�����ݵ�����
    // ���ĸ����������Ƿ�ϣ�����ݱ���׼��
    // ���������Ϊ�����������Ķ���������֮��ļ��
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //?
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    


    //��Ⱦѭ��(Render Loop)
    while (!glfwWindowShouldClose(window)) {
        //����û��Ƿ����˷��ؼ�(Esc)
        processInput(window);

        //��Ⱦָ�����glClear�����������Ļ����ɫ���壩
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //��Ⱦ���򣬻�������
        //����������(����֮��ÿ����ɫ�����ú���Ⱦ���ö���ʹ������������)
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);



        //�����û�д���ʲô�¼������´���״̬�������ö�Ӧ�Ļص�����
        glfwSwapBuffers(window);
        //������ɫ����
        glfwPollEvents();
    }

    //ɾ������
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}



//ע��ص����������ڵ������ڴ�С
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

//���뺯��,������escape���˳�����
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}



