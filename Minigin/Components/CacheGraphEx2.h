#pragma once

#include <vector>

#include "Component.h"

namespace dae
{
	class CacheGraphEx2 final : public Component
	{
	public:
		explicit CacheGraphEx2(GameObject* pOwner);

		virtual void RenderUI() override;

	private:
		int m_sampleCount{ 100 };
		std::vector<float> m_elapsedTimes;
		std::vector<float> m_elapsedTimesAlt;

		void SampleCache();
		void SampleCacheAlt();

		//Data structures for testing
		struct Transform
		{
			float matrix[16] = {
				1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				0,0,0,1 };
		};

		class GameObject3D
		{
		public:
			Transform transform;
			int ID;
		};

		class GameObject3DAlt
		{
		public:
			Transform* pTransform;
			int ID;
		};
	};
}