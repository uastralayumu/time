#include"serect.h"
#include "sound.h"
extern ongaku o;

void serect::init()
{
	stage_serect[0] = sprite_load(L"./Data/Images/stage_select.png");
	stage_serect[1] = sprite_load(L"./Data/Images/stage_select_b.png");
	stage[0] = sprite_load(L"./Data/Images/1-1.png");
	stage[1] = sprite_load(L"./Data/Images/1-1_b.png");
	stage[2] = sprite_load(L"./Data/Images/1-2.png");
	stage[3] = sprite_load(L"./Data/Images/1-2_b.png");
	stage[4] = sprite_load(L"./Data/Images/1-3.png");
	stage[5] = sprite_load(L"./Data/Images/1-3_b.png");
	stage[6] = sprite_load(L"./Data/Images/1-4.png");
	stage[7] = sprite_load(L"./Data/Images/1-4_b.png");
	stage[8] = sprite_load(L"./Data/Images/1-5.png");
	stage[9] = sprite_load(L"./Data/Images/1-5_b.png");
	stage[10] = sprite_load(L"./Data/Images/1-6.png");
	stage[11] = sprite_load(L"./Data/Images/1-6_b.png");
	stage[12] = sprite_load(L"./Data/Images/1-7.png");
	stage[13] = sprite_load(L"./Data/Images/1-7_b.png");
	stage[14] = sprite_load(L"./Data/Images/1-8.png");
	stage[15] = sprite_load(L"./Data/Images/1-8_b.png");
	stage_serect_chapter_go[0] = sprite_load(L"./Data/Images/U_next_b.png");
	stage_serect_chapter_go[1] = sprite_load(L"./Data/Images/U_next_w2.png");
	stage_serect_chapter_back[0] = sprite_load(L"./Data/Images/U_next_b2.png");
	stage_serect_chapter_back[1] = sprite_load(L"./Data/Images/U_next_w.png");
	stage_serect_back[0] = sprite_load(L"./Data/Images/U_back_b.png");
	stage_serect_back[1] = sprite_load(L"./Data/Images/U_back_b2.png");
	stege_serect_gamen[0] = sprite_load(L"./Data/Images/1.png");
	stege_serect_gamen[1] = sprite_load(L"./Data/Images/2.png");
	stege_serect_gamen[2] = sprite_load(L"./Data/Images/3.png");
	stege_serect_gamen[3] = sprite_load(L"./Data/Images/4.png");
	stege_serect_gamen[4] = sprite_load(L"./Data/Images/5.png");
	stege_serect_gamen[5] = sprite_load(L"./Data/Images/6.png");
	stege_serect_gamen[6] = sprite_load(L"./Data/Images/7.png");
	stege_serect_gamen[7] = sprite_load(L"./Data/Images/8.png");
	muzui = sprite_load(L"./Data/Images/muzu.png");
	serectpos[0] = { 70,120 };
	serectpos[1] = { 395,590 };
	serectpos[2] = { 720,120 };
	serectpos[3] = { 1045,590 };
	serectpos[4] = { 1370,120 };
	serect_chapter_gopos = { 1700,900 };
	serect_chapter_backpos = { 100,900 };
	stage_serect_backpos = { 0,0 };
	
	for (int i = 0; i < 5; i++)
	{
		serectnoue[i] = false;
	}
	serect_chapter = 0;
	serect_stage_music = false;
	serect_back_hantei = false;
	serect_chapter_hantei = false;
}


