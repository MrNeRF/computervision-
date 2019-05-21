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
        glm::vec3 m_right = glm::vec3(1.0f, 0.0f, 0.0f);
        glm::vec3 m_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);


        float m_yaw = Constants::YAW;
        float m_roll = Constants::ROLL;
        float m_pitch = Constants::PITCH;
        float m_zoom = Constants::ZOOM;
        float m_movementSpeed = Constants::SPEED;
        float m_mouseSensitivity = Constants::SENSITYVITY; 

        glm::mat4 viewMatrix = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
        glm::quat cameraQuat = glm::toQuat(viewMatrix);
        int lastkey = 0;
        glm::vec3 move = glm::vec3(0.f,0.f,0.f);
};

void Camera::updateView(void)
{
    glm::quat quatPitch = glm::quat(glm::vec3(m_pitch, 0.0f, 0.0f)); 
    glm::quat quatYaw = glm::quat(glm::vec3(0.0f, m_yaw, 0.0f)); 
    m_pitch = m_roll = m_yaw = 0.0f;

    cameraQuat = quatPitch * cameraQuat * quatYaw;
    cameraQuat = glm::normalize(cameraQuat);
    glm::mat4 rotate = glm::mat4_cast(cameraQuat);

    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, move);

    viewMatrix = rotate * trans;
}

void Camera::ProcessInput(GLFWwindow *window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = 2.5 * deltaTime; 
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        if (lastkey != GLFW_KEY_W)
        {
            m_cameraPos = glm::vec3(0.f, 0.f, 0.f);
        }
        else
        {
            m_cameraPos += cameraSpeed * m_cameraUp;
        }
        
        lastkey = GLFW_KEY_W;

    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        if (lastkey != GLFW_KEY_S)
        {
            m_cameraPos = glm::vec3(0.f, 0.f, 0.f);
        }
        else
        {
            m_cameraPos -= cameraSpeed * m_cameraUp;
        }
        lastkey = GLFW_KEY_S;
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        if (lastkey != GLFW_KEY_A)
        {
            m_cameraPos = glm::vec3(0.f, 0.f, 0.f);
        }
        else
        {
            m_cameraPos -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * cameraSpeed;
        }
        lastkey = GLFW_KEY_A;
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 
    {
        if (lastkey != GLFW_KEY_D)
        {
            m_cameraPos = glm::vec3(0.f, 0.f, 0.f);
        }
        else
        {
            m_cameraPos += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * cameraSpeed;
        }
        lastkey = GLFW_KEY_D;
    }
    else
    {
            m_cameraPos = glm::vec3(0.f, 0.f, 0.f);
     }
    
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        move += glm::vec3(1.f, 0.f, 0.f) * cameraSpeed * 10.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        move -= glm::vec3(1.f, 0.f, 0.f) * cameraSpeed * 10.f;
    }
    else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        move -= glm::vec3(0.f, 0.f, 1.f) * cameraSpeed * 10.f;
    }
    else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        move += glm::vec3(0.f, 0.f, 1.f) * cameraSpeed * 10.f;
    }

    m_yaw = m_cameraPos.x;
    m_pitch = m_cameraPos.y;
    std::cout << move.x << " " << move.y << std::endl;
    updateView();
}