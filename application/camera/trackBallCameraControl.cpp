#pragma once
#include "trackBallCameraControl.h"

TrackBallCameraControl::TrackBallCameraControl()
{
}

TrackBallCameraControl::~TrackBallCameraControl()
{
}


void TrackBallCameraControl::onCursor(double xpos, double ypos) {

	if (mMiddleMouseDown && !mKeyMap[GLFW_KEY_LEFT_SHIFT]) {
	//���������ʱ���������Ѿ�ʵ�֣�//�������������
		//01���������λ�Ƶó���ת�������Ƕ�(sen���жȣ������Կ�
		float deltaX = (xpos - mCurrentX) * mSensitivity;
		float deltaY = (ypos - mCurrentY) * mSensitivity;

	//02���ֿ� pitch �� yaw ���Լ���//�߼���װ�ں�����
		pitch(deltaY);//���ŵ�����귽��
		yaw(deltaX);
	}

	//ʵ�ְ�סshiftͬʱ��ס����м�ƽ��
	if (mMiddleMouseDown && mKeyMap[GLFW_KEY_LEFT_SHIFT]) {
		float deltaX = (xpos - mCurrentX) * moveSpeed;
		float deltaY = (ypos - mCurrentY) * moveSpeed;

		mCamera->mPosition += mCamera->mUp * deltaY;
		mCamera->mPosition -= mCamera->mRight * deltaX;
	}

	//��ɺ����x,y��ֵ***������****
	mCurrentX = xpos;
	mCurrentY = ypos;
}

void TrackBallCameraControl::onScroll(float offset) {
	mCamera->scale(mScaleSpeed * offset);
}

//��װpitch����ת����
void TrackBallCameraControl::pitch(float angle) {
	//��right������ת
	auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), mCamera->mRight);

	//Ӱ�쵱ǰ�����up������λ�ã������任��
			//��up��������Ϊ��ά(1�����0��������)
	mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f);//��ά�������Խo3ά����xyz��
	mCamera->mPosition = mat * glm::vec4(mCamera->mPosition, 1.0f);
}

void TrackBallCameraControl::yaw(float angle) {
	auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f,1.0f,0.0f));

	mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f);
	mCamera->mRight = mat * glm::vec4(mCamera->mRight, 0.0f);
	mCamera->mPosition = mat * glm::vec4(mCamera->mPosition, 1.0f);
}

