#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct Camera
{
public:
	Camera()
	{
	}

	void initCamera(const glm::vec3& pos, float fov, float aspect, float nearClip, float farClip) //initialises the camera depending on the certain variables
	{
		this->pos = pos; //used for camera position
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f); //sets the forward float based on the vector used for moving forward
		this->up = glm::vec3(0.0f, 1.0f, 0.0f); //sets the up float based on the vector used for moving up
		this->projection = glm::perspective(fov, aspect, nearClip, farClip); //sets the projection 
	}

	

	inline glm::mat4 GetProjection() const
	{
		return projection;
	}

	inline glm::mat4 GetView() const
	{
		return glm::lookAt(pos, pos + forward, up);
	}
	inline glm::mat4 GetViewProjection() const //used for getting the view projection matrix
	{
		return projection * glm::lookAt(pos, pos + forward, up);
	}
	inline glm::vec3 GetPos() const
	{
		return pos;
	}

	void MoveForward(float amt) //used for moving camera forwards, changes position by adding the forward vector times the "amt" float to the position
	{
		pos += forward * amt;
	}

	void MoveBackward(float amt) //same as MoveForward but subtracts rather than adding
	{
		pos -= forward * amt;
	}

	void MoveUp(float amt) //same as MoveForward but subtracts rather than adding
	{
		pos += up * amt;
	}

	void MoveDown(float amt) //same as MoveForward but subtracts rather than adding
	{
		pos -= up * amt;
	}

	void MoveRight(float amt) //used for moving camera to the right
	{
		pos -= glm::cross(up, forward) * amt;
	}

	void MoveLeft(float amt) //used for moving camera to the left
	{
		pos += glm::cross(up, forward) * amt;
	}

	void Pitch(float angle) //used to pitch the camera angle
	{
		glm::vec3 right = glm::normalize(glm::cross(up, forward));

		forward = glm::vec3(glm::normalize(glm::rotate(angle, right) * glm::vec4(forward, 0.0)));
		up = glm::normalize(glm::cross(forward, right));
	}

	void RotateY(float angle) //used to rotate the camera
	{
		static const glm::vec3 UP(0.0f, 1.0f, 0.0f);

		glm::mat4 rotation = glm::rotate(angle, UP);

		forward = glm::vec3(glm::normalize(rotation * glm::vec4(forward, 0.0)));
		up = glm::vec3(glm::normalize(rotation * glm::vec4(up, 0.0)));
	}

protected:
private:
	glm::mat4 projection;
	glm::vec3 pos;
	glm::vec3 forward;
	glm::vec3 up;
};


