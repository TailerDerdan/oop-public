#include "ManageCar.h"
#include <string>

void OutputGear(const Car& car)
{
	switch (car.GetGear())
	{
	case Gear::ReverseGear:
		std::cout << "Gear is -1" << std::endl;
		break;
	case Gear::NeutralGear:
		std::cout << "Gear is 0" << std::endl;;
		break;
	case Gear::FirstGear:
		std::cout << "Gear is 1" << std::endl;;
		break;
	case Gear::SecondGear:
		std::cout << "Gear is 2" << std::endl;;
		break;
	case Gear::ThirdGear:
		std::cout << "Gear is 3" << std::endl;;
		break;
	case Gear::FourthGear:
		std::cout << "Gear is 4" << std::endl;;
		break;
	case Gear::FiveGear:
		std::cout << "Gear is 5" << std::endl;;
		break;
	default:
		break;
	}
}

void OutputStateEngine(const Car& car)
{
	if (car.isTurnedOn())
	{
		std::cout << "Engine is on" << std::endl;
	}
	if (!car.isTurnedOn())
	{
		std::cout << "Engine is off" << std::endl;
	}
}

void OutputDirection(const Car& car)
{
	switch (car.GetDirection())
	{
	case Direction::Backward:
		std::cout << "Direction is backward" << std::endl;
		break;
	case Direction::Forward:
		std::cout << "Direction is forward" << std::endl;
		break;
	case Direction::Standing:
		std::cout << "Direction is standing" << std::endl;
		break;
	default:
		break;
	}
}

void Info(const Car& car)
{
	OutputGear(car);
	std::cout << "Speed is " << car.GetSpeed() << std::endl;
	OutputStateEngine(car);
	OutputDirection(car);
}

void DialogWithUser()
{
	Car car;
	std::string line;

	while (std::getline(std::cin, line))
	{
		if (line == "Info")
		{
			Info(car);
		}
		if (line == "EngineOn")
		{
			car.TurnOnEngine();
		}
		if (line == "EngineOff")
		{
			if (!car.TurnOffEngine())
			{
				std::cout << "You can't turn off the engine" << std::endl;
			}
		}

		std::string command;
		std::string argument;
		size_t posSpace = line.find_first_of(" ");
		if (posSpace <= line.size())
		{
			command.append(line, 0, posSpace);
			argument.append(line, posSpace + 1, line.size() - posSpace);

			if (command == "SetGear")
			{
				if (!car.SetGear(stoi(argument)))
				{
					std::cout << "You can't change gear to" << argument << std::endl;
				}
			}
			if (command == "SetSpeed")
			{
				if (!car.SetSpeed(stoi(argument)))
				{
					std::cout << "You can't drive at " << argument << "this speed" << argument << std::endl;
				}
			}
		}
	}
}