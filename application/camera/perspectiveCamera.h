#pragma once

#include "camera.h"

class PerspectiveCamera :public Camera {
public:
	PerspectiveCamera(
		float fovy,
		float aspect,
		float near,
		float far,
		glm::vec3 Position,
		glm::vec3 Up,
		glm::vec3 Right
	);
	~PerspectiveCamera();

	glm::mat4 getProjectionMatrix()override;
	void scale(float deltaScale)override;//重写鼠标滚轮读取函数

private:
	float mFovy = 0.0f;
	float mAspect = 0.0f;
	float mNear = 0.0f;
	float mFar = 0.0f;
};