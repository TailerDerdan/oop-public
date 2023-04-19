#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Car/Car.h"

SCENARIO("Uniform shifting across all gears")
{
	Car car;
	REQUIRE(car.TurnOnEngine());
	REQUIRE(car.SetGear(1));
	REQUIRE(car.SetSpeed(20));
	REQUIRE(car.SetGear(1));
	REQUIRE(car.SetGear(2));
	REQUIRE(car.SetSpeed(50));
	REQUIRE(car.SetGear(3));
	REQUIRE(car.SetGear(4));
	REQUIRE(car.SetGear(5));
	REQUIRE(car.SetGear(0));
	REQUIRE(car.SetSpeed(10));
	REQUIRE(car.SetGear(-1));
	REQUIRE(car.SetSpeed(0));
	REQUIRE(car.SetGear(0));
	REQUIRE(car.TurnOffEngine());
}

SCENARIO("Gear shift check -1, 0, 1")
{
	Car car;
	REQUIRE(car.TurnOnEngine());
	REQUIRE(car.SetGear(1));
	REQUIRE(car.SetSpeed(10));
	REQUIRE(!car.SetGear(-1));
	REQUIRE(car.SetSpeed(0));
	REQUIRE(car.SetGear(-1));
	REQUIRE(car.SetSpeed(10));
	REQUIRE(!car.SetGear(1));
	REQUIRE(car.SetGear(0));
	REQUIRE(!car.SetGear(1));
}