#include "Input.h"
#include "Logger.h"

Input::Input(void)
{
  m_mouseDelta = glm::vec2(0, 0);
  m_mousePosition = glm::vec2(0, 0);
}

Input::~Input(void)
{
}

void Input::storeLastFrame()
{
	m_buttonStateOld = m_buttonState;
	m_keyStateOld = m_keyState;
}

void Input::handleKeyboardEvent(SDL_KeyboardEvent keyEvent)
{
  m_keyState[keyEvent.keysym.sym] = keyEvent.state;
  m_keyModState = SDL_GetModState();
}

void Input::handleMouseEvent(SDL_MouseButtonEvent buttonEvent)
{
  m_buttonState[buttonEvent.button] = buttonEvent.state;
}

void Input::handleMouseWheelEvent(Sint32 x, Sint32 y)
{
  m_mouseWheel.x = x;
  m_mouseWheel.y = y;
}

void Input::handleMultigesture(SDL_MultiGestureEvent multigestureEvent)
{
}

bool Input::isPressed(SDL_Keycode key)
{
  return (m_keyState[key] == SDL_PRESSED);
}

bool Input::isReleased(SDL_Keycode key)
{
  return (m_keyState[key] == SDL_RELEASED);
}

Input::InputState Input::keyState(SDL_Keycode key)
{
	int just = m_keyState[key] != m_keyStateOld[key];
	return (InputState)(m_keyState[key] | (just<<1));
}

bool Input::mouseIsPressed(Uint8 button)
{
  return (m_buttonState[button] == SDL_PRESSED);
}

bool Input::mouseIsReleased(Uint8 button)
{
  return (m_buttonState[button] == SDL_RELEASED);
}

Input::InputState Input::mousePressedState(Uint8 button)
{
	auto just = m_buttonState[button] != m_buttonStateOld[button];
	return (InputState)(m_buttonState[button] | (just<<1));
}

void Input::setMouseDelta(int x, int y)
{
  m_mouseDelta.x = x;
  m_mouseDelta.y = y;
}

void Input::setMousePosition(int x, int y)
{
  m_mousePosition.x = x;
  m_mousePosition.y = y;
}

glm::vec2 Input::getMouseDelta(void) const
{
  return m_mouseDelta;
}

glm::vec2 Input::getMousePosition(void) const
{
  return m_mousePosition;
}

glm::vec2 Input::getMouseWheel(void) const
{
  return m_mouseWheel;
}

SDL_Keymod Input::getKeyModState(void) const
{
  return m_keyModState;
}

void Input::grabMouse(void)
{
  SDL_SetRelativeMouseMode(SDL_TRUE);
}

void Input::releaseMouse(void)
{
  SDL_SetRelativeMouseMode(SDL_FALSE);
}
