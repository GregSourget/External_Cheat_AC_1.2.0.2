#pragma once
class Player
{
public:
	Vector3 position;
	Vector3 velocity;
	Vector3 v;
	Vector3 vv;
	float yaw;
	float pitch;
	float roll;
};

class EntityList {
	Player* players[64]
};