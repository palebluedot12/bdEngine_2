#include "pch.h"
#include "InputManager.h"

std::vector<Input::Key> Input::Keys = {};

int ASCII[(UINT)eKeyCode::End] =
{
	'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
	'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
	'Z', 'X', 'C', 'V', 'B', 'N', 'M',
	VK_LEFT, VK_RIGHT, VK_DOWN, VK_UP, VK_RETURN, VK_BACK
};

void Input::Initailize()
{
	CreateKeys();
}

void Input::Update()
{
	UpdateKeys();
}
void Input::CreateKeys()
{
	for (size_t i = 0; i < (UINT)eKeyCode::End; i++)
	{
		Key key = {};
		key.bPressed = false;
		key.state = eKeyState::None;
		key.keyCode = (eKeyCode)i;

		Keys.push_back(key);
	}
}

void Input::UpdateKeys()
{
	std::for_each(Keys.begin(), Keys.end(),
		[](Key& key) -> void
		{
			UpdateKey(key);
		});
}

void Input::UpdateKey(Input::Key& key)
{
	if (IsKeyDown(key.keyCode))
	{
		UpdateKeyDown(key);
	}
	else
	{
		UpdateKeyUp(key);
	}
}

bool Input::IsKeyDown(eKeyCode code)
{
	return GetAsyncKeyState(ASCII[(UINT)code]) & 0x8000;
}

void Input::UpdateKeyDown(Input::Key& key)
{
	if (key.bPressed == true)
		key.state = eKeyState::Pressed;
	else
		key.state = eKeyState::Down;

	key.bPressed = true;
}
void Input::UpdateKeyUp(Input::Key& key)
{
	if (key.bPressed == true)
		key.state = eKeyState::Up;
	else
		key.state = eKeyState::None;

	key.bPressed = false;
}