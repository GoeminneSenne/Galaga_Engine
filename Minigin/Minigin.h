#pragma once
#include <string>
#include <functional>
#include <filesystem>
#include <chrono>

namespace dae
{
	class Minigin final
	{
		bool m_quit{};
		std::chrono::time_point<std::chrono::steady_clock> m_lastTime
		{std::chrono::high_resolution_clock::now()};
		float m_lag{0.f};
		float m_fixedTimeStep{ 0.02f };
		int m_msPerFrame{ 16 };
	public:
		explicit Minigin(const std::filesystem::path& dataPath);
		~Minigin();
		void Run(const std::function<void()>& load);
		void RunOneFrame();

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;
	};
}