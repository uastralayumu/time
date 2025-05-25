#pragma once
#include "all.h"

class serect
{
public:
	void init();
	void update(int *serect_stage,int*game_state);
	void render();
	void deinit();
private:
	Sprite* stage_serect[2];
	Sprite* stage[20];
	Sprite* stage_serect_chapter_go;
	Sprite* stage_serect_chapter_back;
	Sprite* stage_serect_back;
	DirectX::XMFLOAT2 serectpos[5];
	DirectX::XMFLOAT2 serect_chapter_gopos;
	DirectX::XMFLOAT2 serect_chapter_backpos;
	DirectX::XMFLOAT2 stage_serect_backpos;
	bool serectnoue[5];
	bool serect_stage_music;
	int serect_chapter;

};