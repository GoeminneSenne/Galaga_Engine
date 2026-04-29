#pragma once
#include <memory>
#include "GameObject.h"

namespace dae
{
	using EventId = unsigned int;

	struct EventArgs
	{
		virtual ~EventArgs() = default;
	};

	struct ScoreAddedArgs : public EventArgs
	{
		explicit ScoreAddedArgs(int scoreInc, GameObject* pTarget) : EventArgs(), scoreInc(scoreInc), pTarget(pTarget) {}

		int scoreInc;
		GameObject* pTarget;
	};

	struct PlaySFXArgs : public EventArgs
	{
		explicit PlaySFXArgs(std::string path) : EventArgs(), path(std::move(path)) {}

		std::string path;
	};

	struct Event
	{
		EventId id;
		std::unique_ptr<EventArgs> args;
	};


	template <int length> struct sdbm_hash
	{
		consteval static unsigned int _calculate(const char* const text, unsigned int& value)
		{
			const unsigned int character = sdbm_hash<length - 1>::_calculate(text, value);
			value = character + (value << 6) + (value << 16) - value;
			return text[length - 1];
		}

		consteval static unsigned int calculate(const char* const text)
		{
			unsigned int value = 0;
			const auto character = _calculate(text, value);
			return character + (value << 6) + (value << 16) - value;
		}
	};

	template <> struct sdbm_hash<1>
	{
		consteval static int _calculate(const char* const text, unsigned int&) { return text[0]; }
	};

	template <size_t N> consteval EventId make_sdbm_hash(const char (&text)[N])
	{
		return sdbm_hash<N - 1>::calculate(text);
	}
}
