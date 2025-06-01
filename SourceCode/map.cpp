#include "map.h"
#include "obj.h"
#include "sound.h"

extern player play;
extern obj objs;
extern ongaku o;
// デバッグ用でサボテン用のアニメーションを定義
Animation saboten_animation;

//// ── 外部シンボル
constexpr float SANPU_W = 64.0f;
constexpr float SANPU_H = 64.0f;
constexpr float PLANT_W = 78.0f;
constexpr float PLANT_H = 64.0f;
constexpr float KUKI_W = 32.0f;
constexpr float KUKI_H = 64.0f;
constexpr float UI_X = 1500.0f;     
constexpr float UI_Y = 100.0f;      
constexpr float UI_W = 340.0f;   // 画像サイズに合わせて調整
constexpr float UI_H = 192.0f;
int chara_anim = 0;          // アニメ制御用カウンタ




void maps::init(int &serect_stage,int &game_title)
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
	asayorukirikae[0] = sprite_load(L"./Data/Images/nextUI_kari.png");
	asayorukirikae[1] = sprite_load(L"./Data/Images/nextUI_kari_2.png");
	saboten = sprite_load(L"./Data/Images/G_saboten_kare2.png");
	home[0] = sprite_load(L"./Data/Images/U_home.png");
	home[1] = sprite_load(L"./Data/Images/U_home_b.png");
    plant = sprite_load(L"./Data/Images/plant_kari.png");
    g_kuki_sprite = sprite_load(L"./Data/Images/G_kuki.png");
    star[0] = sprite_load(L"./Data/Images/G_star.png");
    star[1] = sprite_load(L"./Data/Images/G_star_b.png");
	chara_jyosou = sprite_load(L"./Data/Images/chara_jyosou.png");
	chara_hiryou = sprite_load(L"./Data/Images/chara_hiryou.png");
	kuki = sprite_load(L"./Data/Images/G_kuki.png");
	gorlhubki = sprite_load(L"./Data/Images/G_kamihubuki.png");
	suuzi = sprite_load(L"./Data/Images/Number.png");
	reset[0] = sprite_load(L"./Data/Images/rsetUI_kari1.png");
	reset[1] = sprite_load(L"./Data/Images/rsetUI_kari2.png");
	switch (serect_stage)
	{
	case 0:
		stagesuuzi[serect_stage] = sprite_load(L"./Data/Images/UI_stage_1.png");
		break;
	case 1:
		stagesuuzi[serect_stage] = sprite_load(L"./Data/Images/UI_stage_2.png");
		break;
	case 2:
		stagesuuzi[serect_stage] = sprite_load(L"./Data/Images/UI_stage_3.png");
		break;
	case 3:
		stagesuuzi[serect_stage] = sprite_load(L"./Data/Images/UI_stage_4.png");
		break;
	case 4:
		stagesuuzi[serect_stage] = sprite_load(L"./Data/Images/UI_stage_5.png");
		break;
	case 5:
		stagesuuzi[serect_stage] = sprite_load(L"./Data/Images/UI_stage_6.png");
		break;
	case 6:
		stagesuuzi[serect_stage] = sprite_load(L"./Data/Images/UI_stage_7.png");
		break;
	case 7:
		stagesuuzi[serect_stage] = sprite_load(L"./Data/Images/UI_stage_8.png");
		break;
	case 8:
		stagesuuzi[serect_stage] = sprite_load(L"./Data/Images/UI_stage_9.png");
		break;
	case 9:
		stagesuuzi[serect_stage] = sprite_load(L"./Data/Images/UI_stage_10.png");
		break;
	}
	
	retrai[0] = sprite_load(L"./Data/Images/gameover_botton_1.png");
	retrai[1] = sprite_load(L"./Data/Images/gameover_botton_2.png");
	taitoru[0] = sprite_load(L"./Data/Images/gameover_botton_3.png");
	taitoru[1] = sprite_load(L"./Data/Images/gameover_botton_4.png");
	gameoverspr = sprite_load(L"./Data/Images/gameover.png");
	newstege[0] = sprite_load(L"./Data/Images/next_botton_1.png");
	newstege[1] = sprite_load(L"./Data/Images/next_botton_2.png");
	
	botanpos = { 10.0f,0.0f };
	homepos = { 29,0 };
	sanpulpos = { 1500,100 };
	o.music(14);
	o.music(15);
	if (game_title == 1)
	{
		timer = 0;
		kanban[0] = sprite_load(L"./Data/Images/UI_kanban1_1.png");
		kanban[1] = sprite_load(L"./Data/Images/UI_kanban1_2.png");
		kanban[2] = sprite_load(L"./Data/Images/UI_kanban1_3.png");
		kanban[3] = sprite_load(L"./Data/Images/UI_kanban1_4.png");
		kanban[4] = sprite_load(L"./Data/Images/UI_kanban1_5.png");
		kanban[5] = sprite_load(L"./Data/Images/UI_kanban1_6.png");
		kanban[6] = sprite_load(L"./Data/Images/UI_kanban1_7.png");
		kanban[7] = sprite_load(L"./Data/Images/UI_kanban1_8.png");
		kanban[8] = sprite_load(L"./Data/Images/UI_kanban1_9.png");
		kanban[9] = sprite_load(L"./Data/Images/UI_kanban1_10.png");
		kanban[10] = sprite_load(L"./Data/Images/UI_kanban1_11.png");
	}
	suu(serect_stage);
}

