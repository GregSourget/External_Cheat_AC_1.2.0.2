#pragma once
//c'est la strcture des entit ydans assault cube

class Entity {
public:
	char pad_0000[92];
	Vector3 feet;
	char pad_0068[56];
	Vector3 torso;
	char pad_00AC[52];
	float health;
	float shield;
};