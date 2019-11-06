#include "Entity.h"

std::vector<unsigned int> indices = { 0, 1, 2, 0, 2, 3 };

Entity::Entity(const std::vector<float>& vertices, float width, float height,
            const std::string& texPath, int texRows, int texCols,
            glm::vec3 position, float angle, glm::vec3 scale)
    : m_VBO(vertices.data(), vertices.size() * sizeof(float), GL_DYNAMIC_DRAW),
      m_IBO(indices.data(), indices.size() * sizeof(unsigned int), GL_DYNAMIC_DRAW),
      m_Width(width), m_Height(height),
      m_Pos(position), m_Angle(angle), m_Scale(scale), 
      m_Texture(texPath, texRows, texCols), m_Rows(texRows), m_Cols(texCols)
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

    shader.Bind();

    m_Texture.Bind(0);
	shader.SetUniform1i("u_Texture", 0);
}

void Entity::Unbind() const {
    m_VAO.Unbind();
    m_VBO.Unbind();
    m_IBO.Unbind();
}

void Entity::Draw(Shader& shader, glm::mat4* vp) const {
    Bind(shader);

	glm::mat4 model = ComputeModel();
	glm::mat4 mvp = *(vp) * model;

	shader.SetUniformMat4f("u_MVP", mvp);
	shader.SetUniformVec2f("u_TexOffset", GetTexOffset());

	glDrawElements(GL_TRIANGLES, GetIBOSize() / 3, GL_UNSIGNED_INT, nullptr);
}

glm::mat4 Entity::ComputeModel() const {
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
    return glm::vec2(m_Sprite % m_Cols, (m_Rows-1)-((m_Sprite / m_Cols) % m_Rows)) * glm::vec2(m_Texture.GetSpriteWidth(), m_Texture.GetSpriteHeight()); 
}