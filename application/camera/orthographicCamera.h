#pragma once

#include "camera.h"

class OrthographicCamera :public Camera
{
public:
	OrthographicCamera(float l,
		float r,
		float t,
		float b,
		float n,
		float f,
		glm::vec3 Position,
		glm::vec3 Up,
		glm::vec3 Right
	);
	~OrthographicCamera();

	glm::mat4 getProjectionMatrix()override;
	void scale(float deltaScale)override;

private://һ�θ�ֵ���������
	float mLeft = 0.0f;
	float mRight = 0.0f;
	float mTop = 0.0f;
	float mBottom = 0.0f;
	float mNear = 0.0f;
	float mFar = 0.0f;

	float mScale{ 0.0f };//��¼�����еĴ�С�仯
};

