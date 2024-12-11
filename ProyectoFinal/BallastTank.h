#pragma once
class BallastTank
{
public:
	BallastTank();
	BallastTank(float volume, float flowRate);

	void SwitchWaterGate();
	void SwitchAirGate();

	bool GetWaterGateOpen() { return waterGateOpen; }
	bool GetAirGateOpen() { return airGateOpen; }

	void UpdateWaterVolume(double t);

	float GetMass() const;
	int GetWaterPercentage() const;
private:

	bool waterGateOpen;
	bool airGateOpen;

	float actualWaterVolume;

	float volume;
	float flowRate;
};

