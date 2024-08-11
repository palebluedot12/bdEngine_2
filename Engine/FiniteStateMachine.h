#pragma once
#include "Component.h"
#include "FSMState.h"

class FiniteStateMachine : public Component
{
public:
	FiniteStateMachine();
	virtual ~FiniteStateMachine();
	virtual void Update() override;
	virtual void Render() override;

	FSMState* GetNowState() { return m_NowState; }

	template<typename T, typename = std::enable_if<std::is_base_of<FSMState, T>::value>>
	void ChangeState()
	{
		// 현재 상태(m_Nowstate)가 없거나, 새로운 상태 T가 현재 상태와 다른 타입일 때
		if (!m_NowState || !std::is_same_v<T, std::decay_t<decltype(*m_NowState)>>)
		{
			if (m_NowState)
			{
				m_NowState->Exit();
				delete m_NowState;
			}

			m_NowState = new T;
			m_NowState->SetOwner(m_Owner);
			m_NowState->SetFSM(this);
		}
		m_NowState->Enter();
	}

private:
	FSMState* m_NowState = nullptr;

};

