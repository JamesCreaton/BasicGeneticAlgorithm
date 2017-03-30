#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <Gizmos.h>
#include <glm\ext.hpp>

Application2D::Application2D() {

}

Application2D::~Application2D() {

}

bool Application2D::startup() {

	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();

	m_font = new aie::Font("./font/consolas.ttf", 32);

	// initialize the physics scene 
	m_physicsScene = new PhysicsScene(); 
	m_physicsScene->setGravity(vec2(0, -10)); 
	m_physicsScene->setTimeStep(0.01f);

	// add a physics object to the scene 
	Sphere* ball; 
	ball = new Sphere(vec2(1, 5), vec2(10, 30), 3.0f, 1, vec4(1, 0, 0, 1)); 
	m_physicsScene->addActor(ball);

	m_cameraX = 0;
	m_cameraY = 0;
	m_timer = 0;

	return true;
}

void Application2D::shutdown() {
	
	delete m_font;
	delete m_2dRenderer;
}

void Application2D::update(float deltaTime) {

	m_timer += deltaTime;

	// input example
	aie::Input* input = aie::Input::getInstance();

	// use arrow keys to move camera
	if (input->isKeyDown(aie::INPUT_KEY_UP))
		m_cameraY += 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
		m_cameraY -= 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
		m_cameraX -= 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
		m_cameraX += 500.0f * deltaTime;

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	aie::Gizmos::clear();

	// update physics 
	m_physicsScene->update(deltaTime); 
	m_physicsScene->updateGizmos();
}

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();
	setBackgroundColour(0.25f, 0.25f, 0.25f, 1);

	// set the camera position before we begin rendering
	m_2dRenderer->setCameraPos(m_cameraX, m_cameraY);

	// begin drawing sprites
	m_2dRenderer->begin();

	static float AR = 16 / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / AR, 100 / AR, -1.0f, 1.0f));
	
	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);

	// done drawing sprites
	m_2dRenderer->end();
}