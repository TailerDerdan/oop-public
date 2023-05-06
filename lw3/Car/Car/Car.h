#pragma once

enum class Direction { Forward, Backward, Standing };
enum class Gear { ErrorGear = -2, ReverseGear, NeutralGear, FirstGear, SecondGear, ThirdGear, FourthGear, FiveGear };

class Car
{
public:
	bool isTurnedOn() const;
	Direction GetDirection() const;
	// unsigned int or int
	int GetSpeed() const;
	Gear GetGear() const;

	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);
private:
	Gear ReturnTheTransferValue(int gear);
	Gear ChangeGearDependingSpeed(int lowerLimit, int underLimit, int gear);
	bool m_engineState = false;//переименовать в m_engineIsOn
	int m_speed = 0;
	Gear m_gear = Gear::NeutralGear;
};