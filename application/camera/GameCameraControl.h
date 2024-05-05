#pragma once

#include"cameraControl.h"

class GameCameraControl : public CameraControl
{
public:
	GameCameraControl();
	~GameCameraControl();

	//�����ӿ�
	void onCursor(double xpos, double ypos)override;//��д����ƶ������������ӽ�
	void update()override;//��д���º�������ؼ���״̬
	void setSpeed(float speed) { mSpeed = speed; }
private:
	//���ߺ���
	void pitch(float angle);
	void yaw(float angle);
	//�����洢
	float mPitch{ 0.0f };//��¼�Ƕȣ��������ƽǶ�
	float mSpeed{ 0.1f };//�ƶ��ٶ�
};

