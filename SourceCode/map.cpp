#include "map.h"
#include "obj.h"
#include "sound.h"
 
extern player play;
extern obj objs;
extern ongaku o;


Sprite* asa;
Sprite* yoru;
Sprite* tuti;
Sprite* botan;
Sprite* paneru;
Sprite* sanpu[4];
Sprite* gorl;
Sprite* gorlgo;
Sprite* saboten;
Sprite* home[2];

void maps::init(int &serect_stege)
{
	asa = sprite_load(L"./Data/Images/H_asa.png");
	yoru = sprite_load(L"./Data/Images/H_yoru.png");
	botan = sprite_load(L"./Data/Images/U_kanbanUI.png");
	tuti = sprite_load(L"./Data/Images/tuti_kari.png");
	paneru = sprite_load(L"./Data/Images/jyuudenn_kari.png");
	sanpu[0] = sprite_load(L"./Data/Images/U_sanpu4.png");
	sanpu[1] = sprite_load(L"./Data/Images/U_sanpu3.png");
	sanpu[2] = sprite_load(L"./Data/Images/U_sanpu2.png");
	sanpu[3] = sprite_load(L"./Data/Images/U_sanpu1.png");
	gorl = sprite_load(L"./Data/Images/G_Gole.png");
	gorlgo = sprite_load(L"./Data/Images/nextUI_kari.png");
	saboten = sprite_load(L"./Data/Images/saboten.png");
	home[0] = sprite_load(L"./Data/Images/U_home.png");
	home[1] = sprite_load(L"./Data/Images/U_home_b.png");
	o.music(14);
	o.music(15);
	
	{

		for (int i = 0; i < chip_y; i++)
		{
			for (int j = 0; j < chip_x; j++)
			{
				tikei[i][j] = toti[i][j];
			}
		}
		botanpos = { 10.0f,10.0f };
		sabotenpos = { 18,14 };
		panerupos = { 5,14 };
		gorlpos = { 25,14 };
		homepos = { 29,0 };
		music::pause(15);
	}
	kirikae = true;
	kaihukukirikae = FALSE;
	kaihuku = 0;
	kaihukutaimer = 0;
	gorlhantei = FALSE;
	homemove = false;
	gorl_music = false;
	

	
}



bool maps::isfloor(float x,float y,float width)
{
	for (; width > 0; width -= 32)
	{
		const float left = x - width;
		const float right = x + width;

		if (left < 0) continue;
		if (right >= chip_x * 32) continue;
		
		if (ishitdown(left + 5, y)) return true;
		if (ishitdown(right - 5, y)) return true;
	}
	return ishitdown(x, y);
}

bool maps::isceiling(float x, float y, float width)
{
	for (; width > 0; width -= 32)
	{
		const float left = x - width;
		const float right = x + width;

		if (left < 240) continue;
		if (right >= chip_x * 32) continue;
		if (ishitall(left, y)) 
			return true;
		if (ishitall(right, y)) 
			return true;
	}
	return ishitall(x, y);
}

bool maps::iswall(float x, float y, float height)
{
	for (; height > 0; height -= 32)
	{
		const float yPos = y - height;
		if (yPos < 0)      continue;
		if (yPos > chip_y * 32) continue;

		if (ishitall(x, yPos))
			return true;
		if (ishitall(x, yPos + 32))
			return true;
		if (ishitall(x, yPos + 64))
			return true;
	}

	return ishitall(x, y);
}

int maps::getdata(char mapchip[][chip_x], const DirectX::XMFLOAT2& pos)
{
	int divx = static_cast<int>(pos.x) / 32;
	int divy = static_cast<int>(pos.y) / 32;

	if (divx < 0 || divx >= chip_x ||
		divy < 0 || divy >= chip_y)
		return -1;

	return mapchip[divy][divx];
}

bool maps::ishitdown(float x, float y)
{
	DirectX::XMFLOAT2 pos = { x, y };
	switch (getTerrainAttr(pos))
	{
	case tr_attr::ALL_BLOCK: return true;
	}
	return false;

}

