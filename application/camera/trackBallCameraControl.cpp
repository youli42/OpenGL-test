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
	//当左键按下时（父类中已经实现）//调整摄像机参数
		//01、计算鼠标位移得出旋转的增量角度(sen敏感度）正负皆可
		float deltaX = (xpos - mCurrentX) * mSensitivity;
		float deltaY = (ypos - mCurrentY) * mSensitivity;

	//02、分开 pitch 和 yaw 各自计算//逻辑封装在函数中
		pitch(deltaY);//负号调整鼠标方向
		yaw(deltaX);
	}

	//实现按住shift同时按住鼠标中间平移
	if (mMiddleMouseDown && mKeyMap[GLFW_KEY_LEFT_SHIFT]) {
		float deltaX = (xpos - mCurrentX) * moveSpeed;
		float deltaY = (ypos - mCurrentY) * moveSpeed;

		mCamera->mPosition += mCamera->mUp * deltaY;
		mCamera->mPosition -= mCamera->mRight * deltaX;
	}

	//完成后更新x,y的值***别忘了****
	mCurrentX = xpos;
	mCurrentY = ypos;
}

void TrackBallCameraControl::onScroll(float offset) {
	mCamera->scale(mScaleSpeed * offset);
}

//封装pitch角旋转函数
void TrackBallCameraControl::pitch(float angle) {
	//绕right向量旋转
	auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), mCamera->mRight);

	//影响当前相机的up向量和位置（增量变换）
			//将up向量提升为四维(1代表点0代表向量)
	mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f);//四维向量可以給3维（给xyz）
	mCamera->mPosition = mat * glm::vec4(mCamera->mPosition, 1.0f);
}

void TrackBallCameraControl::yaw(float angle) {
	auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f,1.0f,0.0f));

	mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f);
	mCamera->mRight = mat * glm::vec4(mCamera->mRight, 0.0f);
	mCamera->mPosition = mat * glm::vec4(mCamera->mPosition, 1.0f);
}

