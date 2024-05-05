#include "perspectiveCamera.h"
#include <iostream>

PerspectiveCamera::PerspectiveCamera(
	float fovy,
	float aspect,
	float near,
	float far,
	glm::vec3 Position,
	glm::vec3 Up,
	glm::vec3 Right
):Camera(Position,Up,Right) {
	mFovy = fovy;
	mAspect = aspect;
	mNear = near;
	mFar = far;
}

PerspectiveCamera::~PerspectiveCamera() {

}

glm::mat4 PerspectiveCamera::getProjectionMatrix() {
	//std::cout << "投影变换" << std::endl;
	//注意：传入的fovy是角度，需要转化为弧度
	return glm::perspective(glm::radians(mFovy), mAspect, mNear, mFar);
}

void PerspectiveCamera::scale(float deltaScale) {
	auto frount = glm::cross(mUp, mRight);
	mPosition += (frount * deltaScale);
}