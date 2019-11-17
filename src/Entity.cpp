#include "Entity.h"

std::vector<unsigned int> indices = { 0, 1, 2, 0, 2, 3 };

Entity::Entity( const std::string& texPath, int texRows, int texCols, glm::vec3 position, float angle)
    : m_Texture(texPath, texRows, texCols), m_Rows(texRows), m_Cols(texCols)
{
    m_Width = m_Texture.GetSpriteWidth() * m_Texture.GetWidth();
    m_Height = m_Texture.GetSpriteHeight() * m_Texture.GetHeight();

    std::vector<float> vertices = {
        -m_Width/2,  m_Height/2, 0.0f, 1.0f/texRows,  
         m_Width/2,  m_Height/2, 1.0f/texCols, 1.0f/texRows,  
         m_Width/2, -m_Height/2, 1.0f/texCols, 0.0f, 
        -m_Width/2, -m_Height/2, 0.0f, 0.0f
    };

    m_VBO = new VertexBuffer(vertices.data(), vertices.size() * sizeof(float), GL_DYNAMIC_DRAW);
    m_IBO = new IndexBuffer(indices.data(), indices.size() * sizeof(unsigned int), GL_DYNAMIC_DRAW);

	VertexBufferLayout layout;
	layout.PushFloat(2);
	layout.PushFloat(2);
	m_VAO.AddBuffer(*m_VBO, layout);

    SetPosition(position);
    if (angle != 0.0f) {
        SetAngle(angle);
    } else {
        m_Angle = angle;
    }
}

Entity::~Entity() {}

void Entity::Bind(Shader& shader) const {
    m_VAO.Bind();
    m_VBO->Bind();
    m_IBO->Bind();

    shader.Bind();

    m_Texture.Bind(0);
	shader.SetUniform1i("u_Texture", 0);
}

void Entity::Unbind() const {
    m_VAO.Unbind();
    m_VBO->Unbind();
    m_IBO->Unbind();
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

    return model;
}

void Entity::Update(float dt) {     // change this to a general update call? or perhaps entity has an update call which this class will override?
    SetPosition(m_Pos + m_Velocity);
}

void Entity::UpdateBounds() {
    m_TopLeft = glm::vec2(m_Pos.x - m_Width / 2, m_Pos.y + m_Height / 2);
    m_BottomRight = glm::vec2(m_Pos.x + m_Width / 2, m_Pos.y - m_Height / 2);
}

void Entity::SetPosition(glm::vec3 position) { 
    m_Pos = position;

    UpdateBounds();
}

void Entity::SetAngle(float angle) { 
    m_Angle = angle; 
    float radians = glm::radians(angle);

    float tempX1 = m_TopLeft.x - m_Pos.x;
    float tempY1 = m_TopLeft.y - m_Pos.y;

    float rotatedX1 = tempX1*cos(radians) - tempY1*sin(radians);
    float rotatedY1 = tempX1*sin(radians) + tempY1*cos(radians);

    float tempX2 = m_BottomRight.x - m_Pos.x;
    float tempY2 = m_BottomRight.y - m_Pos.y;

    float rotatedX2 = tempX2*cos(radians) - tempY2*sin(radians);
    float rotatedY2 = tempX2*sin(radians) + tempY2*cos(radians);

    m_TopLeft.x = rotatedX1 < rotatedX2 ? rotatedX1 : rotatedX2;
    m_TopLeft.y = rotatedY1 > rotatedY2 ? rotatedY1 : rotatedY2;

    m_BottomRight.x = rotatedX1 > rotatedX2 ? rotatedX1 : rotatedX2;
    m_BottomRight.y = rotatedY1 < rotatedY2 ? rotatedY1 : rotatedY2;

    m_TopLeft.x += m_Pos.x;
    m_TopLeft.y += m_Pos.y;
    m_BottomRight.x += m_Pos.x;
    m_BottomRight.y += m_Pos.y;
}

glm::vec2 Entity::GetTexOffset() const { 
    return glm::vec2(m_Sprite % m_Cols, (m_Rows-1)-((m_Sprite / m_Cols) % m_Rows)) * glm::vec2(m_Texture.GetSpriteWidth(), m_Texture.GetSpriteHeight()); 
}