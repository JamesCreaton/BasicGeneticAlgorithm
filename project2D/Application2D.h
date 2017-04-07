#pragma once
#include "Application.h"
#include <glm\glm.hpp>
#include <glm\ext.hpp>

#include "Box.h"
#include "Ground.h"

#include <Renderer2D.h>
#include <vector>
#include "GA.h"
#include "Person.h"

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

private:
	GA* m_ga;
	aie::Renderer2D*				m_2dRenderer;

	std::unique_ptr<b2World>		m_world;
	b2Vec2							m_gravity;
	std::vector<Box>				m_boxes;

	float							m_cameraX, m_cameraY;
};