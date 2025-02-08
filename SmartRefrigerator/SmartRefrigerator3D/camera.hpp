// By using these several preprocessor directives at the top of the header file, the compiler is informed to only
// include and compile this header file if it hasn't been included yet. This applies even if multiple files include the
// camera header. This prevents linking conflicts.
#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

// Fly-like camera.
class Camera
{
private:
	glm::vec3 target = glm::vec3(0.0F, 0.0F, 2.55F);
	glm::vec3 direction = glm::vec3(0.0F, 0.0F, 1.0F);
	glm::vec3 upVector = glm::vec3(0.0F, 1.0F, 0.0F);
	glm::vec3 right = glm::vec3(0.0F);
	glm::vec3 up = glm::vec3(0.0F);
	// The camera's movement is presented with the Euler angles - a set of 3 values that can represent any rotation in a
	// 3D space.
	// The fly-like camera requires the use of only the first two of the Euler angles: the pitch angle (top/bottom,
	// movement around a fixed x-axis) and the yaw angle (left/right, movement around a fixed y-axis).
	// The third Euler angle, the roll angle (movement around a fixed z-axis) will not be required, because the user
	// will not rotate the camera like a mobile phone, bending it to left or right or turning it upside-down.
	float pitch = 0.0F;
	// The yaw angle is initialized to -90.0F degrees, because a 0.0F value would result in "camera's direction" vector
	// pointing to the right, towards the positive z-axis (on the xz plane). That is not the desired pointing direction,
	// because the camera is set up to look away from user, towards the negative z-axis. Therefore, the yaw angle should
	// be initialized with a negative value, which means clockwise rotation.
	float yaw = -90.0F;
	const float sensitivityOfMouse = 0.05F;
public:
	glm::vec3 position = glm::vec3(0.0F, 0.0F, 3.55F);
	// This vector acts as insurance that however the user moves the camera, it will always keep looking straight ahead.
	// Math is explained below. In 2. thing needed to manually create the LookAt matrix - the "camera's direction":
	// glm::vec3 cameraTarget = cameraPosition + cameraFront;
	// glm::vec3 cameraDirection = glm::normalize(cameraPosition - cameraTarget) = glm::normalize(-cameraFront);
	glm::vec3 front = glm::vec3(0.0F, 0.0F, -1.0F);
	float fov = 45.0F;

	Camera()
	{
		updateCoordinateSystemOfCamera();
	}

	Camera(glm::vec3 position, glm::vec3 front, glm::vec3 upVector)
	{
		this->position = position;
		this->front = front;
		this->upVector = upVector;

		updateCoordinateSystemOfCamera();
	}

	// REFERENCE: https://www.geeksforgeeks.org/destructors-c/
	virtual ~Camera() {}

	// Utility function for calculating all the vectors required to create the camera's coordinate system.
	void updateCoordinateSystemOfCamera()
	{
		// Calculate the ACTUAL camera's direction vector, the result of subtracting the camera's position from the
		// camera's target (thus visually ending at the camera's target, the minuend of subtraction).
		glm::vec3 actualDirection = glm::vec3(0.0F);
		actualDirection.x = glm::cos(glm::radians(pitch)) * glm::cos(glm::radians(yaw));
		actualDirection.y = glm::sin(glm::radians(pitch));
		actualDirection.z = glm::cos(glm::radians(pitch)) * glm::sin(glm::radians(yaw));
		front = glm::normalize(actualDirection);

		// The "camera's direction". It's a bad name, because what is actually needed is the direction TO camera.
		// The camera's direction is counted by subtracting the camera's position from the camera's target. However,
		// the camera in the OpenGL by convention points towards the negative z-axis and the z-axis in the view matrix's
		// coordinate system is designed to be positive. Because of those two reasons, the subtraction order needs to be
		// switched (the camera's target - the camera's position). The vector visually ends at the minuend (the first
		// operand of subtraction) and starts at the subtrahend (the second operand of subtraction). Therefore, it
		// should end on camera's position, pointing to it.
		target = position + front;
		direction = glm::normalize(position - target);

		// The camera's right vector. This vector points right from the camera and is perpendicular to the "camera's
		// direction".
		// It can be created by doing a cross product between the "up" vector and the "camera's direction". The result
		// of a cross product is a vector perpendicular to both vectors. In this case, that resulting vector will point
		// in the positive x-axis' direction.
		right = glm::normalize(glm::cross(upVector, direction));
		// The camera's up vector. Since the vectors that point in the positive z-axis' direction (the "camera's
		// direction") and the positive x-axis's direction (camera's right vector) are already calculated, their cross
		// product will be the vector pointing in the positive y-axis's direction (the camera's up vector).
		up = glm::normalize(glm::cross(direction, right));
	}

