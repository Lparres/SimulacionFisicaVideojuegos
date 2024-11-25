#pragma once

class RenderItem;


class Axis3D
{
private:
	RenderItem* ballX;	// Pelota eje x
	RenderItem* ballY;	// Pelota eje y
	RenderItem* ballZ;	// Pelota eje z
	RenderItem* ballO;	// Pelota origen

public:
	Axis3D();
	~Axis3D();

	RenderItem* GetBallX() const { return ballX; };
	RenderItem* GetBallY() const { return ballY; };
	RenderItem* GetBallZ() const { return ballZ; };
	RenderItem* GetBallOrigin() const { return ballO; };

};

