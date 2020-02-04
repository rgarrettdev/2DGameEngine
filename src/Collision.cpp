#include "./Collision.h"

bool Collision::CheckRectCollision(const SDL_Rect& rectA, const SDL_Rect& rectB) {
	return (
		rectA.x + rectA.w >= rectB.x &&
		rectB.x + rectB.w >= rectA.x && //AABB alogrithm, checks if rectangle are overlapping.
		rectA.y + rectA.h >= rectB.y &&
		rectB.y + rectB.h >= rectA.y
		);
}