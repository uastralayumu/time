#pragma once
#include <DirectXMath.h>

class obj
{
public:
	void init(int &serect_stage);
	void update();
	void render();
	void atrihantei();
	void game_deinit();
	void suu(int& serect_stage);
	
public:
	DirectX::XMFLOAT2 position[10] = {};
	DirectX::XMFLOAT2 vector[10] = {};
	bool motu[10] = {};
	int uekikosuu = 0;
private:
	DirectX::XMFLOAT2 sita = { 24,96 };
	int left = 96;
	bool onGround;
	

};

