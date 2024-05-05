#include "cameraControl.h"
#include <iostream>

CameraControl::CameraControl() {

}

CameraControl::~CameraControl() {

}

//�����ӿ�
void CameraControl::onMouse(int button, int action, double xpos, double ypos)
 {
	std::cout << "onMouse����" << std::endl;
	//01���жϵ�ǰ�����Ƿ���
	bool pressed = action == GLFW_PRESS ? true : false;

	//02������ʱ��¼����λ��
	if (pressed) {
		mCurrentX = xpos;
		mCurrentY = ypos;
	}

	//03�����ݰ��µ���갴�������İ�����¼��״̬
	switch (button) {
	case GLFW_MOUSE_BUTTON_LEFT:
		mLeftMouseDown = pressed;
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		mRightMouseDown = pressed;
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		mMiddleMouseDown = pressed;
		break;
	}
}

void CameraControl::onCursor(double xpos, double ypos) {
	std::cout << "onCursor(����ƶ�)����" << std::endl;
	//û�й������֣��ɸ���ʵ��
}

void CameraControl::onKey(int key, int action, int mods) {
	std::cout << "onKey����" << std::endl;
	//����repeat����ס�������
	if (action == GLFW_REPEAT) {
		return;
	}
	
	//01���жϵ�ǰ�����Ƿ���
	bool pressed = action == GLFW_PRESS ? true : false;
	
	//02����¼��keyMap��
	mKeyMap[key] = pressed;
}

 void CameraControl::onScroll(float offset) {

}

//ÿ֡����
void CameraControl::update() {
	//û�й������֣��ɸ���ʵ��
}

