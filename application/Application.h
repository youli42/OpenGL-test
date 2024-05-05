#pragma once
class GLFWwindow;

#define application Application::getInstance()

using ResizeCallback = void(*)(int width, int height);
using keyCallback = void(*)(int key, int scancode, int action, int mods);
using mouseCallback = void(*)(int button, int action, int mods);
using cursorCallback = void(*)(double xpos, double ypos);
using ScrollCallback = void(*)(double offset);

class Application {
public:
	~Application();
	static Application* getInstance();

	bool init(const int& width = 800, const int& height = 600);
	bool updata();

	void destroy();

	//传递数据函数
	uint32_t getWidth() const { return mWidth; }
	uint32_t getHidth() const { return mHeight; }
	void getCursorPosition(double* x, double* y);
	GLFWwindow* getWindow() { return mWindow; }

	//暴露接口
	void setResizeCallback(ResizeCallback callback) { mResizeCallback = callback; }
	void setKeyCallback(keyCallback callback) { mkeyCallbake = callback; }
	void setMouseCallback(mouseCallback callback) { mMouseCallback = callback; }
	void setCursotCallback(cursorCallback callback) { mCursorCallback = callback; }
	void setScrollCallback(ScrollCallback callback) { mScrollCallback = callback; }

private:
	static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void MouseCallback(GLFWwindow* window, int button, int action, int mods);
	static void CursorCallback(GLFWwindow* window, double xpos, double ypos);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

private:
	static Application* M_Instance;

	uint32_t mWidth{ 0 };
	uint32_t mHeight{ 0 };
	GLFWwindow* mWindow{ nullptr };

	ResizeCallback mResizeCallback{ nullptr };
	keyCallback mkeyCallbake{ nullptr };
	mouseCallback mMouseCallback{ nullptr };
	cursorCallback mCursorCallback{ nullptr };
	ScrollCallback mScrollCallback{ nullptr };

	Application();
};

