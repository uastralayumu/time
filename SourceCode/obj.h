#pragma once
#include <DirectXMath.h>
class obj
{
public:
	void init();
	void update();
	void render();
	void atrihantei();
public:
	DirectX::XMFLOAT2 position = { 1500,930 };
	DirectX::XMFLOAT2 vector = { 0,0 };
	bool motu = false;
private:
	
	DirectX::XMFLOAT2 sita = { 24,96 };
	int left = 96;
	bool onGround;
	
};

