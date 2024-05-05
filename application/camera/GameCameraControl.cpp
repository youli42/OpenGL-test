#include"GameCameraControl.h"

GameCameraControl::GameCameraControl()
{
}

GameCameraControl::~GameCameraControl()
{
}

void GameCameraControl::onCursor(double xpos, double ypos) {
	float deltaX = (xpos - mCurrentX) * mSensitivity;
	float deltaY = (ypos - mCurrentY) * mSensitivity;

	if (mRightMouseDown) {
		pitch(-deltaY);
		yaw(-deltaX);
	}

	mCurrentX = xpos;
	mCurrentY = ypos;
}

void GameCameraControl::update() {
	glm::vec3 direction(0.0f);//最终移动方向
	glm::vec3 upDown(0.0f);//上下方向

	auto front = glm::cross(mCamera->mUp, mCamera->mRight);//计算前向量
	auto right = mCamera->mRight;
	auto up = mCamera->mUp;

	//移动逻辑实现
	if (mKeyMap[GLFW_KEY_W]) {
		direction += front;
	}

	if (mKeyMap[GLFW_KEY_S]) {
		direction -= front;
	}
	
	if (mKeyMap[GLFW_KEY_A]) {
		direction -= right;
	}

	if (mKeyMap[GLFW_KEY_D]) {
		direction += right;
	}

	if (mKeyMap[GLFW_KEY_E]) {
		upDown += up;
	}

	if (mKeyMap[GLFW_KEY_Q]) {
		upDown -= up;
	}

	//此时direction有可能不为1，所以要进行归一化
		//但是要排除为0的情况
	if (glm::length(direction) != 0) {
		direction = glm::normalize(direction);
		mCamera->mPosition += direction * mSpeed;
	}

	//upDown = glm::normalize(upDown);
	mCamera->mPosition += upDown * mScaleSpeed;

	//固定鼠标位置
	if (mKeyMap[GLFW_KEY_L]) {
		glfwSetCursorPos(application->getWindow(), application->getWidth() / 2, application->getHidth() / 2);
	}

}






//***********工具函数*************
void GameCameraControl::pitch(float angle) {
	//抬头角度限制
	mPitch += angle;
	if (mPitch > 89.9f || mPitch < -89.9f) {
		mPitch -= angle;
		return;
	}

	//在gameCameraControl下，pitch不会影响位置
	auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), mCamera->mRight);
	mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f);
}

void GameCameraControl::yaw(float angle) {
	auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f);
	mCamera->mRight = mat * glm::vec4(mCamera->mRight, 0.0f);
}
