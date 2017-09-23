#include "glm/glm.hpp"

bool circleRectCollision(glm::vec2 rectCenter, glm::vec2 rectScale, glm::vec2 circleCenter, float radius)
{
	glm::vec2 rMin = rectCenter - rectScale / 2.0f - circleCenter;
	glm::vec2 rMax = rectCenter + rectScale / 2.0f - circleCenter;
	if (rMax.x < 0)
	{
		if(rMax.y < 0)
		{
			return rMax.x * rMax.x + rMax.y * rMax.y < radius * radius;
		}
		else if(rMin.y > 0)
		{
			return rMax.x * rMax.x + rMin.y * rMin.y < radius * radius;
		}
		return -rMax.x < radius;
	}
	else if (rMin.x > 0)
	{
		if(rMax.y < 0)
		{
			return rMin.x * rMin.x + rMax.y * rMax.y < radius * radius;
		}
		else if(rMin.y > 0)
		{
			return rMin.x * rMin.x + rMin.y * rMin.y < radius * radius;
		}
		return rMin.x < radius;
	}
	else
	{
		if(rMax.y < 0)
		{
			return -rMax.y < radius;
		}
		else if(rMin.y > 0)
		{
			return rMin.y < radius;
		}
		return true;
	}
}