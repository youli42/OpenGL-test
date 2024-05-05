#pragma once

#include"cameraControl.h"

class GameCameraControl : public CameraControl
{
public:
	GameCameraControl();
	~GameCameraControl();

	//函数接口
	void onCursor(double xpos, double ypos)override;//覆写鼠标移动函数，控制视角
	void update()override;//覆写更新函数，监控键盘状态
	void setSpeed(float speed) { mSpeed = speed; }
private:
	//工具函数
	void pitch(float angle);
	void yaw(float angle);
	//变量存储
	float mPitch{ 0.0f };//记录角度，用来限制角度
	float mSpeed{ 0.1f };//移动速度
};

