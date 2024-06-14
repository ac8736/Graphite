#include "DeltaTime.h"

void DeltaTime::UpdateDeltaTime(float currentFrame)
{
	m_DeltaTime = currentFrame - m_LastFrame;
	m_LastFrame = currentFrame;
}
