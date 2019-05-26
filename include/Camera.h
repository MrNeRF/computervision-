#include <vector>
#include <GLFW/glfw3.h>

#define GLM_FORCE_CXX14
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Constants
{
    const float YAW = -90.f;
    const float PITCH = 0.0f;
    const float SPEED = 2.5f;
    const float SENSITYVITY = 0.1f;
    const float ZOOM = 45.0f;
    const float ROLL = 0.0f;
};

class Camera
{
    private:
     enum class ECamDir
    {
        forward,
        backward,
        left,
        right
    };

    public:
        Camera() = default;
        Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) :
            m_cameraPos{position}, m_worldUp{up} {};
        ~Camera() = default;
        void ProcessInput(GLFWwindow *window, float deltaTime);
        glm::mat4 GetViewMatrix(void) {return viewMatrix;};

    private:
        void updateView(void);

    private:
        glm::vec3 m_cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 m_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 m_cameraRight = glm::vec3(1.0f, 0.0f, 0.0f);
        glm::vec3 m_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);


        float m_yaw = Constants::YAW;
        float m_roll = Constants::ROLL;
        float m_pitch = Constants::PITCH;
        float m_zoom = Constants::ZOOM;
        float m_m_cameraPositionmentSpeed = Constants::SPEED;
        float m_mouseSensitivity = Constants::SENSITYVITY; 

        glm::mat4 viewMatrix = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
        glm::quat cameraQuat = glm::toQuat(viewMatrix);
};

void Camera::updateView(void)
{
    glm::quat quatPitch = glm::quat(glm::vec3(m_pitch, 0.0f, 0.0f)); 
    glm::quat quatYaw = glm::quat(glm::vec3(0.0f, m_yaw, 0.0f)); 
    
    m_pitch = m_roll = m_yaw = 0.0f;

    cameraQuat =  quatYaw * quatPitch * cameraQuat * glm::conjugate(quatPitch) * glm::conjugate(quatYaw);
    cameraQuat = glm::normalize(cameraQuat);
    glm::mat4 rotate = glm::mat4_cast(cameraQuat);

    m_cameraFront =  glm::conjugate(quatPitch) * m_cameraFront * quatYaw; 
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, m_cameraPos);

    viewMatrix = rotate * trans;
}

void Camera::ProcessInput(GLFWwindow *window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = 2.5 * deltaTime; 
    
    // Translation
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        m_yaw -= cameraSpeed;
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        m_yaw += cameraSpeed;
    }
    else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        m_pitch -= cameraSpeed;
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
    {
        m_pitch += cameraSpeed;
    }
    else 
    {
       m_yaw = m_pitch = 0.0f; 
    }

// Rotation
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        m_cameraPos -= m_cameraFront * cameraSpeed;
    }
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        m_cameraPos += m_cameraFront * cameraSpeed;
    }
    else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        m_cameraPos += m_cameraRight * cameraSpeed;
    }
    else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        m_cameraPos -= m_cameraRight * cameraSpeed;
    }
    m_cameraRight = glm::normalize(glm::cross(m_cameraFront, m_worldUp));
    updateView();
}