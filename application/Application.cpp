#include<iostream>
#include<glad/glad.h>
//.cpp文件单独编译，所以不会有引用冲突
#include <GLFW/glfw3.h>

#include"Application.h"

//初始化Application的静态变量
Application* Application::M_Instance = nullptr;//// 访问并初始化静态成员变量  
Application* Application::getInstance() {
	//如果M_Instance已经实例化了（new出来了），就直接返回，
	//否则就先new再返回（因为全局静态变量只实例一次）
	if (M_Instance == nullptr) {
		M_Instance = new Application();//在类中可以调用私有函数
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

	//this 就是当前全局唯一的 application 对象，将这个对象存到指针中给到 glsw
	glfwSetWindowUserPointer(mWindow, this);//可以理解成将 this 对象存到了 mWindow 中

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
	
//回调函数部分
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

//滚动消息的offset
void Application::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if (self->mScrollCallback != nullptr) {
		self->mScrollCallback(yoffset);
	}
}