void maps::suu(int &serect_stage)
{
	switch (serect_stage)
	{
	case 0:
		// 可変領域を固定地形で初期化
		for (int i = 0; i < chip_y; i++)
		{
			for (int j = 0; j < chip_x; j++)
			{
				tikei[i][j] = toti[i][j];
			}
		}
		sabotenkosuu = 0;
		panerupos[0] = {24,28};
		panerukosuu = 1;
		gorlpos = { 55,7 };
		pulantpos[0] = {1630,920};
		pulantpos[1] = { objs.position[0].x,objs.position[0].y - 30};
		kirikaejougen = 5;
		kirikae = true;
		gorljouken[0] = 2;
		gorljouken[1] = 3;
		plantkosuu = 2;
		plantueki = 1;
		music::pause(15);
		break;
	case 1:
		for (int i = 0; i < chip_y; i++)
		{
			for (int j = 0; j < chip_x; j++)
			{
				tikei[i][j] = toti1[i][j];
			}
		}
		sabotenpos[0] = { 36,24 };
		panerupos[0] = {24,27};
		panerukosuu = 1;
		gorlpos = { 55,9 };
		pulantpos[0] = { 0,695 };
		pulantpos[1] = { objs.position[0].x,objs.position[0].y - 30 };
		plantkosuu = 2;
		plantueki = 1;
		kirikaejougen = 5;
		kirikae = true;
		gorljouken[0] = 2;
		gorljouken[1] = 3;
		sabotenkosuu = 1;
		music::pause(15);
		break;
	case 2:
		for (int i = 0; i < chip_y; i++)
		{
			for (int j = 0; j < chip_x; j++)
			{
				tikei[i][j] = toti2[i][j];
			}
		}
		sabotenpos[0] = { 32,56 };
		sabotenpos[1] = { 36,56 };
		sabotenpos[2] = { 36,50 };
		sabotenpos[3] = { 40,50 };
		sabotenpos[4] = { 40,44 };
		sabotenpos[5] = { 40,38 };
		sabotenpos[6] = { 40,32 };
		sabotenpos[7] = { 78,56 };
		sabotenkosuu = 8;
		panerupos[0] = { 0, 9};
		panerupos[1] = { 0, 28};
		panerukosuu = 2;
		gorlpos = { 52,15 };
		pulantpos[0] = { 1800,920 };
		pulantpos[1] = { objs.position[0].x,objs.position[0].y - 30 };
		plantkosuu = 2;
		plantueki = 1;
		kirikaejougen = 6;
		kirikae = true;
		gorljouken[0] = 2;
		gorljouken[1] = 3;
		
		music::pause(15);
		break;
	case 3:
		for (int i = 0; i < chip_y; i++)
		{
			for (int j = 0; j < chip_x; j++)
			{
				tikei[i][j] = toti3[i][j];
			}
		}
		sabotenpos[0] = { 48,22 };
		sabotenpos[1] = { 66,22 };
		sabotenkosuu = 2;
		panerupos[0] = { 6, 28 };
		panerukosuu = 1;
		gorlpos = { 28, -1 };
		pulantpos[0] = { 900,920 };
		pulantpos[1] = { objs.position[0].x,objs.position[0].y - 30 };
		pulantpos[2] = { objs.position[1].x,objs.position[1].y - 30 };
		plantkosuu = 3;
		plantueki = 2;
		kirikaejougen = 6;
		kirikae = true;
		gorljouken[0] = 2;
		gorljouken[1] = 3;

		music::pause(15);
		break;
	case 4:
		for (int i = 0; i < chip_y; i++)
		{
			for (int j = 0; j < chip_x; j++)
			{
				tikei[i][j] = toti7[i][j];
			}
		}
		sabotenpos[0] = { 0,26 };
		sabotenpos[1] = { 34,33 };
		sabotenpos[2] = { 64,32 };
		sabotenpos[3] = { 76,36 };
		sabotenpos[4] = { 82,20 };
		sabotenpos[5] = { 88,20 };
		sabotenpos[6] = { 88,26 };
		sabotenkosuu = 7;
		panerupos[0] = { 14, 19 };
		panerupos[1] = { 0, 28 };
		panerukosuu = 2;
		pulantpos[0] = { 540,475 };
		pulantpos[1] = { 940,930 };
		pulantpos[2] = { 735,535 };
		pulantpos[3] = { 1570,920 };
		pulantpos[4] = { objs.position[0].x,objs.position[0].y - 30 };
		plantkosuu = 5;
		plantueki = 1;
		for (int j = 0; j < plantkosuu; j++)
		{
			hiryousanpusuu[j] = 0;
			yorusanpu[j] = 0;
			for (int i = 0; i < 4; i++)
			{
				planthantei[i][j] = false;
			}
		}
		hiryousanpusuu[0] = 1;
		yorusanpu[0] = 1;
		hiryousanpusuu[1] = 1;
		yorusanpu[1] = 1;
		for (int i = 0; i < 2; i++)
		{
			planthantei[i][0] = true;
		}
		for (int i = 0; i < 2; i++)
		{
			planthantei[i][1] = true;
		}
		gorlpos = { 47,1, };
		kirikaejougen = 9;
		gorljouken[0] = 3;
		gorljouken[1] = 5;
		kirikae = true;
		
		break;
	case 5:
		for (int i = 0; i < chip_y; i++)
		{
			for (int j = 0; j < chip_x; j++)
			{
				tikei[i][j] = toti5[i][j];
			}
		}
		sabotenpos[0] = { 0,48 };
		sabotenpos[1] = { 30,56 };
		sabotenpos[2] = { 30,40 };
		sabotenpos[3] = { 30,34 };
		sabotenpos[4] = { 30,28 };
		sabotenpos[5] = { 30,22 };
		sabotenpos[6] = { 42,56 };
		sabotenpos[7] = { 42,50 };
		sabotenpos[8] = { 54,32 };
		sabotenpos[9] = { 54,26 };
		sabotenpos[10] = { 80,56 };
		sabotenpos[11] = { 114,56 };

		sabotenkosuu = 12;
		pulantpos[0] = { 580,920 };
		plantkosuu = 1;
		plantueki = 0;
		gorlpos = { 30,18 };
		panerupos[0] = { 0, 28 };
		panerupos[1] = { 50, 28 };
		panerukosuu = 2;
		kirikaejougen = 8;
		gorljouken[0] = 4;
		gorljouken[1] = 6;
		kirikae = true;
		break;
	case 6:
		for (int i = 0; i < chip_y; i++)
		{
			for (int j = 0; j < chip_x; j++)
			{
				tikei[i][j] = toti6[i][j];
			}
		}
		saboten = 0;
		pulantpos[0] = { objs.position[0].x,objs.position[0].y - 30 };
		pulantpos[1] = { objs.position[1].x,objs.position[1].y - 30 };
		plantkosuu = 2;
		plantueki = 2;
		pulantpos[0] = { 580,920 };
		pulantpos[1] = { 580,920 };
		plantkosuu = 2;
		panerupos[0] = { 13, 17 };
		panerupos[1] = { 45, 17 };
		panerukosuu = 2;
		gorlpos = { 29,6 };
		kirikaejougen = 8;
		gorljouken[0] = 2;
		gorljouken[1] = 4;
		kirikae = true;
		break;
	case 7:
		for (int i = 0; i < chip_y; i++)
		{
			for (int j = 0; j < chip_x; j++)
			{
				tikei[i][j] = toti4[i][j];
			}
		}
		sabotenpos[0] = { 104,38 };
		sabotenpos[1] = { 78,32 };
		sabotenpos[2] = { 54,32 };
		sabotenpos[3] = { 104,0 };
		sabotenkosuu = 4;
		pulantpos[0] = { 790,920 };
		pulantpos[1] = { 1220,450 };
		pulantpos[2] = { 780,80 };
		pulantpos[3] = { 0,920 };
		pulantpos[4] = { 1850,640 };
		pulantpos[5] = { objs.position[0].x,objs.position[0].y - 30 };
		pulantpos[6] = { objs.position[1].x,objs.position[1].y - 30 };
		plantkosuu = 7;
		plantueki = 2;
		for (int j = 0; j < plantkosuu; j++)
		{
			hiryousanpusuu[j] = 0;
			yorusanpu[j] = 0;
			for (int i = 0; i < 4; i++)
			{
				planthantei[i][j] = false;
			}
		}

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				planthantei[j][i] = true;
			}
			hiryousanpusuu[i] = 1;
			yorusanpu[i] = 1;
		}
		panerupos[0] = { 41, 22 };
		panerupos[1] = { 22, 20 };
		panerupos[2] = { 54, 7 };
		panerukosuu = 3;
		gorlpos = { 13,3 };
		kirikaejougen = 9;
		gorljouken[0] = 1;
		gorljouken[1] = 3;
		kirikae = true;
		break;
	};
	taitoruhe = false;
	restart = false;
	timer = 0;
	kaihuku = 0;
	kaihukutaimer = 0;
	gorlhantei = FALSE;
	homemove = false;
	gorl_music = false;
	hiyoorjousou = false;
	hiyoudasu = false;
	for (int i = 0; i < sabotenkosuu; i++)
	{
		sabotenhantei[i] = false;
		sabotensakujo[i] = false;
		josousaboten[i] = false;
		sabotenjosou[i] = false;
	}
	saboten_animation.suu();
	
	for (int i = 0; i < panerukosuu; i++)
	{
		kaihukukirikae[i] = FALSE;
	}
	
	gameover = false;
	timercrek = false;
	timerhiryou = false;
	if (serect_stage != 7 && serect_stage !=  4)
	{
		for (int j = 0; j < plantkosuu; j++)
		{
			hiryousanpusuu[j] = 0;
			yorusanpu[j] = 0;
			for (int i = 0; i < 4; i++)
			{
				planthantei[i][j] = false;
			}
		}
	}
	for (int i = 0; i < plantkosuu; i++)
	{
		hiryousanpuhantei[i] = false;
	}

	yoruhiyou = 0;
	gorltimer = 0;
	kirikaekaisuu = 0;
	timerpoint = 0;
	
}

