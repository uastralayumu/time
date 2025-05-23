#include "map.h"
#include "obj.h"

extern player play;
extern obj objs;

int chara_anim = 0;          // �A�j������p�J�E���^

Sprite* asa;
Sprite* yoru;
Sprite* tuti;
Sprite* botan;
Sprite* paneru;
Sprite* sanpu[4];
Sprite* gorl;
Sprite* gorlgo;
Sprite* saboten;
Sprite* plant;
Sprite* chara_jyosou;//������
Sprite* chara_hiryou;//�엿
//void maps::init()
//{
//	asa = sprite_load(L"./Data/Images/H_asa.png");
//	yoru = sprite_load(L"./Data/Images/H_yoru.png");
//	botan = sprite_load(L"./Data/Images/UI_kari.png");
//	tuti = sprite_load(L"./Data/Images/tuti_kari.png");
//	paneru = sprite_load(L"./Data/Images/jyuudenn_kari.png");
//	sanpu[0] = sprite_load(L"./Data/Images/U_sanpu4.png");
//	sanpu[1] = sprite_load(L"./Data/Images/U_sanpu3.png");
//	sanpu[2] = sprite_load(L"./Data/Images/U_sanpu2.png");
//	sanpu[3] = sprite_load(L"./Data/Images/U_sanpu1.png");
//	gorl = sprite_load(L"./Data/Images/G_Gole.png");
//	gorlgo = sprite_load(L"./Data/Images/nextUI_kari.png");
//	saboten = sprite_load(L"./Data/Images/saboten.png");
//	plant = sprite_load(L"./Data/Images/plant_kari.png");
//	for (int i = 0; i < chip_y; i++)
//	{
//		for (int j = 0; j < chip_x; j++)
//		{
//			tikei[i][j] = toti[i][j];
//		}
//	}
//}



