#pragma once

#include"../../glframework/core.h"
#include "../camera/cameraControl.h"
class GUI
{
public:
	GUI();
	~GUI();


//**��ʼ��**
	void setGuiInit(GLFWwindow* windows, bool test);

//**��ʼѭ��**
	void startGUI_up();
	void startGUI_end();

//**�����������**
	void destroyGUI();

//**ʵ�ִ���**
	void controlPlane();



public:
//**����һЩ����
	bool getComeraContuol() { return onGameCameraControl; }
	bool getComera() { return onPerspectiveCamera; }

private:
	//����һЩ����
	bool show_control_plane = true;
	//������������
	bool onGameCameraControl = true;
	bool onPerspectiveCamera = true;

	float color[4] = { 0.5f,0.5f,0.5f,1.0f };

	float mCameraFov = 60.0f;
	float fov = 60.0f;
};

