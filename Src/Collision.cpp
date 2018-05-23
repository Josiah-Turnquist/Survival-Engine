#include "Collision.h"
#include "ECS/ColliderComponent.h"

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB)
{
	if (
		recA.x + recA.w >= recB.x + 100 &&
		recB.x + recB.w >= recA.x + 100 &&
		recA.y + recA.h >= recB.y + 50 &&
		recB.y + recB.h >= recA.y + 50
		)
	{
		return true;
	}

	return false;
}

bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB)
{
	if (AABB(colA.collider, colB.collider))
	{
		//std::cout << colA.tag << " hit: " << colB.tag << std::endl;
		return true;
	}
	else
	{
		return false;
	}
}
