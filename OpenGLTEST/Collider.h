#pragma once
#include <glm/vec3.hpp>
#include <utility>
#include <glm/vec2.hpp>

namespace LGE
{
	using flat_AABBCollider = std::pair<glm::vec2, glm::vec2>;
	using flat_CylinderCollider = std::pair<glm::vec2, float>;

	enum class ColliderType
	{
		AABB,
		Cylinder
	};

	class Collider
	{
	public:
		ColliderType Type;
		glm::vec3 shift = glm::vec3(0.0f, 0.0f, 0.0f);

		float Delta = 0.005f;

		virtual void shiftCollider() = 0;

		static bool Collide(std::pair<Collider*, glm::vec3> FirstCollider, std::pair<Collider*, glm::vec3> SecondCollider);

		virtual ~Collider() = default;

	private:
		//static void AABBCollide(std::pair<Collider, glm::vec3> FirstCollider, std::pair<Collider, glm::vec3> SecondCollider);

		static bool AABBCylinderCollide(std::pair<Collider*, glm::vec3> FirstCollider, std::pair<Collider*, glm::vec3> SecondCollider);

		static std::pair<bool, float> getDimensionIntersection(std::pair<float, float> d1, std::pair<float, float> d2);

		static std::pair<bool, glm::vec2> getFlatCircleIntersection(flat_AABBCollider f1, flat_CylinderCollider f2);
	};

	class AABBCollider : public Collider
	{
	private:
		glm::vec3 _LeftNearBottom;
		glm::vec3 _RightFarUpper;
	public:
		glm::vec3 LeftNearBottom = glm::vec3(0.0f, 0.0f, 0.0f);;
		glm::vec3 RightFarUpper = glm::vec3(0.0f, 0.0f, 0.0f);;

		AABBCollider(ColliderType _colliderType, glm::vec3 lnb, glm::vec3 rfu);
		void shiftCollider() override;

		flat_AABBCollider getFlatCollider();
	};

	class CylinderCollider : public Collider
	{
	private:
		glm::vec3 _Center;
	public:
		glm::vec3 Center = glm::vec3(0.0f, 0.0f, 0.0f);;
		float Height;
		float Rad;

		CylinderCollider(ColliderType _colliderType, glm::vec3 _center, float _height, float _rad);
		void shiftCollider() override;

		flat_CylinderCollider getFlatCollider();
	};
}