	// Utility function for calculating the view matrix.
	glm::mat4 getCalculatedViewMatrix()
	{
		updateCoordinateSystemOfCamera();

		// GLM's "lookAt" function requires the camera's position, the camera's target and the "up" vector.
		return glm::lookAt(position, target, upVector);
	}

	// Utility function for processing the keyboard input.
	void processInputFromKeyboard(std::string key, float deltaTime)
	{
		// The camera will move at a constant speed of 2.5 units per second.
		float speedOfCamera = 2.5F * deltaTime;
		// Move the camera forward (away from the user, in the negative z-axis' direction) by adding the scaled camera's
		// direction to the camera's position.
		if (key == "W")
		{
			position += front * speedOfCamera;
		}
		// Move the camera backwards (towards the user, in the positive z-axis' direction) by subtracting the scaled
		// camera's direction from the camera's position.
		else if (key == "S")
		{
			position -= front * speedOfCamera;
		}
		// Move the camera to the left (in the negative x-axis' direction) by subtracting the scaled right vector
		// (the cross product of the camera's front vector and the "up" vector) from the camera's position. That right
		// vector has to be normalized, because the cross product could return differently sized vectors depending on
		// the value of the "front" vector. Also, the user would move slow or fast depending on the camera's orientation,
		// instead of at a consistent speed.
		else if (key == "A")
		{
			position -= glm::normalize(glm::cross(front, upVector)) * speedOfCamera;
		}
		// Move the camera to the right (in the positive x-axis' direction) by adding the scaled right vector (the cross
		// product of the camera's front vector and the "up" vector) to the camera's position. That right vector has to
		// be normalized, because the cross product could return differently sized vectors depending on the value of the
		// "front" vector. Also, the user would move slow or fast depending on the camera's orientation, instead of at a
		// consistent speed.
		else if (key == "D")
		{
			position += glm::normalize(glm::cross(front, upVector)) * speedOfCamera;
		}
	}

	// Utility function for processing the mouse movement, starting from the 2. step of calculating the "camera's front"
	// vector. The "camera's front" vector acts as insurance that however the user moves the camera, it will always keep
	// looking straight ahead.
	// Math is explained below. In 2. thing needed to manually create the LookAt matrix - the "camera's direction":
	// glm::vec3 cameraTarget = cameraPosition + cameraFront;
	// glm::vec3 cameraDirection = glm::normalize(cameraPosition - cameraTarget) = glm::normalize(-cameraFront);.
	void processMovementOfMouse(float xoffset, float yoffset)
	{
		// 2. step: add the offset values to the camera's pitch and yaw angles.
		// The mouse movement would be too erratic if it had not been scaled by a sensitivity variable.
		xoffset *= sensitivityOfMouse;
		yoffset *= sensitivityOfMouse;
		pitch += yoffset;
		yaw += xoffset;

		// 3. step: add constraints to the minimum and maximum pitch values.
		if (pitch < -89.0F)
		{
			pitch = -89.0F;
		}
		if (pitch > 89.0F)
		{
			pitch = 89.0F;
		}

		// 4. and final step: calculate the ACTUAL camera's direction vector, the result of subtracting the camera's
		// position from the camera's target (thus visually ending at the camera's target, the minuend of subtraction).
		updateCoordinateSystemOfCamera();
	}

	// Utility function for processing the mouse scrolling.
	void processMouseScroll(float yoffset)
	{
		fov -= yoffset;
		if (fov < 1.0F)
		{
			fov = 1.0F;
		}
		if (fov > 45.0F)
		{
			fov = 45.0F;
		}
	}

	// Utility function for resetting the camera to the default position, meant for the orthogonal projection.
	void resetToDefaultPositionMeantForOrthogonalProjection()
	{
		position = glm::vec3(0.0F, 0.0F, 3.55F);
		upVector = glm::vec3(0.0F, 1.0F, 0.0F);
		pitch = 0.0F;
		yaw = -90.0F;
		fov = 45.0F;

		updateCoordinateSystemOfCamera();
	}
};
#endif