bool maps::isfloor(float x, float y, float width)
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
	assert(index < CHIP_NUM_PER_LINE * CHIP_LINE_NUM);
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

void maps::objmaphosedown(int o)
{
	float y = objs.position[o].y;
	int inty = static_cast<int>(y);
	y = static_cast<float>(inty - inty % 32);
	objs.position[o].y = y - 0.01f;
	objs.vector[o].y = (std::min)(objs.vector[o].y, 0.0f);
}

void maps::objmaphoseup(int o)
{
	float y = objs.position[o].y;
	y += 32 - fmodf(y, 32);
	objs.position[o].y = y - 8;
	objs.vector[o].y = (std::max)(objs.vector[o].y, 0.0f);
}


bool maps::state()
{
	for (int i = 0; i < sabotenkosuu; i++)
	{
		if (play.position.x + 56 > sabotenpos[i].x * 16 && play.position.x < sabotenpos[i].x * 16 + 56 &&
			play.position.y  < sabotenpos[i].y * 16 + 96 && play.position.y + 64 > sabotenpos[i].y * 16 && !sabotenjosou[i])
		{
			asayorudamege = true;
			return true;
		}
	}
	return false;

}

void maps::syuuryou(int* game_state,int * screen_game,int & screen_game_b,int& game_title)
{
	if (play.position.x + 48 > gorlpos.x * 32 && play.position.x < gorlpos.x * 32 + 32 &&
		play.position.y  < gorlpos.y * 32 + 96 && play.position.y > gorlpos.y * 32 + 28)
	{
		int getx = getCursorPosX();
		int gety = getCursorPosY();
		newstegepos = { 690,500 };
		taitorupos = { 670,300 };
		play.move = 0;
		game_title = 0;
		if(!gorl_music)o.music(9);
		gorl_music = true;
		gorlhantei = TRUE;
		for (int o = 0; o < objs.uekikosuu; o++)
		{
			objs.motu[o] = false;
		}
		if (gorlhantei)
		{
			play.taikitimer++;
			if (play.taikitimer > 35)
			{
				play.taikimovetimer++;
				play.taikitimer = 0;
				if (play.taikimovetimer > 5) play.taikimovetimer = 0;
			};
			gorltimer++;
		}
		if (getx > taitorupos.x + 140 && getx < taitorupos.x + 420 && gety > taitorupos.y + 25 && gety < taitorupos.y + 95)
		{
			
			if (!taitoruhantei)
			{
				o.music(2);
				taitoruhantei = true;
			}
		}
		if (getx > taitorupos.x + 30 && getx < taitorupos.x + 530 && gety > taitorupos.y - 5 && gety < taitorupos.y + 110
			&& taitoruhantei)
		{
			if (TRG(0) & PAD_START)
			{
				o.music(3);
				*game_state = 1;
			}
		}
		else
		{
			taitoruhantei = false;
		}
		if (screen_game_b < 9)
		{
			if (getx > newstegepos.x + 120 && getx < newstegepos.x + 400 && gety > newstegepos.y + 90 && gety < newstegepos.y + 355
				&& screen_game_b < 9)
			{
				
				if (!newstagehantei)
				{
					o.music(2);
					newstagehantei = true;
				}
				if (TRG(0) & PAD_START)
				{
					o.music(3);
					*screen_game = screen_game_b + 1;
					*game_state = 5;
				}
			}
			else
			{
				newstagehantei = false;
			}
		}
	}
	else
	{
		gorl_music = false;
	}
	
}

