#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "Entity.h"
#include "Evt_Display.h"

#ifndef PI
#define PI		(3.1415926535f)
#endif

class Camera : public Entity, DisplayListener {
public:

	Camera(const glm::vec3& pos, double fov, double aspect, double zNear, double zFar);
	Camera();

	void changeAspect(double, double);

	void setFOV(double);

	void setOffset(float);

	double getFOV() { return m_fov; }
	float getOffset() { return offset; }

	glm::vec3& getForward() { return m_forward; }
	glm::vec3& getUp() { return m_up; }

	void rotate(glm::vec3 amt) override;
	void setRot(glm::vec3 amt) override;

	glm::mat4 getViewMatrix();

private:

	void onResize(int, int) override;
	void initialize(const glm::vec3& pos, double fov, double aspect, double zNear, double zFar);

	float offset = 0.0f;
	glm::mat4 m_perspective;
	glm::vec3 m_forward = glm::vec3(0, 0, 0);
	glm::vec3 m_up = glm::vec3(0, 0, 0);
	double m_fov = 0;
	double m_aspect = 0;
	double m_znear = 0;
	double m_zfar = 0;
};