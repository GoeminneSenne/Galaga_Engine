#pragma once

namespace dae
{
	
	class ICommand
	{
	public:
		virtual ~ICommand() = default;
		virtual void Execute(float deltaTime) = 0;
	};
}