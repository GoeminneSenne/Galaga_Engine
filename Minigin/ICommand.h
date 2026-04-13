#pragma once

namespace dae
{
	
	class ICommand
	{
	public:
		virtual void Execute(float deltaTime) = 0;

		virtual ~ICommand() = default;
		ICommand(const ICommand& other) = delete;
		ICommand(ICommand&& other) = delete;
		ICommand& operator=(const ICommand& other) = delete;
		ICommand& operator=(ICommand&& other) = delete;
	};
}