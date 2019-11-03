#include "Entity.h"

Entity::Entity(const SpriteData& data, const std::string& texPath, int texWidth, int texHeight)
    : m_VBO(data.m_vertices.data(), data.m_vertices.size() * sizeof(float), GL_DYNAMIC_DRAW),
      m_IBO(data.m_indices.data(), data.m_indices.size() * sizeof(unsigned int), GL_DYNAMIC_DRAW),
      m_Texture(texPath, texWidth, texHeight), 
      m_Pos(glm::vec3(0.0f)), m_Angle(0.0f), m_Scale(glm::vec3(1.0f))
{
	VertexBufferLayout layout;
	layout.PushFloat(2);
	layout.PushFloat(2);
	m_VAO.AddBuffer(m_VBO, layout);
}

Entity::Entity(const SpriteData& data, const std::string& texPath, int texWidth, int texHeight,
            glm::vec3 position, float angle, glm::vec3 scale)
    : m_VBO(data.m_vertices.data(), data.m_vertices.size() * sizeof(float), GL_DYNAMIC_DRAW),
      m_IBO(data.m_indices.data(), data.m_indices.size() * sizeof(unsigned int), GL_DYNAMIC_DRAW),
      m_Pos(position), m_Angle(angle), m_Scale(scale), m_Texture(texPath, texWidth, texHeight)
{
	VertexBufferLayout layout;
	layout.PushFloat(2);
	layout.PushFloat(2);
	m_VAO.AddBuffer(m_VBO, layout);
}

Entity::~Entity() {}

void Entity::Bind(Shader& shader) const {
    m_VAO.Bind();
    m_VBO.Bind();
    m_IBO.Bind();

    m_Texture.Bind(0);
	shader.SetUniform1i("u_Texture", 0);
}

void Entity::Unbind() const {
    m_VAO.Unbind();
    m_VBO.Unbind();
    m_IBO.Unbind();
}

void Entity::Draw(Shader& shader) const {
	Bind(shader);
	shader.Bind();

	glDrawElements(GL_TRIANGLES, GetIBOSize() / 3, GL_UNSIGNED_INT, nullptr);
}

glm::mat4 Entity::ComputeModel() {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, m_Pos);
	model = glm::rotate(model, glm::radians(m_Angle), m_AxisOfRotation);
	model = glm::scale(model, m_Scale);

    return model;
}

void Entity::Update(float dt) {     // change this to a general update call? or perhaps entity has an update call which this class will override?
    float pixels_per_meter = 16.0f;
    glm::vec3 m_Acceleration = glm::vec3(0.0f, -9.81f, 0.0f);

    m_Velocity += m_Acceleration * dt;

    if (m_Pos.y < 0.0f && m_Velocity.y < 0.0f) {
        m_Velocity.y = 0.0f;
        m_Pos.y = 0.0f;
    }

    m_Pos += m_Velocity * dt * pixels_per_meter;
}

glm::vec2 Entity::GetTexOffset() const { 
    return glm::vec2(m_Sprite % m_Cols, (m_Rows-1)-((m_Sprite / m_Cols) % m_Rows)) * glm::vec2(m_SpriteWidth, m_SpriteHeight); 
}