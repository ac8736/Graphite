#include "Camera.h"

Camera::Camera(float lastX, float lastY, glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : m_LastX(lastX), m_LastY(lastY), m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(DefaultCamera::MovementSpeed), m_MouseSensitivity(DefaultCamera::Sensitivity), m_Zoom(DefaultCamera::Zoom)
{
    m_Position = position;
    m_WorldUp = up;
    m_Yaw = yaw;
    m_Pitch = pitch;
    UpdateCameraVectors();
}

void Camera::ProcessKeyboard(CameraMovement direction, float deltaTime)
{
    float velocity = m_MovementSpeed * deltaTime;
    if (direction == FORWARD)
    {
        m_Position += m_Front * velocity;
    }
    if (direction == BACKWARD)
    {
        m_Position -= m_Front * velocity;
    }
    if (direction == LEFT)
    {
        m_Position -= m_Right * velocity;
    }
    if (direction == RIGHT)
    {
        m_Position += m_Right * velocity;
    }
    if (direction == UP)
    {
        m_Position += m_Up * velocity;
    }
    if (direction == DOWN)
    {
        m_Position -= m_Up * velocity;
    }
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= m_MouseSensitivity;
    yoffset *= m_MouseSensitivity;

    m_Yaw += xoffset;
    m_Pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (m_Pitch > 89.0f)
            m_Pitch = 89.0f;
        if (m_Pitch < -89.0f)
            m_Pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
    m_Zoom -= (float)yoffset;
    if (m_Zoom < 1.0f)
    {
        m_Zoom = 1.0f;
    }
    if (m_Zoom > 45.0f)
    {
        m_Zoom = 45.0f;
    }
}

void Camera::SetFirstMouse(bool set)
{
    m_FirstMouse = set;
}

void Camera::SetLastX(float x)
{
    m_LastX = x;
}

void Camera::SetLastY(float y)
{
    m_LastY = y;
}

glm::mat4 Camera::GetViewMatrix() const
{
    return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

void Camera::UpdateCameraVectors()
{
    // calculate the new Front vector
    glm::vec3 front{};
    front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    front.y = sin(glm::radians(m_Pitch));
    front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Front = glm::normalize(front);

    // also re-calculate the Right and Up vector
    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}
