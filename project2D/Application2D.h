#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Audio.h"

#include "PhysicsObject.h"
#include "PhysicsScene.h"
#include "Sphere.h"
#include <glm\glm.hpp>

using glm::vec2;
using glm::vec3;
using glm::vec4;

class Application2D : public aie::Application {
public:

	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	PhysicsScene*		m_physicsScene;

	float m_cameraX, m_cameraY;
	float m_timer;
};