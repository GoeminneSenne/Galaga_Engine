#pragma once

#include "Component.h"

namespace dae
{
	class CacheGraph final : public Component
	{
	public:
		explicit CacheGraph(GameObject* pOwner);

		void SampleIntCache();

	private:
		int m_intSampleCount{ 10 };
	};
}