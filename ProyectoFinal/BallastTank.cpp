#include "BallastTank.h"
#include <iostream>

BallastTank::BallastTank() :
	volume(0),
	flowRate(0)
{
}

BallastTank::BallastTank(float volume, float flowRate) :
	volume(volume),
	flowRate(flowRate),
	waterGateOpen(false),
	airGateOpen(false),
	actualWaterVolume(0)
{
}

void BallastTank::SwitchWaterGate()
{
	waterGateOpen = !waterGateOpen;
}

void BallastTank::SwitchAirGate()
{
	airGateOpen = !airGateOpen;
}

void BallastTank::UpdateWaterVolume(double t)
{
	if (waterGateOpen && actualWaterVolume < volume) {
		actualWaterVolume += flowRate * t;
		std::cout << actualWaterVolume << std::endl;
	}
	if (airGateOpen && actualWaterVolume > 0) {
		actualWaterVolume -= flowRate * t;
	}

	if (actualWaterVolume > volume) {
		actualWaterVolume = volume;
	}
	if (actualWaterVolume < 0) {
		actualWaterVolume = 0;
	}
}

float BallastTank::GetMass() const
{
	return actualWaterVolume;	// Suponemos que 1L = 1Kg
}

int BallastTank::GetWaterPercentage() const
{
	return actualWaterVolume / volume * 100;
}
