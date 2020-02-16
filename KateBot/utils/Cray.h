#ifndef _CRAY_H_
#define _CRAY_H_

#include "..\main.h"

class Cray
{
public:
	Cray(Vector origin, Vector direction) {
		this->origin = origin;
		this->direction = direction;

		this->direction_inverse.x = 1.0f / direction.x;
		this->direction_inverse.y = 1.0f / direction.y;
		this->direction_inverse.z = 1.0f / direction.z;
	};

	static Vector AngleToDirection(Vector angle)
	{
		angle.x = (angle.x) * 3.14159265 / 180;
		angle.y = (angle.y) * 3.14159265 / 180;

		float sinYaw = sin(angle.y);
		float cosYaw = cos(angle.y);

		float sinPitch = sin(angle.x);
		float cosPitch = cos(angle.x);

		Vector direction;
		direction.x = cosPitch * cosYaw;
		direction.y = cosPitch * sinYaw;
		direction.z = -sinPitch;

		return direction;
	}

	bool Trace(Vector leftbottom, Vector righttop, float& distance)
	{
		if (direction.x == 0.0f && (origin.x < fmin(leftbottom.x, righttop.x) || origin.x > fmax(leftbottom.x, righttop.x)))
			return false;

		if (direction.y == 0.0f && (origin.y < fmin(leftbottom.y, righttop.y) || origin.y > fmax(leftbottom.y, righttop.y)))
			return false;

		if (direction.z == 0.0f && (origin.z < fmin(leftbottom.z, righttop.z) || origin.z > fmax(leftbottom.z, righttop.z)))
			return false;

		float t1 = (leftbottom.x - origin.x) * this->direction_inverse.x;
		float t2 = (righttop.x - origin.x) * this->direction_inverse.x;
		float t3 = (leftbottom.y - origin.y) * this->direction_inverse.y;
		float t4 = (righttop.y - origin.y) * this->direction_inverse.y;
		float t5 = (leftbottom.z - origin.z) * this->direction_inverse.z;
		float t6 = (righttop.z - origin.z) * this->direction_inverse.z;

		float tmin = fmax(fmax(fmin(t1, t2), fmin(t3, t4)), fmin(t5, t6));
		float tmax = fmin(fmin(fmax(t1, t2), fmax(t3, t4)), fmax(t5, t6));

		if (tmax < 0) {
			distance = tmax;
			return false;
		}

		if (tmin > tmax) {
			distance = tmax;
			return false;
		}

		distance = tmin;
		return true;
	}

private:
	Vector origin, direction, direction_inverse;
};

#endif