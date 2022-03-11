#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <memory>
#include "shader_s.h"
#include <vector>
#include "Collider.h"


namespace LGE
{
	enum class GameObjectType
	{
		staticObject,
		dynamicObject, 
		userobject
	};

	class GameObject
	{
	public:
		unsigned int ID;
		glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.0f);
		GameObjectType ObjectType;
		glm::vec3 GlobalCoords = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 prevGlobalCoords = glm::vec3(0.0f, 0.0f, 0.0f);
		float GlobalRotation;
		Collider *LocalCollider;
		int shaderID;

		void setLocalVelocity(glm::vec3 _localVelocity);
		void updateCollider();
		void move();
		void move(glm::vec3 _coords);
		virtual ~GameObject() = default;
	};

	class GameObjectPolyhedron : public GameObject
	{
	public:
		unsigned int VBO, VAO;
		std::vector<float> LocalCoords;

		GameObjectPolyhedron(GameObjectType objType, unsigned int _ID, std::vector<float> &obj, int _shaderID, glm::vec3 coords, float rotat)
		{
			ID = _ID;
			ObjectType = objType;
			LocalCoords = std::vector<float>(obj);
			shaderID = _shaderID;
			GlobalCoords = coords;
			GlobalRotation = rotat;
			////
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);

			glBindVertexArray(VAO);

			auto local_coord = &LocalCoords[0];

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(*local_coord)*LocalCoords.size(), local_coord, GL_STATIC_DRAW);

			// Координатные атрибуты
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			// Атрибуты цвета
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
			// Атрибуты текстурных координат
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			glEnableVertexAttribArray(2);

			glBindVertexArray(0);
		}

		void setCollider(Collider *c)
		{
			switch (c->Type)
			{
			case ColliderType::AABB:
				{
					AABBCollider* AABBcoll = dynamic_cast<AABBCollider*>(c);
					LocalCollider = AABBcoll;
					break;
				}
				
			case ColliderType::Cylinder:
				{
					CylinderCollider* CylinderColl = dynamic_cast<CylinderCollider*>(c);
					LocalCollider = CylinderColl;
					break;
				}
				
			}
		}

		void bind()
		{
			glBindVertexArray(VAO);
		}

		void Draw()
		{
			glDrawArrays(GL_TRIANGLES, 0, LocalCoords.size() / 8);
		}

		void Dispose()
		{
			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
		}


		glm::vec3 getCameraFrom()
		{
			return (this->GlobalCoords + glm::vec3(0.0f, 0.6f, 0.0f));
		}

		glm::vec3 getCameraTo()
		{
			float _x = this->GlobalCoords.x - 1.0f*glm::sin(glm::radians(360 * this->GlobalRotation));
			float _y = this->GlobalCoords.y;
			float _z = this->GlobalCoords.z - 1.0f*glm::cos(glm::radians(360 * this->GlobalRotation));;
			return glm::vec3(_x, _y + 0.5f, _z);
		}
	};
}
