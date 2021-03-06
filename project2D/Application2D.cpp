#include "Application2D.h"
#include "Input.h"
#include <iostream>
#include <gl_core_4_4.h>
#include <GLFW\glfw3.h>
#include <GLFW\glfw3native.h>
#include <imgui_glfw3.h>

#include <Box2D.h>


Application2D::Application2D() {

}

Application2D::~Application2D() {

}

bool Application2D::startup() {
	m_2dRenderer = new aie::Renderer2D();

	m_gravity = b2Vec2(0.0f, 0.0f);
	m_world = std::make_unique<b2World>(m_gravity);

	m_target = new Box();
	m_target->init(m_world.get(), glm::vec2(getWindowWidth() - 50, getWindowHeight() / 2), glm::vec2(50, 50));

	m_ga = new GA(b2Vec2(m_target->GetBody()->GetPosition()));

	m_font = new aie::Font("consolas.ttf", 12);

	for (auto& person : (*m_ga->GetPeople())) {
		person->init(m_world.get(), glm::vec2(getWindowWidth() / 2, getWindowHeight() / 2), glm::vec2(25.0f, 25.0f));
	}
	
	m_cameraX = 0;
	m_cameraY = 0;

	return true;
}

void Application2D::shutdown() {
	
}

void Application2D::update(float deltaTime) {
	// input example
	aie::Input* input = aie::Input::getInstance();

	m_world->Step(1.0f / 20.f, 6, 2);
	m_ga->UpdatePopulation(deltaTime);

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::draw() {
	// wipe the screen to the background colour
	clearScreen();

	// set the camera position before we begin rendering
	m_2dRenderer->setCameraPos(m_cameraX, m_cameraY);

	// begin drawing sprites
	m_2dRenderer->begin();
	
	m_target->Draw(m_2dRenderer);

	m_ga->DrawPopulation(m_2dRenderer);
	m_ga->DrawGUI(m_2dRenderer, m_font);

	m_2dRenderer->end();
}