//
///*====================================================================
//    ユーティリティ：簡易矩形
// ====================================================================*/
struct Rect { float x, y, w, h; };
static bool hit(const Rect& a, const Rect& b)
{
    return !(a.x + a.w < b.x || b.x + b.w < a.x ||
        a.y + a.h < b.y || b.y + b.h < a.y);
}

 /*====================================================================
     sanpu UI 左右クリック処理
  ====================================================================*/
void maps::handleSanpuClick(int i)
{
	if (hiyoudasu)
	{
		if (hiyoutimer < 60)return;
	}
	
	if (kaihuku == 0) return;

	// マウス座標を float にキャスト
	float mx = static_cast<float>(getCursorPosX());
	float my = static_cast<float>(getCursorPosY());

	{
		//sanpuの左をクリックするとplantに肥料が散布されてる時charahiryouが動く
		
			if (mx > sanpulpos.x && mx < sanpulpos.x + 140 && my > sanpulpos.y + 30 && my < sanpulpos.y + 180 && TRG(0) & PAD_START)
			{
				kaihuku--;
				hiyoorjousou = false;
				hiyoudasu = true;
				o.music(10);
				hiryousanpusuu[i]++;
				hiryousanpuhantei[i] = false;
				hiryousanpujosouhantei[i] = true;
				timerhiryou = true;
			}


			//sanpuを左クリックするとplantに除草剤が散布されてる時chara_jyosouが動く
			else if (mx > sanpulpos.x + 170 && mx < sanpulpos.x + 340 && my > sanpulpos.y + 30 && my < sanpulpos.y + 180 && TRG(0) & PAD_START)
			{
				kaihuku--;
				hiyoorjousou = true;
				hiyoudasu = true;
				o.music(10);
				hiryousanpusuu[i]--;
				hiryousanpuhantei[i] = true;
				hiryousanpujosouhantei[i] = false;
			}
		
	}
}

