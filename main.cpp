 #include<iostream>

#include"glframework/core.h"

#include "wrapper/checkError.h"
#include "application/Application.h"
#include "glframework/shader.h"
#include "glframework/texture.h"

#include "application/camera/trackBallCameraControl.h"
#include "application/camera/GameCameraControl.h"
#include "application/camera/perspectiveCamera.h"
#include "application/camera/orthographicCamera.h"

#include "application/imGui/imGui_user.h"

GLuint vao;

Texture* foxTexture = nullptr;
Texture* groundTexture = nullptr;
Shader* shader = nullptr;

//���
Camera* camera = nullptr;
OrthographicCamera* orthographicCamera = nullptr;
PerspectiveCamera* perspectiveCamera = nullptr;
//�������
CameraControl* cameraControl = nullptr;
GameCameraControl* gameCameraControl = nullptr;
TrackBallCameraControl* trackBallCameraControl = nullptr;


GUI* imGui = nullptr;

glm::mat4 Utransform(1.0);
glm::mat4 UtransformFox(1.0);

void onResize(int width, int heiht) {
    GL_CALL(glViewport(0, 0, width, heiht));
    //���Ե����Ƿ���Ч(�����ڴ�С�����仯ʱ)
    std::cout << "���ǣ�����������" << std::endl;
}

void onKey(int key, int scancode, int action, int mods)
{
    cameraControl->onKey(key, action, mods);
}

void onMouse(int button, int action, int mods) {
    double x, y;
    application->getCursorPosition(&x, &y);
    cameraControl->onMouse(button, action, x, y);
}

void onCousor(double xpos, double ypos) {
    cameraControl->onCursor(xpos, ypos);
}

void onScroll(double offset) {
    cameraControl->onScroll(offset);
}

void prepareShader() {
    //ֱ�Ӵ��� shader
    shader = new Shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
}

void prepareVAO() {
    /*float positions[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
    };*/
    
    float positions[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
    };

    //������ɫ����
    float colors[] = {
         1.0f,    0.0f,    0.0f,
         0.0f,    1.0f,     0.0f,
         0.0f,     0.0f,     1.0f,
         0.5f, 0.5f, 0.5f,
    };

    float uvs[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
    };

    unsigned int indices[] = {
        0,1,2,
        2,1,3,
    };

    GLuint posVbo, colorVbo, uvVbo;
    glGenBuffers(1, &posVbo);
    glBindBuffer(GL_ARRAY_BUFFER, posVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    //����������ɫ����
    glGenBuffers(1, &colorVbo);
    glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    glGenBuffers(1, &uvVbo);
    glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, posVbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

    //����ɫvbo
    glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

    //��UV����vbo
    glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glBindVertexArray(0);
}

void prepareTexture() {
    foxTexture = new Texture("assets/textures/fox.png", 0);
    groundTexture = new Texture("assets/textures/grass.jpg", 0);
}

void prepareCamera() {
    //�����������
    glm::vec3 CPosition = glm::vec3(0.0f, 0.0f, 5.0f);
    glm::vec3 CUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 CRight = glm::vec3(1.0f, 0.0f, 0.0f);
    float size = 10.0f;
    //�����������
    perspectiveCamera = new PerspectiveCamera(60.0f,(float)application->getWidth() / (float)application->getHidth(),0.1f,1000.0f,glm::vec3(0.0f, 0.0f, 5.0f),glm::vec3(0.0f, 1.0f, 0.0f),glm::vec3(1.0f, 0.0f, 0.0f));
    orthographicCamera = new OrthographicCamera(-size, size, size, -size, size, -size, CPosition, CUp, CRight);
    //���������������
    gameCameraControl = new GameCameraControl;
    trackBallCameraControl = new TrackBallCameraControl;

    gameCameraControl->setCamera(perspectiveCamera);


    gameCameraControl->setSensitivity(0.05f);
    trackBallCameraControl->setSensitivity(0.05f);

}

void render(){
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
    shader->begin();
    //����ʱ��
    shader->setUFloat("time", glfwGetTime());
    //���ò�������
    shader->setInt("Sampler", 0);

    
    //�л����
     if (imGui->getComera()) 
     {
         camera = perspectiveCamera;
     }

    if (!imGui->getComera()) 
    {
        camera = orthographicCamera;
    }
    //�л����������
    if (imGui->getComeraContuol()) {
        gameCameraControl->setCamera(camera);
        gameCameraControl->update();
        cameraControl = gameCameraControl;
    }

    if (!imGui->getComeraContuol()) {
        trackBallCameraControl->setCamera(camera);
        cameraControl = trackBallCameraControl;
    }

    //���ñ任
    shader->setMatrix4x4("transform", Utransform);
    //������ͼ�任
    shader->setMatrix4x4("viewMatrix", camera->getViewMatrix());
    //����ͶӰ�任
    shader->setMatrix4x4("projectionMatrix", camera->getProjectionMatrix());
    

    glBindVertexArray(vao);

    //��һ����Ⱦ
    foxTexture->bindTexture();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    //�ڶ�����Ⱦ
    groundTexture->bindTexture();
    UtransformFox = glm::translate(glm::mat4(1.0f), glm::vec3(0.8f, 0.0f, -1.0f));
    shader->setMatrix4x4("transform", UtransformFox);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);

    shader->end();//��ѧϰ�����У��������ͽ��
}


int main() {

    if (!application->init(800, 600)) {
        std::cout << "��ʼ��ʧ��" << std::endl;
        return -1;
    }

    imGui = new GUI;
    imGui->setGuiInit(application->getWindow(), true);

    application->setResizeCallback(onResize);
    application->setKeyCallback(onKey);
    application->setMouseCallback(onMouse);
    application->setCursotCallback(onCousor);
    application->setScrollCallback(onScroll);

    glViewport(0, 0, 800, 600);
    glClearColor(0.2f, 0.3f, 0.6f, 1.0f);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    prepareShader();
    prepareVAO();
    prepareTexture();
    prepareCamera();

    CameraControl* cameraControl = gameCameraControl;

    while (application->updata()) {
        imGui->startGUI_up();
        //gameCameraControl->update();
        render();
        imGui->startGUI_end();
    };

    application->destroy();
    imGui->destroyGUI();
    delete foxTexture;
    
    //return 0;
    
}