bool maps::ishitall(float x, float y)
{
	DirectX::XMFLOAT2 pos = { x, y };
	return(getTerrainAttr(pos)) == ALL_BLOCK;
}

maps::tr_attr maps::getTerrainAttr(const DirectX::XMFLOAT2& pos)
{
	int index = getdata(tikei, pos);
	if (index < 0)return TR_NONE;
	assert(index < CHIP_NUM_PER_LINE* CHIP_LINE_NUM);
	return tikeiattr[index];
}

void maps::playmaphosedown()
{
	float y = play.position.y;
	int inty = static_cast<int>(y);
	y = static_cast<float>(inty - inty % 32);
	play.position.y = y + 5.01f;
	play.vector.y = (std::min)(play.vector.y, 0.0f);
}

void maps::playmaphoseup()
{
	float y = play.position.y;
	y += 32 - fmodf(y, 32);
	play.position.y = y - 8;
	play.vector.y = (std::max)(play.vector.y, 0.0f);
}

void maps::playmaphoseright()
{
	float x = play.position.x;
	x -= fmodf(x, 32);
	play.position.x = x - 0.025f;
	play.vector.x = 0.0f;
}

void maps::playmaphoseleft()
{
	float x = play.position.x;
	x -= fmodf(x, 32);
	play.position.x = x + 32 + 0.025f;
	play.vector.x = 0.0f;
}

void maps::objmaphosedown()
{
	float y = objs.position.y;
	int inty = static_cast<int>(y);
	y = static_cast<float>(inty - inty % 32);
	objs.position.y = y - 0.01f;
	objs.vector.y = (std::min)(objs.vector.y, 0.0f);
}

void maps::objmaphoseup()
{
	float y = objs.position.y;
	y += 32 - fmodf(y, 32);
	objs.position.y = y - 8;
	objs.vector.y = (std::max)(objs.vector.y, 0.0f);
}

void maps::objmaphoseright()
{
	float x = objs.position.x;
	x -= fmodf(x, 32);
	objs.position.x = x - 0.025f;
	objs.vector.x = 0.0f;
}

void maps::objmaphoseleft()
{
	float x = objs.position.x;
	x -= fmodf(x, 32);
	objs.position.x = x + 32 + 0.025f;
	objs.vector.x = 0.0f;
}

bool maps::state()
{
	if (play.position.x + 56 > sabotenpos.x * 64 && play.position.x < sabotenpos.x * 64 + 56 &&
		play.position.y  < sabotenpos.y * 64 + 96 && play.position.y + 64 > sabotenpos.y * 64)
	{
		
		return true;
	}
	
	return false;
}

void maps::syuuryou()
{
	if (play.position.x + 48 > gorlpos.x * 64 && play.position.x < gorlpos.x * 64 + 64 &&
		play.position.y  < gorlpos.y * 64 + 96 && play.position.y > gorlpos.y * 64 + 28)
	{
		if(!gorl_music)o.music(9);
		gorl_music = true;
		gorlhantei = TRUE;
	}
	else
	{
		gorl_music = false;
	}
}

