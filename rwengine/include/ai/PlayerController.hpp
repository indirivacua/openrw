#pragma once
#ifndef _PLAYERCONTROLLER_HPP_
#define _PLAYERCONTROLLER_HPP_
#include <ai/CharacterController.hpp>

class PlayerController : public CharacterController
{
	glm::quat cameraRotation;
	
	glm::vec3 direction;
	glm::vec3 _rawDirection;
	
	glm::quat lastRotation;
	
	bool running;

	bool _enabled;
	
public:
	
	PlayerController(CharacterObject* character);
	
	void setRunning(bool run);

	/**
	 * @brief Enables and disables player input.
	 * @todo actually implement input being disabled.
	 */
	void setInputEnabled(bool enabled);
	
	void updateCameraDirection(const glm::quat& rot);
	
	void updateMovementDirection(const glm::vec3& pos, const glm::vec3& rawdirection);
	
	void exitVehicle();
	
	void enterNearestVehicle();
	
    virtual void update(float dt);
	
    virtual glm::vec3 getTargetPosition();
	
	void jump();
};

#endif
