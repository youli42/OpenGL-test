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
	glm::vec3 direction(0.0f);//�����ƶ�����
	glm::vec3 upDown(0.0f);//���·���

	auto front = glm::cross(mCamera->mUp, mCamera->mRight);//����ǰ����
	auto right = mCamera->mRight;
	auto up = mCamera->mUp;

	//�ƶ��߼�ʵ��
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

	//��ʱdirection�п��ܲ�Ϊ1������Ҫ���й�һ��
		//����Ҫ�ų�Ϊ0�����
	if (glm::length(direction) != 0) {
		direction = glm::normalize(direction);
		mCamera->mPosition += direction * mSpeed;
	}

	//upDown = glm::normalize(upDown);
	mCamera->mPosition += upDown * mScaleSpeed;

	//�̶����λ��
	if (mKeyMap[GLFW_KEY_L]) {
		glfwSetCursorPos(application->getWindow(), application->getWidth() / 2, application->getHidth() / 2);
	}

}






//***********���ߺ���*************
void GameCameraControl::pitch(float angle) {
	//̧ͷ�Ƕ�����
	mPitch += angle;
	if (mPitch > 89.9f || mPitch < -89.9f) {
		mPitch -= angle;
		return;
	}

	//��gameCameraControl�£�pitch����Ӱ��λ��
	auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), mCamera->mRight);
	mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f);
}

void GameCameraControl::yaw(float angle) {
	auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f);
	mCamera->mRight = mat * glm::vec4(mCamera->mRight, 0.0f);
}
