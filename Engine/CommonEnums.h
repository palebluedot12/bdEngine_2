#pragma once

enum class eWorldTag
{
	Default,
	Title,
	Scene1,
	Scene2,
	SIZE,
};

enum class eDirType
{
	UP,
	RIGHT,
	DOWN,
	LEFT,
};

// 업데이트 순서
enum class eComponentType
{
	Scene,
	Movement,
	Collider,
	Script,
	Animator,
	Camera,
	End,
};