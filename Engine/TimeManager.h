#pragma once

class TimeManager
{
private:
	TimeManager() = default;

public:
	static TimeManager* GetInstance()
	{
		static TimeManager _instance;
		return &_instance;
	}

public:
	void Init();
	void Update();
	float GetDeltaTime() { return _deltaTime; }

private:
	unsigned int _frequency = 0;
	unsigned int _prevCount = 0;
	float _deltaTime = 0.f;
};

