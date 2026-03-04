#include "CacheGraph.h"

#include <algorithm>

#include "imgui.h"


dae::CacheGraph::CacheGraph(GameObject* pOwner)
	:Component{ pOwner } {}

void dae::CacheGraph::RenderUI()
{
	ImGui::Begin("Exercise 1");

	ImGui::SetNextItemWidth(20);
	ImGui::InputInt("##value", &m_sampleCount, 0, 0);

	ImGui::SameLine();
	if (ImGui::Button("-"))
		--m_sampleCount;

	ImGui::SameLine();
	if (ImGui::Button("+"))
		++m_sampleCount;

	ImGui::SameLine();
	ImGui::Text("#samples");

	if (ImGui::Button("Thrash the cache"))
	{
		SampleIntCache();
	}

	if (!m_elapsedTimes.empty())
	{
		ImGui::PlotLines("##", m_elapsedTimes.data(), (int)m_elapsedTimes.size(),
			0, nullptr, FLT_MAX, FLT_MAX, ImVec2(300, 150));
	}
	

	ImGui::End();
}

void dae::CacheGraph::SampleIntCache()
{

	constexpr int maxStepSize{ 1024 };

	m_elapsedTimes.clear();
	m_elapsedTimes.reserve(10);

	std::vector<int> arr(1 << 26);

	for (int stepSize = 1; stepSize <= maxStepSize; stepSize *= 2)
	{
		std::vector<float> samples(m_sampleCount);

		for (int sample{}; sample < m_sampleCount; ++sample)
		{
			auto start = std::chrono::high_resolution_clock::now();

			for (int i = 0; i < arr.size(); i += stepSize)
			{
				arr[i] += 1;
			}

			auto end = std::chrono::high_resolution_clock::now();
			auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			samples.push_back(static_cast<float>(elapsedTime));
		}

		std::ranges::sort(samples);

		samples.pop_back();
		samples.erase(samples.begin());

		float sum = 0.f;
		for (auto sample : samples)
		{
			sum += sample;
		}

		m_elapsedTimes.push_back(sum / (float)samples.size());

	}
}
