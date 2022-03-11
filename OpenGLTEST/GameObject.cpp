#include "GameObject.h"

void LGE::GameObject::setLocalVelocity(glm::vec3 _localVelocity)
{
	velocity.x = _localVelocity.z * glm::sin(glm::radians(360 * GlobalRotation)) + _localVelocity.x * glm::cos(glm::radians(360 * GlobalRotation));
	velocity.y = 0;
	velocity.z = _localVelocity.x * glm::sin(glm::radians(360 * GlobalRotation)) + _localVelocity.z * glm::cos(glm::radians(360 * GlobalRotation));
}

void LGE::GameObject::updateCollider()
{
	LocalCollider->shift = GlobalCoords;

	switch (LocalCollider->Type)
	{
	case ColliderType::AABB:
	{
		AABBCollider* coll = dynamic_cast<AABBCollider*>(LocalCollider);
		coll->shiftCollider();
		break;
	}

	case ColliderType::Cylinder:
	{
		CylinderCollider* coll = dynamic_cast<CylinderCollider*>(LocalCollider);
		coll->shiftCollider();
		break;
	}
	}
}

void LGE::GameObject::move()
{
	prevGlobalCoords = GlobalCoords;
	GlobalCoords += velocity;
	updateCollider();
}

void LGE::GameObject::move(glm::vec3 _coords)
{
	prevGlobalCoords = GlobalCoords;
	GlobalCoords = _coords;
	updateCollider();
}
