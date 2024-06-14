#pragma once

class DeltaTime
{
public:
	DeltaTime() {}
	~DeltaTime() {}

	void UpdateDeltaTime(float currentFrame);

	inline float GetDeltaTime() const { return m_DeltaTime; }
private:
	float m_DeltaTime = 0.0f;
	float m_LastFrame = 0.0f;
};
