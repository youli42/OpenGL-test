#include<iostream>
#include<glad/glad.h>
//.cpp�ļ��������룬���Բ��������ó�ͻ
#include <GLFW/glfw3.h>

#include"Application.h"

//��ʼ��Application�ľ�̬����
Application* Application::M_Instance = nullptr;//// ���ʲ���ʼ����̬��Ա����  
Application* Application::getInstance() {
	//���M_Instance�Ѿ�ʵ�����ˣ�new�����ˣ�����ֱ�ӷ��أ�
	//�������new�ٷ��أ���Ϊȫ�־�̬����ֻʵ��һ�Σ�
	if (M_Instance == nullptr) {
		M_Instance = new Application();//�����п��Ե���˽�к���
	}

	return M_Instance;
}

Application::Application() {

}

Application::~Application() {

}


bool Application::init(const int& width, const int& height) {
	mWidth = width;
	mHeight = height;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mWindow = glfwCreateWindow(mWidth, mHeight, "MipMap", NULL, NULL);
	if (mWindow == NULL) {
		return false;
	}

	glfwMakeContextCurrent(mWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Faild to initialize GLAD" << std::endl;
		return false;
	}

	glfwSetFramebufferSizeCallback(mWindow, frameBufferSizeCallback);
	glfwSetKeyCallback(mWindow, KeyCallback);
	glfwSetMouseButtonCallback(mWindow, MouseCallback);
	glfwSetCursorPosCallback(mWindow, CursorCallback);
	glfwSetScrollCallback(mWindow, scrollCallback);

	//this ���ǵ�ǰȫ��Ψһ�� application ���󣬽��������浽ָ���и��� glsw
	glfwSetWindowUserPointer(mWindow, this);//�������ɽ� this ����浽�� mWindow ��

	return true;
}

bool Application::updata() {
	if (glfwWindowShouldClose(mWindow)) {
		return false;
	}

	glfwPollEvents();

	glfwSwapBuffers(mWindow);

	return true;
}

void Application::destroy() {
	glfwTerminate();
}

void Application::getCursorPosition(double* x, double* y) {
	glfwGetCursorPos(mWindow, x, y);
}
	
//�ص���������
void Application::frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if(self != nullptr)
		self->mResizeCallback(width, height);
}

void Application::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if (self->mkeyCallbake != nullptr) {
		self->mkeyCallbake(key, scancode, action, mods);
	}
}


void Application::MouseCallback(GLFWwindow* window, int button, int action, int mods) {
	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if (self->mMouseCallback != nullptr) {
		self->mMouseCallback(button, action, mods);
	}
}

void Application::CursorCallback(GLFWwindow* window, double xpos, double ypos) {
	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if (self->mCursorCallback != nullptr) {
		self->mCursorCallback(xpos, ypos);
	}
}

//������Ϣ��offset
void Application::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if (self->mScrollCallback != nullptr) {
		self->mScrollCallback(yoffset);
	}
}



