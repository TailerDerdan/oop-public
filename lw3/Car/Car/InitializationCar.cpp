#include "Car.h"
#include <iostream>

//ѕереключить передачу можно только при включенном двигателе
//Ќа нейтральной передаче мы можем ехать вперед
//ѕри неверной команде говорить Unknow command

Gear Car::ReturnTheTransferValue(int gear)
{
	switch (gear)
	{
	case -1:
		return Gear::ReverseGear;
	case 0:
		return Gear::NeutralGear;
	case 1:
		return Gear::FirstGear;
	case 2:
		return Gear::SecondGear;
	case 3:
		return Gear::ThirdGear;
	case 4:
		return Gear::FourthGear;
	case 5:
		return Gear::FiveGear;
	default:
		return Gear::ErrorGear;
	}
}

Gear Car::ChangeGearDependingSpeed(int lowerLimit, int underLimit, int gear)
{
	if (m_speed >= lowerLimit && m_speed <= underLimit)
	{
		return ReturnTheTransferValue(gear);
	}
	return m_gear;
}

bool Car::isTurnedOn() const
{
	return m_engineState;
}

Direction Car::GetDirection() const
{
	if (m_speed > 0)
	{
		return Direction::Forward;
	}
	if (m_speed < 0)
	{
		return Direction::Backward;
	}
	return Direction::Standing;
}

int Car::GetSpeed() const
{
	return std::abs(m_speed);
}

Gear Car::GetGear() const
{
	return m_gear;
}

bool Car::TurnOnEngine()
{
	if (!isTurnedOn())
	{
		m_engineState = true;
		m_gear = Gear::NeutralGear;
		m_speed = 0;
	}
	return true;
}

bool Car::TurnOffEngine()
{
	if (m_gear == Gear::NeutralGear && m_speed == 0)
	{
		m_engineState = false;
		return true;
	}
	return false;
}

bool Car::SetGear(int gear)
{
	//сделать метод покороче
	if (!m_engineState)
	{
		return false;
	}
	//почему здесь фигурируют диапозоны скоростей
	switch (gear)
	{
	case -1://можно переключитс€ на заднюю передачу только при остановке
		if ((m_speed == 0) || (m_speed >= 0 && m_speed <= 20 && m_gear == Gear::NeutralGear))
		{
			m_speed = -m_speed;
			m_gear = Gear::ReverseGear;
		}
		else
		{
			return false;
		}
		break;
	case 0:
		m_gear = Gear::NeutralGear;
		break;
	case 1:
		if ((m_gear == Gear::ReverseGear && m_speed != 0) || (m_gear == Gear::NeutralGear && m_speed != 0))
		{
			return false;
		}
		if ((m_speed >= 0 && m_speed <= 20)
			|| (m_gear == Gear::NeutralGear && m_speed == 0)
			|| (m_speed == 0 && m_gear == Gear::ReverseGear))
		{
			m_gear = Gear::FirstGear;
		}
		else
		{
			return false;
		}
		break;
	case 2:
		m_gear = ChangeGearDependingSpeed(20, 50, gear);
		break;
	case 3:
		m_gear = ChangeGearDependingSpeed(30, 60, gear);
		break;
	case 4:
		m_gear = ChangeGearDependingSpeed(40, 90, gear);
		break;
	case 5:
		m_gear = ChangeGearDependingSpeed(20, 50, gear);
		break;
	default:
		return false;
	}

	if (m_gear == Gear::ErrorGear)
	{
		return false;
	}

	return true;
}

bool Car::SetSpeed(int speed)
{
	if (speed < 0)
	{
		return false;
	}
	switch (m_gear)
	{
	case Gear::ReverseGear:
		if (speed >= 0 && speed <= 20)
		{
			m_speed = -speed;
		}
		else
		{
			return false;
		}
		break;
	case Gear::NeutralGear:
		if (std::abs(m_speed) >= speed)
		{
			if (m_speed < 0)
			{
				m_speed = -speed;
			}
			else
			{
				m_speed = speed;
			}
		}
		else
		{
			return false;
		}
		break;
	case Gear::FirstGear:
		if (speed >= 0 && speed <= 30)
		{
			m_speed = speed;
		}
		else
		{
			return false;
		}
		break;
	case Gear::SecondGear:
		if (speed >= 20 && speed <= 50)
		{
			m_speed = speed;
		}
		else
		{
			return false;
		}
		break;
	case Gear::ThirdGear:
		if (speed >= 30 && speed <= 60)
		{
			m_speed = speed;
		}
		else
		{
			return false;
		}
		break;
	case Gear::FourthGear:
		if (speed >= 40 && speed <= 90)
		{
			m_speed = speed;
		}
		else
		{
			return false;
		}
		break;
	case Gear::FiveGear:
		if (speed >= 50 && speed <= 150)
		{
			m_speed = speed;
		}
		else
		{
			return false;
		}
		break;
	default:
		return false;
		break;
	}
	return true;
}