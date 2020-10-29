#pragma once

struct AABB
{
	AABB() : maxY(0), minY(0), minX(0), maxX(0), maxZ(0), minZ(0) {};
	AABB(float _maxY, float _minY, float _maxX, float _minX, float _maxZ, float _minZ) :
		maxY(_maxY),
		minY(_minY),
		maxX(_maxX),
		minX(_minX),
		maxZ(_maxZ),
		minZ(_minZ)
	{};
	float sizeX() const {
		return abs(maxX - minX);
	};
	float sizeY() const {
		return abs(maxY - minY);
	}
	float sizeZ() const {
		return abs(maxZ - minZ);
	}
	float maxY;
	float minY;
	float maxX;
	float minX;
	float maxZ;
	float minZ;
};