bool maps::isfloor(float x, float y, float width)
{
	for (; width > 0; width -= 32)
	{
		const float left = x - width;
		const float right = x + width;

		if (left < 0) continue;
		if (right >= chip_x * 32) continue;

		if (ishitdown(left, y)) return true;
		if (ishitdown(right, y)) return true;
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

void maps::state()
{
	if (play.position.x + 56 > sabotenpos.x * 64 && play.position.x < sabotenpos.x * 64 + 56 &&
		play.position.y  < sabotenpos.y * 64 + 96 && play.position.y + 64 > sabotenpos.y * 64)
	{
		play.position = { 1000.0f,930.0f };
		objs.position = { 1500.0f,930.0f };
		kaihuku = 0;
		objs.motu = false;
	}

}

void maps::syuuryou()
{
	if (play.position.x + 48 > gorlpos.x * 64 && play.position.x < gorlpos.x * 64 + 64 &&
		play.position.y  < gorlpos.y * 64 + 96 && play.position.y > gorlpos.y * 64 + 28)
	{
		gorlhantei = true;
	}
}

//void maps::update()
//{
//	{
//		int getx = getCursorPosX();
//		int gety = getCursorPosY();
//		if (getx > botanpos.x + 70 && getx < botanpos.x + 230 && gety < botanpos.y + 117 && gety > botanpos.y + 65 && TRG(0) & PAD_START)
//		{
//			if (kirikae)kirikae = FALSE;
//			else kirikae = TRUE;
//		}
//	}
//
//	if (play.position.x + 48 > panerupos.x * 64 && play.position.x < panerupos.x * 64 + 40 &&
//		play.position.y  < panerupos.y * 64 + 40 && play.position.y > panerupos.y * 64 + 28)
//	{
//
//
//		if (play.position.y > panerupos.y * 64 + 28 && play.position.y < panerupos.y * 64 + 40)
//		{
//			play.position.y = panerupos.y * 64 + 28;
//			play.vector.y = 0;
//			play.onGround = TRUE;
//			if (kirikae)
//			{
//				kaihukukirikae = TRUE;
//				if (kaihukutaimer == 0)kaihuku++;
//				if (kaihuku > 3) kaihuku = 3;
//				kaihukutaimer++;
//			}
//			else
//			{
//				kaihukukirikae = FALSE;
//			}
//		}
//	}
//	else
//	{
//		kaihukukirikae = FALSE;
//	}
//
//	if (kaihukutaimer == 60) kaihukutaimer = 0;
//	state();
//	syuuryou();
//
//}

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
				1, 1,
				tikei[j][i] * 64);
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

	sprite_render(chara_hiryou,
		play.position.x + 100, play.position.y,
		1, 1, 96 * 2, 0,
		96,96);
	if (plantHasFertilizer)
	{

	}

	/*if (plantHasFertilizer)
	{
		sprite_render(chara_hiryou, play.position.x, play.position.y,1,1,96 * 0,96,
			96);
	}
	else
	{
		sprite_render(chara_jyosou, play.position.x, play.position.y, 1, 1, 96 * 0, 96,
			96);
	}*/
	sprite_render(plant, 700, 920 - plant_growth);
	//kaihuku�����F���{�^��sanpul��UI�엿�̂��
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

// ------------------------------------------------------------
// maps.cpp
// ------------------------------------------------------------
//#include "map.h"
//
//#include "player.h"
//#include "obj.h"
//#include <cassert>
//#include <algorithm>
//#include <cmath>

extern player play;
extern obj objs;

//// ���� �O���V���{��
constexpr float SANPU_W = 64.0f;
constexpr float SANPU_H = 64.0f;
constexpr float PLANT_W = 32.0f;
constexpr float PLANT_H = 64.0f;
constexpr float KUKI_W = 32.0f;
constexpr float KUKI_H = 64.0f;
constexpr float UI_X = 1500.0f;     
constexpr float UI_Y = 100.0f;      
constexpr float UI_W = 340.0f;   // �摜�T�C�Y�ɍ��킹�Ē���
constexpr float UI_H = 192.0f;

//extern player play;
//extern obj    objs;
////extern player play;
////extern obj    objs;
//
//// ���� �X�v���C�g
//Sprite* asa;
//Sprite* yoru;
//Sprite* tuti;
//Sprite* botan;
//Sprite* paneru;
//Sprite* sanpu[4];
//Sprite* gorl;
//Sprite* gorlgo;
//Sprite* saboten;
//Sprite* plant;
Sprite* g_kuki_sprite;          // ��G_Kuki �e�N�X�`��
Sprite* chara_damage;
Sprite* U_kettei1;
Sprite* U_kettei2;


//
///*====================================================================
//    ���[�e�B���e�B�F�ȈՋ�`
// ====================================================================*/
struct Rect { float x, y, w, h; };
static bool hit(const Rect& a, const Rect& b)
{
    return !(a.x + a.w < b.x || b.x + b.w < a.x ||
        a.y + a.h < b.y || b.y + b.h < a.y);
}

/*====================================================================
    maps::init
 ====================================================================*/
void maps::init()
{
    asa = sprite_load(L"./Data/Images/H_asa.png");
    yoru = sprite_load(L"./Data/Images/H_yoru.png");
    botan = sprite_load(L"./Data/Images/UI_kari.png");
    tuti = sprite_load(L"./Data/Images/tuti_kari.png");
    paneru = sprite_load(L"./Data/Images/jyuudenn_kari.png");
    sanpu[0] = sprite_load(L"./Data/Images/U_sanpu4.png");
    sanpu[1] = sprite_load(L"./Data/Images/U_sanpu3.png");
    sanpu[2] = sprite_load(L"./Data/Images/U_sanpu2.png");
    sanpu[3] = sprite_load(L"./Data/Images/U_sanpu1.png");
    gorl = sprite_load(L"./Data/Images/G_Gole.png");
    gorlgo = sprite_load(L"./Data/Images/nextUI_kari.png");
    saboten = sprite_load(L"./Data/Images/saboten.png");
    plant = sprite_load(L"./Data/Images/plant_kari.png");
    g_kuki_sprite = sprite_load(L"./Data/Images/G_kuki.png");
	chara_damage = sprite_load(L"./Data/Images/chara_damage.png");
	U_kettei1 = sprite_load(L"./Data/Images/U_kettei1.png");
	U_kettei2 = sprite_load(L"./Data/Images/U_kettei2.png");
	chara_jyosou = sprite_load(L"./Data/Images/chara_jyosou.png");
	chara_hiryou = sprite_load(L"./Data/Images/chara_hiryou.png");

    // �ϗ̈���Œ�n�`�ŏ�����
   /* for (int i = 0; i < chip_y; i++)
        for (int j = 0; j < chip_x; j++)
            tikei[i][j] = toti[i][j]; */
	for (int i = 0; i < chip_y; i++)
	{
		for (int j = 0; j < chip_x; j++)
		{
			tikei[i][j] = toti[i][j];
		}
	}
}


 /*====================================================================
     sanpu UI ���E�N���b�N����
  ====================================================================*/
void maps::handleSanpuClick()
{
	if (!kaihukukirikae) return;

	if (!(TRG(0) & PAD_START)) return;

	// �}�E�X���W�� float �ɃL���X�g
	float mx = static_cast<float>(getCursorPosX());
	float my = static_cast<float>(getCursorPosY());



	// ���������E������
	bool clickLeft = (UI_X<mx&&mx<UI_X+UI_W&&UI_Y<my&&my<UI_Y+UI_H);
	//bool clickRight = !clickLeft;


		/*-------------------------------------------------
	 �엿�^�����܃t���O�̍X�V
	-------------------------------------------------*/
	if (clickLeft)
	{
		/*-------------------- �엿 --------------------*/
		plantHasFertilizer = true;      // fertilize �t���O ON
		plantHasHerbicide = false;     // herbicide �t���O OFF


	}
	else
	{
		/*-------------------- ������ ------------------*/
		plantHasHerbicide = true;
		plantHasFertilizer = false;


	}

	

//sanpu�̍����N���b�N�����plant�ɔ엿���U�z����Ă鎞charahiryou������



//sanpu���E�N���b�N�����plant�ɏ����܂��U�z����Ă鎞chara_jyosou������




}
/*====================================================================
    G_Kuki �����^�폜
 ====================================================================*/
void maps::growKuki()
{
    DirectX::XMFLOAT2 base = { 700, 920 - plantStage * 32.f };
    DirectX::XMFLOAT2 p = { base.x + static_cast<float>(kukiList.size() + 1) * 64 * 2, base.y };
    kukiList.push_back(p);
}
void maps::decayKuki()
{
    if (!kukiList.empty()) kukiList.pop_back();
}

/*====================================================================
    plant / G_Kuki �Ƃ̓����蔻��
 ====================================================================*/
bool maps::ishitKukiOrPlant(float x, float y)
{
    // �v���C���[�� AABB
    Rect pl{ x - 16.0f, y - 32.0f, 32.0f, 64.0f };

    // plant �{�̂� AABB ��萔�Œ�`
    Rect pr{
        700.0f,
        920.0f - plantStage * 32.0f,
        PLANT_W,
        PLANT_H
    };
    if (hit(pl, pr)) return true;

    // G_Kuki �Q�Ƃ̏Փ�
    for (auto& k : kukiList) {
        if (hit(pl, { k.x, k.y, KUKI_W, KUKI_H })) return true;
    }
    return false;
}

///*====================================================================
//    maps::update
// ====================================================================*/
void maps::update()
{
    /* ---------- ���� UI �{�^������ ---------- */
    int cx = getCursorPosX();
    int cy = getCursorPosY();
    if (cx > botanpos.x + 70 && cx < botanpos.x + 230 &&
        cy > botanpos.y + 65 && cy < botanpos.y + 117 &&
        TRG(0) & PAD_START)
    {
        kirikae = !kirikae;
    }

    /* ---------- sanpu UI & plant ���� ---------- */
    handleSanpuClick();
    /*updatePlantGrowth();*/

    /* ---------- plant �t�߂� sanpu �\�� ---------- */
    Rect playRect{ play.position.x - 16.0f,
                     play.position.y - 32.0f,
                     32.0f, 64.0f };

    
    Rect plantRect{
        700.0f,
        920.0f - plantStage * 32.0f,
        PLANT_W,
        PLANT_H
    };

	
    kaihukukirikae = hit(playRect, plantRect);
	if (play.position.x + 48 > panerupos.x * 64 && play.position.x < panerupos.x * 64 + 40 &&
		play.position.y  < panerupos.y * 64 + 40 && play.position.y > panerupos.y * 64 + 28)
	{


		if (play.position.y > panerupos.y * 64 + 28 && play.position.y < panerupos.y * 64 + 40)
		{
			play.position.y = panerupos.y * 64 + 28;
			play.vector.y = 0;
			play.onGround = TRUE;
			if (kirikae)
			{
				kaihukukirikae = TRUE;
				if (kaihukutaimer == 0)kaihuku++;
				if (kaihuku > 3) kaihuku = 3;
				kaihukutaimer++;
			}
			else
			{
				kaihukukirikae = FALSE;
			}
		}
	}
	else if(hit(playRect, plantRect) == FALSE)
	{
		kaihukukirikae = FALSE;
	}

	if (kaihukutaimer == 60) kaihukutaimer = 0;
	state();
	syuuryou();
// ============================================================
// maps::update �̖���������ɒǉ�
// ============================================================
	{
		// �엿�^�����܃t���O�������Ă���Ԃ����A�j���^�C�}�[��i�߂�
		if (plantHasFertilizer || plantHasHerbicide) {
			chara_anim = (chara_anim + 1) % 60;  // 0�`59 �Ń��[�v
		}
		else {
			chara_anim = 0;
		}
	}

	// ============================================================
	// maps::render ���Asanpu UI �`��̂��Ƃɒǉ�
	// ============================================================
		// �� �엿�U�z���L�����A�j��
	if (plantHasFertilizer) {
		// ��F�㉺�ɂ���瓮����
		float dy = std::sin(chara_anim * 2.0f * 3.1415f / 60.0f) * 5.0f;
		sprite_render(chara_hiryou,
			play.position.x, play.position.y + 64 + dy,
			1, 1);
	}

	// �� �����܎U�z���L�����A�j��
	if (plantHasHerbicide) {
		// ��F���E�ɂ���瓮����
		float dx = std::sin(chara_anim * 2.0f * 3.1415f / 60.0f) * 5.0f;
		sprite_render(chara_jyosou,
			play.position.x + dx, play.position.y + 64,
			1, 1);
	}
}
    /* ---------- �p�l������i�����j ---------- */
    // ...�i�����̃p�l����蔻��R�[�h�����̂܂܁j...

   // state();
    //syuuryou();
//}
//
///*====================================================================
//    maps::render
// ====================================================================*/
//void maps::render()
//{
//    /* ---------- �w�i ---------- */
//    sprite_render(kirikae ? asa : yoru, 0, 0, 1, 1, 0, 0, 1980, 1080);
//
//    /* ---------- �n�` ---------- */
//    for (int i = 0; i < chip_x; i++)
//        for (int j = 0; j < chip_y; j++)
//            sprite_render(tuti, i * 32, j * 32, 1, 1, tikei[j][i] * 64);
//
//    /* ---------- �I�u�W�F�N�g ---------- */
//    sprite_render(paneru, 64 * panerupos.x, 64 * panerupos.y + 32);
//    sprite_render(saboten, sabotenpos.x * 64, sabotenpos.y * 64 + 32);
//    sprite_render(gorl, 64 * gorlpos.x, 64 * gorlpos.y + 32);
//
//    /* ---------- plant & G_Kuki ---------- */
//    sprite_render(plant, 700, 920 - plantStage * 32.f);
//    for (auto& k : kukiList)
//        sprite_render(g_kuki_sprite, k.x, k.y);
//
//    /* ---------- sanpu UI ---------- */
//    if (kaihukukirikae) {
//        sprite_render(sanpu[plantStage], 1500, 100);
//    }
//
//    /* ---------- ���̑� UI ---------- */
//    sprite_render(botan, botanpos.x, botanpos.y);
//    if (gorlhantei)
//        sprite_render(gorlgo, 900, 500);
//}




//#include "map.h"
//#include "obj.h"
// 
//extern player play;
//extern obj objs;
//
//Sprite* asa;
//Sprite* yoru;
//Sprite* tuti;
//Sprite* botan;
//Sprite* paneru;
//Sprite* sanpu[4];
//Sprite* gorl;
//Sprite* gorlgo;
//Sprite* saboten;
//Sprite* plant;
//void maps::init()
//{
//	asa = sprite_load(L"./Data/Images/H_asa.png");
//	yoru = sprite_load(L"./Data/Images/H_yoru.png");
//	botan = sprite_load(L"./Data/Images/UI_kari.png");
//	tuti = sprite_load(L"./Data/Images/tuti_kari.png");
//	paneru = sprite_load(L"./Data/Images/jyuudenn_kari.png");
//	sanpu[0] = sprite_load(L"./Data/Images/U_sanpu4.png");
//	sanpu[1] = sprite_load(L"./Data/Images/U_sanpu3.png");
//	sanpu[2] = sprite_load(L"./Data/Images/U_sanpu2.png");
//	sanpu[3] = sprite_load(L"./Data/Images/U_sanpu1.png");
//	gorl = sprite_load(L"./Data/Images/G_Gole.png");
//	gorlgo = sprite_load(L"./Data/Images/nextUI_kari.png");
//	saboten = sprite_load(L"./Data/Images/saboten.png");
//	plant = sprite_load(L"./Data/Images/plant_kari.png");
//	for (int i = 0; i < chip_y; i++)
//	{
//		for (int j = 0; j < chip_x; j++)
//		{
//			tikei[i][j] = toti[i][j];
//		}
//	}
//}
//
//
//
//bool maps::isfloor(float x,float y,float width)
//{
//	for (; width > 0; width -= 32)
//	{
//		const float left = x - width;
//		const float right = x + width;
//
//		if (left < 0) continue;
//		if (right >= chip_x * 32) continue;
//		
//		if (ishitdown(left, y)) return true;
//		if (ishitdown(right, y)) return true;
//	}
//	return ishitdown(x, y);
//}
//
//bool maps::isceiling(float x, float y, float width)
//{
//	for (; width > 0; width -= 32)
//	{
//		const float left = x - width;
//		const float right = x + width;
//
//		if (left < 240) continue;
//		if (right >= chip_x * 32) continue;
//		if (ishitall(left, y)) 
//			return true;
//		if (ishitall(right, y)) 
//			return true;
//	}
//	return ishitall(x, y);
//}
//
//bool maps::iswall(float x, float y, float height)
//{
//	for (; height > 0; height -= 32)
//	{
//		const float yPos = y - height;
//		if (yPos < 0)      continue;
//		if (yPos > chip_y * 32) continue;
//
//		if (ishitall(x, yPos))
//			return true;
//		if (ishitall(x, yPos + 32))
//			return true;
//		if (ishitall(x, yPos + 64))
//			return true;
//	}
//
//	return ishitall(x, y);
//}
//
//int maps::getdata(char mapchip[][chip_x], const DirectX::XMFLOAT2& pos)
//{
//	int divx = static_cast<int>(pos.x) / 32;
//	int divy = static_cast<int>(pos.y) / 32;
//
//	if (divx < 0 || divx >= chip_x ||
//		divy < 0 || divy >= chip_y)
//		return -1;
//
//	return mapchip[divy][divx];
//}
//
//bool maps::ishitdown(float x, float y)
//{
//	DirectX::XMFLOAT2 pos = { x, y };
//	switch (getTerrainAttr(pos))
//	{
//	case tr_attr::ALL_BLOCK: return true;
//	}
//	return false;
//
//}
//
//bool maps::ishitall(float x, float y)
//{
//	DirectX::XMFLOAT2 pos = { x, y };
//	return(getTerrainAttr(pos)) == ALL_BLOCK;
//}
//
//maps::tr_attr maps::getTerrainAttr(const DirectX::XMFLOAT2& pos)
//{
//	int index = getdata(tikei, pos);
//	if (index < 0)return TR_NONE;
//	assert(index < CHIP_NUM_PER_LINE* CHIP_LINE_NUM);
//	return tikeiattr[index];
//}
//
//void maps::playmaphosedown()
//{
//	float y = play.position.y;
//	int inty = static_cast<int>(y);
//	y = static_cast<float>(inty - inty % 32);
//	play.position.y = y + 5.01f;
//	play.vector.y = (std::min)(play.vector.y, 0.0f);
//}
//
//void maps::playmaphoseup()
//{
//	float y = play.position.y;
//	y += 32 - fmodf(y, 32);
//	play.position.y = y - 8;
//	play.vector.y = (std::max)(play.vector.y, 0.0f);
//}
//
//void maps::playmaphoseright()
//{
//	float x = play.position.x;
//	x -= fmodf(x, 32);
//	play.position.x = x - 0.025f;
//	play.vector.x = 0.0f;
//}
//
//void maps::playmaphoseleft()
//{
//	float x = play.position.x;
//	x -= fmodf(x, 32);
//	play.position.x = x + 32 + 0.025f;
//	play.vector.x = 0.0f;
//}
//
//void maps::objmaphosedown()
//{
//	float y = objs.position.y;
//	int inty = static_cast<int>(y);
//	y = static_cast<float>(inty - inty % 32);
//	objs.position.y = y - 0.01f;
//	objs.vector.y = (std::min)(objs.vector.y, 0.0f);
//}
//
//void maps::objmaphoseup()
//{
//	float y = objs.position.y;
//	y += 32 - fmodf(y, 32);
//	objs.position.y = y - 8;
//	objs.vector.y = (std::max)(objs.vector.y, 0.0f);
//}
//
//void maps::objmaphoseright()
//{
//	float x = objs.position.x;
//	x -= fmodf(x, 32);
//	objs.position.x = x - 0.025f;
//	objs.vector.x = 0.0f;
//}
//
//void maps::objmaphoseleft()
//{
//	float x = objs.position.x;
//	x -= fmodf(x, 32);
//	objs.position.x = x + 32 + 0.025f;
//	objs.vector.x = 0.0f;
//}
//
//void maps::state()
//{
//	if (play.position.x + 56 > sabotenpos.x * 64 && play.position.x < sabotenpos.x * 64 + 56 &&
//		play.position.y  < sabotenpos.y * 64 + 96 && play.position.y + 64 > sabotenpos.y * 64)
//	{
//		play.position = { 1000.0f,930.0f };
//		objs.position = { 1500.0f,930.0f };
//		kaihuku = 0;
//		objs.motu = false;
//	}
//	
//}
//
//void maps::syuuryou()
//{
//	if (play.position.x + 48 > gorlpos.x * 64 && play.position.x < gorlpos.x * 64 + 64 &&
//		play.position.y  < gorlpos.y * 64 + 96 && play.position.y > gorlpos.y * 64 + 28)
//	{
//		gorlhantei = TRUE;
//	}
//}
//
//void maps::update()
//{
//	{
//		int getx = getCursorPosX();
//		int gety = getCursorPosY();
//		if (getx > botanpos.x + 70 && getx < botanpos.x + 230 && gety < botanpos.y + 117 && gety > botanpos.y + 65 && TRG(0) & PAD_START)
//		{
//			if (kirikae)kirikae = FALSE;
//			else kirikae = TRUE;
//		}
//	}
//
//	if (play.position.x + 48 > panerupos.x * 64 && play.position.x < panerupos.x * 64 + 40 &&
//		play.position.y  < panerupos.y * 64 + 40 && play.position.y > panerupos.y * 64 + 28)
//	{
//		
//		
//			if (play.position.y > panerupos.y * 64 + 28 && play.position.y < panerupos.y * 64 + 40)
//			{
//				play.position.y = panerupos.y * 64 + 28;
//				play.vector.y = 0;
//				play.onGround = TRUE;
//				if (kirikae)
//				{
//					kaihukukirikae = TRUE;
//					if (kaihukutaimer == 0)kaihuku++;
//					if (kaihuku > 3) kaihuku = 3;
//					kaihukutaimer++;
//				}
//				else
//				{
//					kaihukukirikae = FALSE;
//				}
//			}
//	}
//	else
//	{
//		kaihukukirikae = FALSE;
//	}
//	
//	if (kaihukutaimer == 60) kaihukutaimer = 0;
//	state();
//	syuuryou();
//	
//}
//
//void maps::render()
//{
//	if (kirikae)
//	{
//		sprite_render(asa,
//			0, 0,
//			1, 1,
//			0, 0,
//			1980, 1080,
//			0, 0,
//			0,
//			1, 1, 1, 1);
//	}
//	else
//	{
//		sprite_render(yoru,
//			0, 0,
//			1, 1,
//			0, 0,
//			1980, 1080,
//			0, 0,
//			0,
//			1, 1, 1, 1);
//	}
//
//	for (int i = 0; i < chip_x; i++)
//	{
//		for (int j = 0; j < chip_y; j++)
//		{
//			sprite_render(
//				tuti,
//				i * 32, j * 32,
//				1,1,
//				tikei[j][i] * 64);
//		}
//	}
//
//	sprite_render(paneru,
//		64 * panerupos.x, 64 * panerupos.y + 32);
//
//	sprite_render(saboten,
//		sabotenpos.x * 64, sabotenpos.y * 64 + 32);
//
//	sprite_render(gorl,
//		64 * gorlpos.x, 64 * gorlpos.y + 32);
//
//	
//	sprite_render(botan,
//		botanpos.x, botanpos.y, 1, 1);
//	
//	sprite_render(plant, 700, 920 - plant_growth);
//	//kaihuku�����F���{�^��sanpul��UI�엿�̂��
//	if (kaihukukirikae)
//	{
//		switch (kaihuku)
//		{
//		case 0:
//			sprite_render(sanpu[0],
//				1500, 100, 1, 1);
//			break;
//		case 1:
//			sprite_render(sanpu[1],
//				1500, 100, 1, 1);
//			break;
//		case 2:
//			sprite_render(sanpu[2],
//				1500, 100, 1, 1);
//			break;
//		case 3:
//			sprite_render(sanpu[3],
//				1500, 100, 1, 1);
//			break;
//		}
//	}
//
//	if (gorlhantei)
//	{
//		sprite_render(gorlgo,
//			900, 500);
//	}
//	
//}