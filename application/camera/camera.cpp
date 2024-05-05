#include "camera.h"

Camera::Camera(glm::vec3 Position, glm::vec3 Up, glm::vec3 Right) {
	mPosition = Position;
	mUp = Up;
	mRight = Right;
}

Camera::~Camera() {

}

glm::mat4 Camera::getViewMatrix() {
	//����lookAt������Ҫ�Ĳ���
	glm::vec3 front = glm::cross(mUp, mRight);
	glm::vec3 center = mPosition + front;

	//����lookAt����ֵ
	return glm::lookAt(mPosition, center, mUp);
}

glm::mat4 Camera::getProjectionMatrix() {
	return glm::identity<glm::mat4>();
}


void Camera::scale(float deltaScale) {
	//�ȴ�����д
}