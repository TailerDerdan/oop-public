#pragma once

enum class Direction { Forward, Backward, Standing };
enum class Gear { ReverseGear = -1, NeutralGear, FirstGear, SecondGear, ThirdGear, FourthGear, FiveGear };

class Car
{
public:
	bool isTurnedOn() const;
	Direction GetDirection() const;
	size_t GetSpeed() const;
	Gear GetGear() const;

	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);

private:
	bool m_engineState = false;
	Direction m_direction = Direction::Standing;
	size_t m_speed = 0;
	Gear m_gear = Gear::NeutralGear;
};