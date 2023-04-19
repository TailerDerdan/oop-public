#include "Car.h"

bool Car::isTurnedOn() const
{
	return m_engineState;
}

Direction Car::GetDirection() const
{
	return m_direction;
}

size_t Car::GetSpeed() const
{
	return m_speed;
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
		m_direction = Direction::Standing;
	}
	return true;
}

bool Car::TurnOffEngine()
{
	if (m_gear == Gear::NeutralGear && m_speed == 0 && m_direction == Direction::Standing)
	{
		m_engineState = false;
		return true;
	}
	return false;
}

bool Car::SetGear(int gear)
{
	switch (gear)
	{
	case -1:
		if ((m_speed == 0) && (m_gear == Gear::NeutralGear) && (m_direction == Direction::Standing && m_engineState) || (m_speed >= 0 && m_speed <= 20 && m_engineState))
		{
			m_direction = Direction::Backward;
			m_gear = Gear::ReverseGear;
		}
		else
		{
			return false;
		}
		break;
	case 0:
		m_gear = Gear::NeutralGear;
		m_direction = Direction::Backward;
		break;
	case 1:
		if ((m_gear == Gear::NeutralGear && m_speed != 0 && m_direction == Direction::Standing && m_engineState) || (m_speed >= 0 && m_speed <= 20 && m_engineState))
		{
			m_gear = Gear::FirstGear;
			m_direction = Direction::Forward;
		}
		else
		{
			return false;
		}
		break;
	case 2:
		if (m_speed >= 20 && m_speed <= 50)
		{
			m_gear = Gear::SecondGear;
			m_direction = Direction::Forward;
		}
		break;
	case 3:
		if (m_speed >= 30 && m_speed <= 60)
		{
			m_gear = Gear::ThirdGear;
			m_direction = Direction::Forward;
		}
		break;
	case 4:
		if (m_speed >= 40 && m_speed <= 90)
		{
			m_gear = Gear::FourthGear;
			m_direction = Direction::Forward;
		}
		break;
	case 5:
		if (m_speed >= 50 && m_speed <= 150)
		{
			m_gear = Gear::FiveGear;
			m_direction = Direction::Forward;
		}
		break;
	default:
		return false;
	}

	return true;
}

bool Car::SetSpeed(int speed)
{
	switch (m_gear)
	{
	case Gear::ReverseGear:
		if (m_speed >= 0 && m_speed <= 20)
		{
			m_speed = speed;
			if (speed == 0)
			{
				m_direction = Direction::Standing;
			}
		}
		else
		{
			return false;
		}
		break;
	case Gear::NeutralGear:
		if (m_speed >= speed)
		{
			m_speed = speed;
			if (speed == 0)
			{
				m_direction = Direction::Standing;
			}
		}
		else
		{
			return false;
		}
		break;
	case Gear::FirstGear:
		if (m_speed >= 0 && m_speed <= 30)
		{
			m_speed = speed;
			if (speed == 0)
			{
				m_direction = Direction::Standing;
			}
		}
		else
		{
			return false;
		}
		break;
	case Gear::SecondGear:
		if (m_speed >= 20 && m_speed <= 50)
		{
			m_speed = speed;
		}
		else
		{
			return false;
		}
		break;
	case Gear::ThirdGear:
		if (m_speed >= 30 && m_speed <= 60)
		{
			m_speed = speed;
		}
		else
		{
			return false;
		}
		break;
	case Gear::FourthGear:
		if (m_speed >= 40 && m_speed <= 90)
		{
			m_speed = speed;
		}
		else
		{
			return false;
		}
		break;
	case Gear::FiveGear:
		if (m_speed >= 50 && m_speed <= 150)
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