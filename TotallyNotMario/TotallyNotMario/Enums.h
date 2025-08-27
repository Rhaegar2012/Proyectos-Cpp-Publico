#pragma  once
#ifndef ENUMS_H
#define ENUMS_H
#include<iostream>
enum ResourceType
{
	TEXTURE,
	SOUNDFX,
	MUSIC
};

enum Events
{
	JUMP_EVENT,
	DIE_EVENT,
	COLLECT_EVENT
};


enum EntityType
{
	GROUND,
	PLATFORM,
	SPIKE,
	GOAL,
	ENEMY,
	ITEM,
	PLAYER
};

enum EntityStates
{
	IDLE,
	MOVING,
	JUMPING,
	FALLING,
	GROUNDED,
	DEAD
};

enum AnimationStates
{
	Idle_1,
	Idle_2,
	Jumping_1,
	Jumping_2,
	Running_1,
	Running_2,
	Running_3
};

enum InputCommands
{
	MoveInput,
	JumpInput,
	NullInput
};

enum SoundFXResourceID
{
	JUMP,
	SQUISH,
	DIE,
	COIN
};

enum MusicResourceID
{
	//TODO: Populate with music
};
#endif