#ifndef FINITESTATEMACHINE_H_
#define FINITESTATEMACHINE_H_
#include <vector>
#include "State.h"
class FiniteStateMachine {
public:
	FiniteStateMachine();

	// pushes a new state into the stack
	void PushState(State* s);

	// switches from one state to another state
	void ChangeState(State* s);

	// removes the top state from the stack
	void PopState();

	// return the current state
	State* GetCurrentState();

	~FiniteStateMachine();

private:
	std::vector<State*> m_currentState;
};

#endif // !FINITESTATEMACHINE_H_




