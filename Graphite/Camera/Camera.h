#pragma once
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

enum CameraMovement 
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
    UP,
    DOWN
};

struct DefaultCamera {
    static constexpr float MovementSpeed = 5.0f;
    static constexpr float Sensitivity = 0.1f;
    static constexpr float Zoom = 45.0f;
};

class Camera
{
public:
    Camera(float lastX, float lastY, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);

    void ProcessKeyboard(CameraMovement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
	void ProcessMouseScroll(float yoffset);

    void SetFirstMouse(bool set);
    void SetLastX(float x);
    void SetLastY(float y);

    glm::mat4 GetViewMatrix() const;
    inline float GetZoom() const { return m_Zoom; }
    inline float GetLastX() const { return m_LastX; }
    inline float GetLastY() const { return m_LastY; }
    inline glm::vec3 GetPosition() const { return m_Position; }
    inline bool IsFirstMouse() const { return m_FirstMouse; }
private:
    void UpdateCameraVectors();

    // camera Attributes
    glm::vec3 m_Position;
    glm::vec3 m_Front;
    glm::vec3 m_Up;
    glm::vec3 m_Right;
    glm::vec3 m_WorldUp;

    // euler Angles
    float m_Yaw, m_Pitch;

    // camera options
    float m_MovementSpeed;
    float m_MouseSensitivity;
    float m_Zoom;
    float m_LastX, m_LastY;

    bool m_FirstMouse = true;
};
