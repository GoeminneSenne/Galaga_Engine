#pragma once

#include <vector>
#include <chrono>


#include "Component.h"

namespace dae
{
	class CacheGraph final : public Component
	{
	public:
		explicit CacheGraph(GameObject* pOwner);

		virtual void RenderUI() override;

		void SampleIntCache();

	private:
		int m_sampleCount{ 10 };
		std::vector<float> m_elapsedTimes;
	};
}