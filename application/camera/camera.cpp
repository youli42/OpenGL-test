#include "camera.h"

Camera::Camera(glm::vec3 Position, glm::vec3 Up, glm::vec3 Right) {
	mPosition = Position;
	mUp = Up;
	mRight = Right;
}

Camera::~Camera() {

}

glm::mat4 Camera::getViewMatrix() {
	//创建lookAt函数需要的参数
	glm::vec3 front = glm::cross(mUp, mRight);
	glm::vec3 center = mPosition + front;

	//返回lookAt函数值
	return glm::lookAt(mPosition, center, mUp);
}

glm::mat4 Camera::getProjectionMatrix() {
	return glm::identity<glm::mat4>();
}


void Camera::scale(float deltaScale) {
	//等待被覆写
}