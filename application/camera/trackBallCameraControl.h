#pragma once

#include "cameraControl.h"

class TrackBallCameraControl :public CameraControl
{
public:
	TrackBallCameraControl();
	~TrackBallCameraControl();

	//�����У���Ҫ��д�ĺ���
	void onCursor(double xpos, double ypos)override;
	void onScroll(float offset)override;

private:
	float moveSpeed = 0.001f;
	//���Լ����õĹ��ߺ���
		////02���ֿ� pitch �� yaw ���Լ���
	void pitch(float angle);
	void yaw(float angle);

};