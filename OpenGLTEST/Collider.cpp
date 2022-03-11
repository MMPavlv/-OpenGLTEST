#include "Collider.h"
#include <glm/detail/func_geometric.inl>
#include <iostream>

bool LGE::Collider::Collide(std::pair<Collider*, glm::vec3> FirstCollider, std::pair<Collider*, glm::vec3> SecondCollider)
{
	if (FirstCollider.first->Type == ColliderType::AABB 
		&& SecondCollider.first->Type == ColliderType::Cylinder)
	{
		return AABBCylinderCollide(FirstCollider, SecondCollider);
	}
}

bool LGE::Collider::AABBCylinderCollide(std::pair<Collider*, glm::vec3> FirstCollider, std::pair<Collider*, glm::vec3> SecondCollider)
{
	AABBCollider* FC = dynamic_cast<AABBCollider*>(FirstCollider.first);

	CylinderCollider *SC = dynamic_cast<CylinderCollider*>(SecondCollider.first);

	auto d2 = getDimensionIntersection(std::make_pair(FC->LeftNearBottom.y, FC->RightFarUpper.y),
		std::make_pair(SC->Center.y - SC->Height / 2, SC->Center.y + SC->Height / 2));

	auto f = getFlatCircleIntersection(FC->getFlatCollider(), SC->getFlatCollider());

	if (f.first)
	{
		std::cout << f.second.x << " " << f.second.y << std::endl;
		return true;
	}

	return false;
}

std::pair<bool, float> LGE::Collider::getDimensionIntersection(std::pair<float, float> d1, std::pair<float, float> d2)
{
	float d1mid = (d1.first + d1.second) / 2; //TODO midpoint overflow
	float d2mid = (d2.first + d2.second) / 2; //TODO midpoint overflow
	float diff = d2mid - d2mid;
	bool res = false;

	if (d2.second > d1.first && d2.first < d1.first)
	{
		res = true;
	}

	if (d2.second > d1.second && d2.second < d1.first)
	{
		res = true;
	}

	return std::make_pair(res, diff);
}

std::pair<bool, glm::vec2> LGE::Collider::getFlatCircleIntersection(flat_AABBCollider f1, flat_CylinderCollider f2)
{
	bool res = false;

	glm::vec2 midpoint = glm::vec2((f1.first.x + f1.second.x)/2, (f1.first.y + f1.second.y) / 2); //TODO midpoint overflow

	glm::vec2 diff = midpoint - f2.first;

	glm::vec2 p1 = f1.first;
	glm::vec2 p2 = glm::vec2(f1.first.x, f1.second.y);
	glm::vec2 p3 = glm::vec2(f1.second.x, f1.first.y);
	glm::vec2 p4 = f1.second;

	auto d1 = glm::distance(p1, f2.first);
	auto d2 = glm::distance(p2, f2.first);
	auto d3 = glm::distance(p3, f2.first);
	auto d4 = glm::distance(p4, f2.first);

	if (d1 < f2.second || d2 < f2.second || d3 < f2.second || d4 < f2.second)
	{
		res = true;
	}

	return std::make_pair(res, diff);
}


LGE::AABBCollider::AABBCollider(ColliderType _colliderType, glm::vec3 lnb, glm::vec3 rfu)
{
	_LeftNearBottom = lnb;
	_RightFarUpper = rfu;

	Type = _colliderType;
}

void LGE::AABBCollider::shiftCollider()
{
	LeftNearBottom = _LeftNearBottom + shift;
	RightFarUpper = _RightFarUpper + shift;
}

LGE::flat_AABBCollider LGE::AABBCollider::getFlatCollider()
{
	glm::vec2 LeftNear = glm::vec2(LeftNearBottom.x, LeftNearBottom.z);
	glm::vec2 RightFar = glm::vec2(RightFarUpper.x, RightFarUpper.z);

	return std::make_pair(LeftNear, RightFar);
}

LGE::CylinderCollider::CylinderCollider(ColliderType _colliderType, glm::vec3 _center, float _height, float _rad)
{
	Type = _colliderType;
	_Center = _center;
	Height = _height;
	Rad = _rad;
}

void LGE::CylinderCollider::shiftCollider()
{
	Center = _Center + shift;
}

LGE::flat_CylinderCollider LGE::CylinderCollider::getFlatCollider()
{
	glm::vec2 FlatCenter = glm::vec2(Center.x, Center.z);
	return std::make_pair(FlatCenter, Rad);
}
