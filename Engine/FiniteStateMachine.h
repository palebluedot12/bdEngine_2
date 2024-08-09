#pragma once
#include "Component.h"
#include "FSMState.h"

class FiniteStateMachine : public Component
{
public:
	FiniteStateMachine();
	virtual ~FiniteStateMachine();
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	FSMState* GetNowState() { return _nowState; }

	template<typename T, typename = std::enable_if<std::is_base_of<FSMState, T>::value>>
	void ChangeState()
	{
		if (!_nowState || !std::is_same_v<T, std::decay_t<decltype(*_nowState)>>)
		{
			if (_nowState)
			{
				_nowState->Exit();
				delete _nowState;
			}

			_nowState = new T;
			_nowState->SetOwner(_owner);
			_nowState->SetFSM(this);
		}
		_nowState->Enter();
	}

private:
	FSMState* _nowState = nullptr;

};

