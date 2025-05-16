#pragma once

#include "all.h"
#include <memory>
#include <d3d11.h>
#include <string>
#include <DirectXMath.h>
class player
{
public:

	DirectX::XMFLOAT2 position = { 1000.0f,930.0f };
	const DirectX::XMFLOAT2 size = { 1.0f,1.0f };
	float gravite = 0.4f;
	DirectX::XMFLOAT2 vector = { 0.0f,0.0f };
	bool onGround = FALSE;
	bool junp = FALSE;
	bool sayuu = TRUE;
private:
	DirectX::XMFLOAT2 asi = { 16 , 96 };
	int move = 0;
	int timer = 0;
	int movetimer = 0;
	int jamptimer = 0;
	int jampmovetimer = 0;
public:
	void init();
	void update();
	void render();

};
