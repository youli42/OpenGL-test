#pragma once

#include"../../glframework/core.h"
#include "../camera/cameraControl.h"
class GUI
{
public:
	GUI();
	~GUI();


//**初始化**
	void setGuiInit(GLFWwindow* windows, bool test);

//**开始循环**
	void startGUI_up();
	void startGUI_end();

//**结束清除程序**
	void destroyGUI();

//**实现窗口**
	void controlPlane();



public:
//**开放一些数据
	bool getComeraContuol() { return onGameCameraControl; }
	bool getComera() { return onPerspectiveCamera; }

private:
	//储存一些变量
	bool show_control_plane = true;
	//相机和相机控制
	bool onGameCameraControl = true;
	bool onPerspectiveCamera = true;

	float color[4] = { 0.5f,0.5f,0.5f,1.0f };

	float mCameraFov = 60.0f;
	float fov = 60.0f;
};

