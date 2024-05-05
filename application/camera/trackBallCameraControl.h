#pragma once

#include "cameraControl.h"

class TrackBallCameraControl :public CameraControl
{
public:
	TrackBallCameraControl();
	~TrackBallCameraControl();

	//父类中，需要重写的函数
	void onCursor(double xpos, double ypos)override;
	void onScroll(float offset)override;

private:
	float moveSpeed = 0.001f;
	//供自己调用的工具函数
		////02、分开 pitch 和 yaw 各自计算
	void pitch(float angle);
	void yaw(float angle);

};