#include "Camera.h"
#include "Display.h"

static const float RIGHT_ANGLE = 1.553343034274953323f;
static const float DEFAULT_FOV = PI * 140 / 360;
static const float DEFAULT_NEAR = 0.01f;
static const float DEFAULT_FAR = 10000;

Camera::Camera() {

	glm::vec2 sz = Display::getGlobal()->getSize();
	initialize(glm::vec3(), DEFAULT_FOV, sz.x / sz.y, DEFAULT_NEAR, DEFAULT_FAR);

}

Camera::Camera(const glm::vec3& pos, double fov, double aspect, double zNear, double zFar) {

	initialize(pos, fov, aspect, zNear, zFar);

}

void Camera::onResize(int x, int y) {

	changeAspect(x, y);

}

void Camera::initialize(const glm::vec3& pos, double fov, double aspect, double zNear, double zFar) {
	
	m_perspective = glm::perspective(fov, aspect, zNear, zFar);
	setPos(pos);
	m_forward = glm::vec3(0, 0, 1);
	m_up = glm::vec3(0, 1, 0);
	m_fov = fov; m_aspect = aspect; m_znear = zNear; m_zfar = zFar;

}

void Camera::rotate(glm::vec3 amt) {

	setRot(getRot() + amt);

}

void Camera::setRot(glm::vec3 rot) {

	if (rot.x > RIGHT_ANGLE) { rot.x = RIGHT_ANGLE; }
	if (rot.x < -RIGHT_ANGLE) { rot.x = -RIGHT_ANGLE; }

	getTransform().SetRot(rot);
	m_forward = glm::vec3(getTransform().GetRotMatrix() * glm::vec4(0, 0, 1, 1));

}

void Camera::setFOV(double fov) {
	m_fov = fov;
	m_perspective = glm::perspective(m_fov, m_aspect, m_znear, m_zfar);
}

void Camera::setOffset(float offset) {
	this->offset = offset;
}

glm::mat4 Camera::getViewMatrix() {
	glm::vec3 pos = getPos() - m_forward * offset;
	return m_perspective * glm::lookAt(pos, pos + m_forward * (offset >= 0.0f ? 1.0f : -1.0f), m_up);
}

void Camera::changeAspect(double W, double H) {
	m_aspect = (W / H);
	m_perspective = glm::perspective(m_fov, m_aspect, m_znear, m_zfar);
}