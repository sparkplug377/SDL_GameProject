#include "FiniteStateMachine.h"


FiniteStateMachine::FiniteStateMachine() {
}

void FiniteStateMachine::PushState(State * s) {
	s->OnEnter();
	m_currentState.push_back(s);
}

void FiniteStateMachine::ChangeState(State * s) {
	// if the stack is not empty
	if (!m_currentState.empty()) {
		// clear the memory of the last item in the stack
		m_currentState.back()->OnExit();
		// delete the current state from the memory
		delete m_currentState.back();
		// remove the top item from the stack
		m_currentState.pop_back();
	}
	// initialize the objects of the state
	s->OnEnter();
	// push the new state on to the stack
	m_currentState.push_back(s);
}


void FiniteStateMachine::PopState() {
	m_currentState.back()->OnExit();
	delete m_currentState.back();
	m_currentState.pop_back();
}

State * FiniteStateMachine::GetCurrentState() {
	return m_currentState.back();
}

FiniteStateMachine::~FiniteStateMachine() {
	for (auto s : m_currentState) {
		s->OnExit();
		delete s;
	}
}