void serect::update(int *serect_stage,int*game_state)
{
	int cx = getCursorPosX();
	int cy = getCursorPosY();
	
	if (cx > serectpos[0].x + 5 && cx < serectpos[0].x + 475 && cy > serectpos[0].y + 10 && cy < serectpos[0].y + 450)
	{
		if (!serect_stage_music)
		{
			o.music(2);
			serect_stage_music = true;
		}
		serectnoue[0] = true;
		if (TRG(0) & PAD_START)
		{
			o.music(3);
			if (serect_chapter == 0)
			{
				*serect_stage = 0;
				
			}
			else if (serect_chapter == 1)
			{
				*serect_stage = 5;
			}
			music::stop(16);
			*game_state = 5;
		}
	}
	else if (cx > serectpos[1].x + 5 && cx < serectpos[1].x + 475 && cy > serectpos[1].y + 10 && cy < serectpos[1].y + 450)
	{
		if (!serect_stage_music)
		{
			serect_stage_music = true;
			o.music(2);
		}
		serectnoue[1] = true;
		if (TRG(0) & PAD_START)
		{
			o.music(3);
			if (serect_chapter == 0)
			{
				*serect_stage = 1;
			}
			else if (serect_chapter == 1)
			{
				*serect_stage = 6;
			}
			music::stop(16);
			*game_state = 5;
		}
	}
	else if (cx > serectpos[2].x + 5 && cx < serectpos[2].x + 475 && cy > serectpos[2].y + 10 && cy < serectpos[2].y + 450)
	{
		if (!serect_stage_music)
		{
			serect_stage_music = true;
			o.music(2);
		}
		serectnoue[2] = true;
		if (TRG(0) & PAD_START)
		{
			o.music(3);
			if (serect_chapter == 0)
			{
				*serect_stage = 2;
			}
			else if (serect_chapter == 1)
			{
				*serect_stage = 7;
			}
			music::stop(16);
			*game_state = 5;
		}
	}
	else if (cx > serectpos[3].x + 5 && cx < serectpos[3].x + 475 && cy > serectpos[3].y + 10 && cy < serectpos[3].y + 450)
	{
		if (!serect_stage_music)
		{
			serect_stage_music = true;
			o.music(2);
		}
		serectnoue[3] = true;
		if (TRG(0) & PAD_START)
		{
			o.music(3);
			if (serect_chapter == 0)
			{
				*serect_stage = 3;
			}
			music::stop(16);
			*game_state = 5;
		}
	}
	else if (cx > serectpos[4].x + 5&& cx < serectpos[4].x + 475 && cy > serectpos[4].y + 10 && cy < serectpos[4].y + 450)
	{
		if (!serect_stage_music)o.music(2);
		serect_stage_music = true;
		serectnoue[4] = true;
		if (TRG(0) & PAD_START)
		{
			o.music(3);
			if (serect_chapter == 0)
			{
				*serect_stage = 4;
			}
			music::stop(16);
			*game_state = 5;
		}
	}
	else
	{
		serect_stage_music = false;
		serectnoue[0] = false;
		serectnoue[1] = false;
		serectnoue[2] = false;
		serectnoue[3] = false;
		serectnoue[4] = false;
	}
	
	if (cx > serect_chapter_gopos.x && cx < serect_chapter_gopos.x + 128 && cy > serect_chapter_gopos.y && cy < serect_chapter_gopos.y + 128 
		&& serect_chapter < 1)
	{
		
		if (!serect_chapter_hantei)
		{
			o.music(2);
			serect_chapter_hantei = true;
		}
		if (TRG(0) & PAD_START)
		{
			serect_chapter++;
		}
	}
	else if (cx > serect_chapter_backpos.x && cx < serect_chapter_backpos.x + 128 && cy > serect_chapter_backpos.y && cy < serect_chapter_backpos.y + 128
		&& serect_chapter != 0)
	{
		if (!serect_chapter_hantei)
		{
			o.music(2);
			serect_chapter_hantei = true;
		}
		if (TRG(0) & PAD_START)
		{
			serect_chapter--;
		}
	}
	else
	{
		serect_chapter_hantei = false;
	}
	if (cx > stage_serect_backpos.x && cx < stage_serect_backpos.x + 128 && cy > stage_serect_backpos.y && cy < stage_serect_backpos.y + 128)
	{
		if (!serect_back_hantei) o.music(2);
		serect_back_hantei = true;
		if (TRG(0) & PAD_START)
		{
			o.music(3);
			*game_state = 0;
		}
	}
	else serect_back_hantei = false;
}

