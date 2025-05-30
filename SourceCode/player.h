#pragma once

#include "all.h"
#include <memory>
#include <d3d11.h>
#include <string>
#include <DirectXMath.h>

class player
{
public:

	DirectX::XMFLOAT2 position = { 0.0f,0.0f };
	const DirectX::XMFLOAT2 size = { 1.0f,1.0f };
	float gravite = 0.4f;
	DirectX::XMFLOAT2 vector = { 0.0f,0.0f };
	bool onGround = FALSE;
	bool junp = FALSE;
	bool sayuu = TRUE;
	bool damege = false;
	int taikitimer = 0;
	int taikimovetimer = 0;
	int move = 0;
private:
	DirectX::XMFLOAT2 asi = { 16 , 96 };
	int timer = 0;
	int movetimer = 0;
	int jamptimer = 0;
	int jampmovetimer = 0;
	int damagetimer = 0;
	int damagemove = 0;
	bool damagemusic = false;
public:
	void init(int &serect_stege);
	void update(int& serect_stage,int &game_title);
	void render();
	void game_deinit();
	void suu(int &serect_stage);
};