void maps::update(int& serect_stage, int& game_title)
{

	//朝と夜の切り替え
	{
		int getx = getCursorPosX();
		int gety = getCursorPosY();
		if (getx > botanpos.x + 315 && getx < botanpos.x + 350 && gety < botanpos.y + 195 && gety > botanpos.y + 150
			|| asayorudamege)
		{
			if (!asayorukirkaeiro&& !asayorudamege)
			{
				o.music(2);
				asayorukirkaeiro = true;
			}
			if (TRG(0) & PAD_START || asayorudamege)
			{
				timercrek = true;
				kirikaekaisuu++;
				if (!kirikaemusic)
				{
					o.music(5);
					yoruhiyou = 0;
				}
				kirikaemusic = true;
				for (int i = 0; i < sabotenkosuu; i++)
				{
					if (josousaboten[i])
					{
						o.music(12);
						sabotenjosou[i] = true;
						sabotensakujo[i] = true;
					}
				}
				
					for (int i = 0; i < plantkosuu; i++)
					{
						if (hiryousanpusuu[i] > 3)
						{
							hiryousanpusuu[i] = 3;
						}
						if (hiryousanpuhantei[i] == true)
						{
							o.music(12);
						}
						else if (hiryousanpujosouhantei[i] == true)
						{
							o.music(11);
						}
						yorusanpu[i] = hiryousanpusuu[i];
					}
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
		else
		{
			asayorukirkaeiro = false;
		}

		if (getx > botanpos.x + 30 && getx < botanpos.x + 126 && gety < botanpos.y + 215 && gety > botanpos.y + 135)
		{
			if (!resethantei)
			{
				o.music(2);
				resethantei = true;
			}
			if (TRG(0) & PAD_START)
			{
				o.music(3);
				play.suu(serect_stage);
				suu(serect_stage);
				objs.suu(serect_stage);
			}
		}
		else
		{
			resethantei = false;
		}
	}

	for (int j = 0; j < plantkosuu; j++)
	{
		for (int i = 0; i < yorusanpu[j] + 1; i++)
		{
			if (play.position.x + 48 > pulantpos[j].x && play.position.x < pulantpos[j].x + 48
				&& play.position.y >(pulantpos[j].y - 32) - plant_growth * i && play.position.y < (pulantpos[j].y - 20) - plant_growth * i
				&& play.vector.y > 0)
			{
				play.onGround = TRUE;
				play.position.y = (pulantpos[j].y - 32) - plant_growth * i;
				play.vector.y = 0;
			}
		}
	}
	for (int i = plantkosuu - plantueki; i < plantkosuu; i++)
	{
		
		{

			pulantpos[i].x = objs.position[i - (plantkosuu - plantueki)].x;
			pulantpos[i].y = objs.position[i - (plantkosuu - plantueki)].y - 30;
			if (i == 2)
			{
				int a = 0;
			}
		}
	}

	//ソーラーパネルの当たり判定
	for (int i = 0; i < panerukosuu; i++)
	{
		if (play.position.x + 48 > panerupos[i].x * 32 && play.position.x < panerupos[i].x * 32 + 40 &&
			play.position.y  < panerupos[i].y * 32 + 40 && play.position.y > panerupos[i].y * 32 + 28)
		{
			if (play.position.y > panerupos[i].y * 32 + 28 && play.position.y < panerupos[i].y * 64 + 40)
			{
				play.position.y = panerupos[i].y * 32 + 28;
				play.vector.y = 0;
				play.onGround = TRUE;
				if (kirikae)
				{
					if (yoruhiyou < 3)
					{

						if (!onemusic[i] && kaihuku != 3)
						{
							o.music(6);
							onemusic[i] = true;
							twomusic = false;
						}
						kaihukukirikae[i] = TRUE;
						if (kaihukutaimer == 0)
						{
							kaihuku++;
							yoruhiyou++;
						}
						if (kaihuku > 2)
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
				}
				else
				{
					kaihukukirikae[i] = FALSE;
				}
			}
		}
		else
		{
			onemusic[i] = false;

			kaihukukirikae[i] = FALSE;
		}
	}

	if (hiyoudasu)
	{
		hiyoutimer++;
		if (hiyoutimer > 60)
		{
			hiyoutimer = 0;
			hiyoudasu = false;
		}
	}

	/* ---------- 既存 UI ボタン処理 ---------- */
	int cx = getCursorPosX();
	int cy = getCursorPosY();

	/* ---------- sanpu UI & plant 処理 ---------- */
	for (int j = 0; j < plantkosuu; j++)
	{
		for (int i = 0; i < yorusanpu[j] + 1; i++)
		{
			if (planthantei[i][j])
			{
				handleSanpuClick(j);
			}
		}
	}

	/* ---------- plant 付近で sanpu 表示 ---------- */
	{
		Rect playRect{ play.position.x + 24.0f,
						 play.position.y - 32.0f,
						 32.0f, 64.0f };

		Rect plantRect[4][10];
		for (int j = 0; j < plantkosuu; j++)
		{
			for (int i = 0; i < yorusanpu[j] + 1; i++)
			{

				plantRect[i][j] = {
					pulantpos[j].x,
					pulantpos[j].y - (plantStage * 32.0f) - plant_growth * i,
					PLANT_W,
					PLANT_H
				};
				planthantei[i][j] = hit(playRect, plantRect[i][j]);
			}

			for (int i = 0; i < 4; i++)
			{
				if (yorusanpu[j] < i)
				{
					planthantei[i][j] = false;
				}
			}
		}
	}
	
	for (int i = 0; i < sabotenkosuu; i++)
	{
		if (play.position.x + 80 > sabotenpos[i].x * 16 && play.position.x < sabotenpos[i].x * 16 + 80 &&
			play.position.y  < sabotenpos[i].y * 16 + 96 && play.position.y + 64 > sabotenpos[i].y * 16&&
			!sabotenjosou[i])
		{
			sabotenhantei[i] = true;

			if (kaihuku > 0)
			{
				if (cx > sanpulpos.x + 170 && cx < sanpulpos.x + 340 && cy > sanpulpos.y + 30 && cy < sanpulpos.y + 180 && TRG(0) & PAD_START)
				{
					o.music(10);
					josousaboten[i] = true;
					kaihuku--;
					hiyoorjousou = true;
					hiyoudasu = true;
				}
			}
		}
		else
		{
			sabotenhantei[i] = false;
		}

		if (sabotenjosou[i])
		{
			saboten_animation.update(i);
		}
	}

	
	
	if (kaihukutaimer == 60) kaihukutaimer = 0;
}





void maps::re(int *screen_game,int &serect_state)
{
	int getx = getCursorPosX();
	int gety = getCursorPosY();
	if (homepos.x * 64 - 16 <= getx && homepos.x * 64 + 48 >= getx && homepos.y * 64 + 10 <= gety && homepos.y * 64 + 74 >= gety
		&& !gameover)
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

	if (kirikaejougen == kirikaekaisuu)
	{
		retraipos = { 670,500 };
		taitorupos = { 670,700 };
		gameover = true;
		if (getx > taitorupos.x + 150 && getx < taitorupos.x + 400 && gety > taitorupos.y + 20 && gety < taitorupos.y + 80)
		{
			if(!taitoruhantei)o.music(2);
			taitoruhantei = true;
		}
		if (getx > taitorupos.x + 30 && getx < taitorupos.x + 530 && gety > taitorupos.y - 5 && gety < taitorupos.y + 110
			&& taitoruhantei)
		{
			if (TRG(0) & PAD_START)
			{
				o.music(3);
				*screen_game = 1;
				taitoruhantei = false;
			}
		}
		else
		{
			taitoruhantei = false;
		}
		if (getx > retraipos.x + 185 && getx < retraipos.x + 370 && gety > retraipos.y + 20 && gety < retraipos.y + 80)
		{
			if (!restarthatei)o.music(2);
			restarthatei = true;
		}
		if (getx > retraipos.x + 85 && getx < retraipos.x + 480 && gety > retraipos.y - 5 && gety < retraipos.y + 110
			&& restarthatei == true)
		{
			
			if (TRG(0) & PAD_START)
			{
				o.music(3);
				play.suu(serect_state);
				suu(serect_state);
				objs.suu(serect_state);
				restarthatei = false;
			}
		}
		else
		{
			restarthatei = false;
		}

	}
}

void Animation::render()
{
	
}

void maps::render(int &serect_stage,int &game_title)
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

	for (int i = 0; i < panerukosuu; i++)
	{
		sprite_render(paneru,
			32 * panerupos[i].x,
			32 * panerupos[i].y + 32);
	}

	/*texture::begin(saboten)*/
	for (int i = 0; i < sabotenkosuu; i++)
	{
		/*sprite_render(saboten,
				sabotenpos[i].x * 32, sabotenpos[i].y * 32 + 32);*/
				// アニメーションが終了していたら描画を行わない

		if (saboten_animation.animation_playing(i) == true) {
			sprite_render(saboten,
				sabotenpos[i].x * 16,        // 位置 x 
				sabotenpos[i].y * 16 + 32,    // 位置 y
				1.0f, 1.0f,
				saboten_animation.get_animation_frame_no(i) * 96,    // テクスチャの切り取り位置 X 
				0,    // テクスチャの切り取り位置 Y
				96,    // テクスチャの切り取り幅
				96    // テクスチュの切り取り高さ
			);


		}
	}


	sprite_render(gorl,
		32 * gorlpos.x, 32 * gorlpos.y + 32);


	sprite_render(botan,
		botanpos.x, botanpos.y, 1.0f, 1);
	if (!resethantei)
	{
		sprite_render(reset[0],
			40,130);
	}
	else
	{
		sprite_render(reset[1],
			40, 130);
	}


	if (!asayorukirkaeiro)
	{
		sprite_render(asayorukirikae[0],
			325, 144,
			0.5f, 0.6f);
	}
	else
	{
		sprite_render(asayorukirikae[1],
			325, 144,
			0.5f, 0.6f);
	}
	sprite_render(stagesuuzi[serect_stage],
		80,40,
		1.3,1.3);

	sprite_render(suuzi,
		200, 125,
		1, 1,
		0 + ((kirikaejougen - kirikaekaisuu) * 100), 0,
		100, 100);

	
	for (int j = 0; j < plantkosuu; j++)
	{
		for (int i = 0; i < yorusanpu[j] * 5; i++)
		{
			sprite_render(kuki, pulantpos[j].x + 32, pulantpos[j].y - (32 * i) + 72);
		}
		for (int i = 0; i < yorusanpu[j] + 1; i++)
		{
			sprite_render(plant, pulantpos[j].x, pulantpos[j].y - (plant_growth * i) + 8);
		}
	}
	
	//kaihukuが黄色いボタンsanpulがUI肥料のやつ

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

	for (int i = 0; i < panerukosuu; i++)
	{
		for (int k = 0; k < plantkosuu; k++)
		{
			for (int i = 0; i < 4; i++)
			{
				if ((planthantei[i][k]) && hiyoudasu)
				{
					if (play.sayuu)
					{
						if (!hiyoorjousou)
						{
							sprite_render(chara_hiryou,
								play.position.x + 10, play.position.y,
								1, 1, 96 * (hiyoutimer / 15), 0,
								96, 96);
						}
						else sprite_render(chara_jyosou,
							play.position.x + 10, play.position.y,
							1, 1, 96 * (hiyoutimer / 15), 0,
							96, 96);
					}
					else
					{
						if (!hiyoorjousou)
						{
							sprite_render(chara_hiryou,
								play.position.x + 85, play.position.y,
								-1, 1, 96 * (hiyoutimer / 15), 0,
								96, 96);
						}
						else sprite_render(chara_jyosou,
							play.position.x + 85, play.position.y,
							-1, 1, 96 * (hiyoutimer / 15), 0,
							96, 96);
					}
				}

				if (kaihukukirikae[i] || planthantei[i][k])
				{
					switch (kaihuku)
					{
					case 0:
						sprite_render(sanpu[0],
							sanpulpos.x, sanpulpos.y, 1, 1);
						break;
					case 1:
						sprite_render(sanpu[1],
							sanpulpos.x, sanpulpos.y, 1, 1);
						break;
					case 2:
						sprite_render(sanpu[2],
							sanpulpos.x, sanpulpos.y, 1, 1);
						break;
					case 3:
						sprite_render(sanpu[3],
							sanpulpos.x, sanpulpos.y, 1, 1);
						break;
					}
				}
			}
		}
	
		for (int j = 0; j < sabotenkosuu; j++)
		{
			if (sabotenhantei[j] && hiyoudasu)
			{
				if (play.sayuu)
				{
					if (!hiyoorjousou)
					{
						sprite_render(chara_hiryou,
							play.position.x + 10, play.position.y,
							1, 1, 96 * (hiyoutimer / 15), 0,
							96, 96);
					}
					else sprite_render(chara_jyosou,
						play.position.x + 10, play.position.y,
						1, 1, 96 * (hiyoutimer / 15), 0,
						96, 96);
				}
				else
				{
					if (!hiyoorjousou)
					{
						sprite_render(chara_hiryou,
							play.position.x + 85, play.position.y,
							-1, 1, 96 * (hiyoutimer / 15), 0,
							96, 96);
					}
					else sprite_render(chara_jyosou,
						play.position.x + 85, play.position.y,
						-1, 1, 96 * (hiyoutimer / 15), 0,
						96, 96);
				}
			}

			if (sabotenhantei[j] && !sabotenjosou[j])
			{
				switch (kaihuku)
				{
				case 0:
					sprite_render(sanpu[0],
						sanpulpos.x, sanpulpos.y, 1, 1);
					break;
				case 1:
					sprite_render(sanpu[1],
						sanpulpos.x, sanpulpos.y, 1, 1);
					break;
				case 2:
					sprite_render(sanpu[2],
						sanpulpos.x, sanpulpos.y, 1, 1);
					break;
				case 3:
					sprite_render(sanpu[3],
						sanpulpos.x, sanpulpos.y, 1, 1);
					break;
				}
			}
		}
	}

	if (gorlhantei)
	{
		
		if (gorltimer > 0 && gorltimer < 56)
		{
			sprite_render(gorlhubki,
				32 * gorlpos.x - 30, 32 * gorlpos.y - 30,
				1.5f,1.25f,
				120 * (gorltimer / 8), 0,
				120,120);
		}
		if (gorltimer > 32)
		{
			sprite_render(star[0],
				32 * gorlpos.x - 32, 32 * gorlpos.y,
				0.5f,0.5f);
		}
		if (gorltimer > 36 && kirikaekaisuu < kirikaejougen - gorljouken[0])
		{
			sprite_render(star[0],
				32 * gorlpos.x + 24, 32 * gorlpos.y,
				0.5f, 0.5f);
		}
		else if (gorltimer > 37)
		{
			sprite_render(star[1],
				32 * gorlpos.x + 24, 32 * gorlpos.y,
				0.5f, 0.5f);
		}
		if (gorltimer > 40 && kirikaekaisuu < kirikaejougen - gorljouken[1])
		{
			sprite_render(star[0],
				32 * gorlpos.x + 80, 32 * gorlpos.y,
				0.5f, 0.5f);
		}
		else if (gorltimer > 42)
		{
			sprite_render(star[1],
				32 * gorlpos.x + 80, 32 * gorlpos.y,
				0.5f, 0.5f);
		}
	}
	if (game_title == 1 && !gorlhantei)
	{	
		timer++;
		if (timer == 600 && kaihuku < 3 && timerpoint == 0)
		{
			kaihuku = 3;
			
		}
		
		if (kaihuku == 3 && timerpoint == 0)
		{
			timerpoint++;
			timer = 0;
		}

		if (timer == 880 && timerpoint == 1)
		{
			timer = 0;
			timerhiryou = true;
		}

		if (timerpoint == 1 && timerhiryou)
		{
			timerpoint++;
			timer = 0;
		}

		if (timerpoint == 2 && timercrek)
		{
			timerpoint++;
			timer = 0;
		}

		if (timer == 880 && timerpoint == 2)
		{
			timer = 0;
			timercrek = true;
		}
		if (timer < 120 && timerpoint < 1)
		{
			sprite_render(kanban[0],
				960 - 256, 540 - 144,
				2, 2);
		}
		else if (timer < 600 && timerpoint < 1)
		{
			sprite_render(kanban[1],
				960 - 256, 540 - 144,
				2, 2);
			
		}
		else if (timer < 350 && timerpoint < 2)
		{
			sprite_render(kanban[2],
				960 - 256, 540 - 144,
				2, 2);
		}
		else if (timer < 700 && timerpoint < 2)
		{
			sprite_render(kanban[3],
				960 - 256, 540 - 144,
				2, 2);
		}
		else if(timer < 1180 && timerpoint < 2)
		{
			sprite_render(kanban[4],
				960 - 256, 540 - 144,
				2, 2);
		}
		else if(timer < 350 && timerpoint < 3)
		{
			sprite_render(kanban[5],
				960 - 256, 540 - 144,
				2, 2);
		}
		else if(timer < 700 && timerpoint < 3)
		{
			sprite_render(kanban[6],
				960 - 256, 540 - 144,
				2, 2);
		}
		else if(timer < 1180 && timerpoint < 3)
		{
			sprite_render(kanban[7],
				960 - 256, 540 - 144,
				2, 2);
		}
		else if(timer < 350 && timerpoint < 4)
		{
			sprite_render(kanban[8],
				960 - 256, 540 - 144,
				2, 2);
		}
		else if(timer < 700 && timerpoint < 4)
		{
			sprite_render(kanban[9],
				960 - 256, 540 - 144,
				2, 2);
		}
		else if(timer < 1050 && timerpoint < 4)
		{
			sprite_render(kanban[10],
				960 - 256, 540 - 144,
				2, 2);
		}

	}
}



void maps::game_deinit()
{
	safe_delete(asa);
	safe_delete(yoru);
	safe_delete(tuti);
	for (int i = 0; i < 10; i++)
	{
		safe_delete(stagesuuzi[i]);
	}
	for (int i = 0; i < 4; i++)
	{
		safe_delete(sanpu[i]);
	}
	for (int i = 0; i < 2; i++)
	{
		safe_delete(asayorukirikae[i]);
		safe_delete(home[i]);
		safe_delete(star[i]);
		safe_delete(reset[i]);
		safe_delete(retrai[i]);
		safe_delete(taitoru[i]);
		safe_delete(newstege[i]);
	}
	safe_delete(botan);
	safe_delete(paneru);
	safe_delete(gorl);
	safe_delete(saboten);
	safe_delete(plant);
	safe_delete(chara_jyosou);
	safe_delete(chara_hiryou);
	safe_delete(g_kuki_sprite);
	safe_delete(U_kettei1);
	safe_delete(U_kettei2);
	safe_delete(kuki);
	safe_delete(gorlhubki);
	safe_delete(suuzi);
	safe_delete(gameoverspr);
	
}