void serect::render()
{
	
	switch (serect_chapter)
	{
	case 0:
		sprite_render(stage_serect[0], 0, 0);
		if (!serectnoue[0]) sprite_render(stage[0], serectpos[0].x, serectpos[0].y);
		else sprite_render(stage[1], serectpos[0].x, serectpos[0].y);
		if (!serectnoue[1])	sprite_render(stage[2], serectpos[1].x, serectpos[1].y);
		else sprite_render(stage[3], serectpos[1].x, serectpos[1].y);
		if (!serectnoue[2]) sprite_render(stage[4], serectpos[2].x, serectpos[2].y);
		else sprite_render(stage[5], serectpos[2].x, serectpos[2].y);
		if (!serectnoue[3]) sprite_render(stage[6], serectpos[3].x, serectpos[3].y);
		else sprite_render(stage[7], serectpos[3].x, serectpos[3].y);
		if (!serectnoue[4]) sprite_render(stage[8], serectpos[4].x, serectpos[4].y);
		else sprite_render(stage[9], serectpos[4].x, serectpos[4].y);
		sprite_render(stege_serect_gamen[0], serectpos[0].x + 25, serectpos[0].y + 120);
		sprite_render(stege_serect_gamen[1], serectpos[1].x + 25, serectpos[1].y + 120);
		sprite_render(stege_serect_gamen[2], serectpos[2].x + 25, serectpos[2].y + 120);
		sprite_render(stege_serect_gamen[3], serectpos[3].x + 25, serectpos[3].y + 120);
		sprite_render(stege_serect_gamen[4], serectpos[4].x + 25, serectpos[4].y + 120);
		sprite_render(muzui, serectpos[4].x + 0, serectpos[4].y + 10);
		
		break;
	case 1:
		sprite_render(stage_serect[1], 0, 0);
		if (!serectnoue[0]) sprite_render(stage[10], serectpos[0].x, serectpos[0].y);
		else sprite_render(stage[11], serectpos[0].x, serectpos[0].y);
		if (!serectnoue[1])	sprite_render(stage[12], serectpos[1].x, serectpos[1].y);
		else sprite_render(stage[13], serectpos[1].x, serectpos[1].y);
		if (!serectnoue[2]) sprite_render(stage[14], serectpos[2].x, serectpos[2].y);
		else sprite_render(stage[15], serectpos[2].x, serectpos[2].y);
		sprite_render(stege_serect_gamen[5], serectpos[0].x + 25, serectpos[0].y + 120);
		sprite_render(stege_serect_gamen[6], serectpos[1].x + 25, serectpos[1].y + 120);
		sprite_render(stege_serect_gamen[7], serectpos[2].x + 25, serectpos[2].y + 120);
		sprite_render(muzui, serectpos[0].x + 0, serectpos[0].y + 10);
		sprite_render(muzui, serectpos[2].x + 0, serectpos[2].y + 10);
		break;
	}
	if (serect_chapter < 1)
	{
		if (!serect_chapter_hantei)
		{
			sprite_render(stage_serect_chapter_go[0],
				serect_chapter_gopos.x, serect_chapter_gopos.y,
				2, 2);
		}
		else
		{
			sprite_render(stage_serect_chapter_go[1],
				serect_chapter_gopos.x, serect_chapter_gopos.y,
				2, 2);
		}
	}
	if (serect_chapter != 0)
	{
		if (!serect_chapter_hantei)
		{
			sprite_render(stage_serect_chapter_back[0],
				serect_chapter_backpos.x, serect_chapter_backpos.y,
				2, 2);
		}
		else
		{
			sprite_render(stage_serect_chapter_back[1],
				serect_chapter_backpos.x, serect_chapter_backpos.y,
				2, 2);
		}
	}
	if(!serect_back_hantei)
	sprite_render(stage_serect_back[0],
		stage_serect_backpos.x, stage_serect_backpos.y,
		2, 2);
	else sprite_render(stage_serect_back[1],
			stage_serect_backpos.x, stage_serect_backpos.y,
			2, 2);
}

void serect::deinit()
{
	for(int i = 0;i < 2 ; i++)safe_delete(stage_serect[i]);
	for (int j = 0; j < 9; j++)safe_delete(stage[j]);
}