void maps::update()
{
	//朝と夜の切り替え
	{
		int getx = getCursorPosX();
		int gety = getCursorPosY();
		if (getx > botanpos.x + 125 && getx < botanpos.x + 365 && gety < botanpos.y + 215 && gety > botanpos.y + 120)
		{
			if (TRG(0) & PAD_START)
			{
				if (!kirikaemusic)
				{
					o.music(5);
				}
				kirikaemusic = true;
				if (kirikae)
				{
					kirikae = FALSE;
					music::pause(14);
					music::resume(15);
					
				}
				else
				{
					kirikae = TRUE;
					music::pause(15);
					music::resume(14);
				}
			}
			else kirikaemusic = false;
		}
		
	}

	//ソーラーパネルの当たり判定
	if (play.position.x + 48 > panerupos.x * 64 && play.position.x < panerupos.x * 64 + 40 &&
		play.position.y  < panerupos.y * 64 + 40 && play.position.y > panerupos.y * 64 + 28)
	{
			if (play.position.y > panerupos.y * 64 + 28 && play.position.y < panerupos.y * 64 + 40)
			{
				play.position.y = panerupos.y * 64 + 28;
				play.vector.y = 0;
				play.onGround = TRUE;
				if (!onemusic && kaihuku != 3)
				{
					o.music(6);
					onemusic = true;
					twomusic = false;
				}

				if (kirikae)
				{
					kaihukukirikae = TRUE;
					if (kaihukutaimer == 0)kaihuku++;
					if (kaihuku > 3)
					{
						kaihuku = 3;
						if (!twomusic)
						{
							o.music(7);
							twomusic = true;
						}
					}
					kaihukutaimer++;
				}
				else
				{
					kaihukukirikae = FALSE;
				}
			}
	}
	else
	{
		onemusic = false;
		
		kaihukukirikae = FALSE;
	}

	if (kaihukutaimer == 60) kaihukutaimer = 0;
	syuuryou();
	
}

void maps::re(int *screen_game)
{
	int getx = getCursorPosX();
	int gety = getCursorPosY();
	if (homepos.x * 64 - 16 <= getx && homepos.x * 64 + 48 >= getx && homepos.y * 64 + 10 <= gety && homepos.y * 64 + 74 >= gety)
	{
		if (!home_music) o.music(2);
		home_music = true;
		homemove = true;
		if (TRG(0) & PAD_START)
		{
			music::pause(14);
			music::pause(15);
			o.music(3);
			*screen_game = 1;
		}
	}
	else
	{
		home_music = false;
		homemove = false;
	}
}

void maps::render()
{
	if (kirikae)
	{
		sprite_render(asa,
			0, 0,
			1, 1,
			0, 0,
			1980, 1080,
			0, 0,
			0,
			1, 1, 1, 1);
	}
	else
	{
		sprite_render(yoru,
			0, 0,
			1, 1,
			0, 0,
			1980, 1080,
			0, 0,
			0,
			1, 1, 1, 1);
	}

	for (int i = 0; i < chip_x; i++)
	{
		for (int j = 0; j < chip_y; j++)
		{
			sprite_render(
				tuti,
				i * 32, j * 32,
				1,1,
				tikei[j][i] * 32, 0,
				32, 32, 0, 0
				);
		}
	}

	sprite_render(paneru,
		64 * panerupos.x, 64 * panerupos.y + 32);

	sprite_render(saboten,
		sabotenpos.x * 64, sabotenpos.y * 64 + 32);

	sprite_render(gorl,
		64 * gorlpos.x, 64 * gorlpos.y + 32);

	
	sprite_render(botan,
		botanpos.x, botanpos.y, 1, 1);

	if (!homemove)
	{
		sprite_render(home[0],
			homepos.x * 64 + 20 - 32, homepos.y * 32 + 10,
			2, 2);
	}
	else
	{
		sprite_render(home[1],
			homepos.x * 64 + 20 - 32, homepos.y * 32 + 10,
			2, 2);
	}

	if (kaihukukirikae)
	{
		switch (kaihuku)
		{
		case 0:
			sprite_render(sanpu[0],
				1500, 100, 1, 1);
			break;
		case 1:
			sprite_render(sanpu[1],
				1500, 100, 1, 1);
			break;
		case 2:
			sprite_render(sanpu[2],
				1500, 100, 1, 1);
			break;
		case 3:
			sprite_render(sanpu[3],
				1500, 100, 1, 1);
			break;
		}
	}

	if (gorlhantei)
	{
		sprite_render(gorlgo,
			900, 500);
	}
}



void maps::game_deinit()
{
	safe_delete(asa);
	safe_delete(yoru);
	safe_delete(tuti);
	safe_delete(sanpu[0]);
	safe_delete(sanpu[1]);
	safe_delete(sanpu[2]);
	safe_delete(sanpu[3]);
	safe_delete(gorlgo);
}