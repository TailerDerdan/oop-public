#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Car/ManageCar.h"

//переписать тесты с проверкой состояния
SCENARIO("Uniform shifting across 1-3 gears")
{
	Car car;
	car.TurnOnEngine();
	REQUIRE(car.isTurnedOn());
	car.SetGear(1);
	REQUIRE(car.GetGear() == Gear::FirstGear);
	car.SetSpeed(20);
	REQUIRE(car.GetSpeed() == 20);
	car.SetGear(2);
	REQUIRE(car.GetGear() == Gear::SecondGear);
	car.SetSpeed(30);
	REQUIRE(car.GetSpeed() == 30);
	car.SetGear(3);
	REQUIRE(car.GetGear() == Gear::ThirdGear);
}

SCENARIO("Switching speeds if we're going backwards in neutral gear")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetSpeed(20);
	car.SetGear(1);
	car.SetGear(2);
	car.SetGear(0);
	REQUIRE(car.GetGear() == Gear::NeutralGear);
	car.SetSpeed(19);
	REQUIRE(car.GetSpeed() == 19);
}

SCENARIO("Neutral transmission check")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(20);
	car.SetGear(2);
	car.SetSpeed(50);
	car.SetGear(0);
	REQUIRE(car.GetGear() == Gear::NeutralGear);
	car.SetSpeed(60);
	REQUIRE(car.GetSpeed() == 50);
	car.SetSpeed(0);
	REQUIRE(car.GetSpeed() == 0);
}

SCENARIO("Checking the switching conditions on ReverseGear, NeutralGear, FirstGear")
{
	Car car;
	car.TurnOnEngine();
	REQUIRE(car.isTurnedOn());
	car.SetGear(1);
	REQUIRE(car.GetGear() == Gear::FirstGear);
	car.SetSpeed(10);
	REQUIRE(car.GetSpeed() == 10);
	car.SetGear(-1);
	REQUIRE(car.GetGear() == Gear::FirstGear);
	car.SetSpeed(0);
	REQUIRE(car.GetSpeed() == 0);
	car.SetGear(-1);
	REQUIRE(car.GetGear() == Gear::ReverseGear);
	car.SetSpeed(10);
	REQUIRE(car.GetSpeed() == 10);
	car.SetGear(1);
	REQUIRE(car.GetGear() == Gear::ReverseGear);
	car.SetGear(0);
	REQUIRE(car.GetGear() == Gear::NeutralGear);
	car.SetGear(1);
	REQUIRE(car.GetGear() == Gear::NeutralGear);
}

SCENARIO("Checking the gear shift with the engine off")
{
	Car car;
	car.SetGear(0);
	REQUIRE(car.GetGear() == Gear::NeutralGear);
	car.SetGear(4);
	REQUIRE(car.GetGear() == Gear::NeutralGear);
	car.SetSpeed(20);
	REQUIRE(car.GetSpeed() == 0);
}

SCENARIO("Checking for correct input of values")
{
	Car car;
	car.TurnOnEngine();
	car.SetSpeed(-5);
	REQUIRE(car.GetSpeed() == 0);
	car.SetGear(10);
	REQUIRE(car.GetGear() == Gear::NeutralGear);
}