//******************************************************************************
//
//      scene_game.cpp
//
//******************************************************************************

#include "all.h"


#include <cmath>  // 距離計算に使用

using namespace DirectX;
using namespace input;  // input名前空間使う想定
#include <memory>
#include <sstream>

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "player.h"
#include"map.h"
#include "obj.h"
#include "title.h"
#include "sound.h"
#include "serect.h"


//------< 定数・型定義 >----------------------------------------------------------------



const int PLANT_GROWTH_MAX = 30;
const int PLANT_GROWTH_MIN = 0;
const int UI_DISTANCE_THRESHOLD = 100; // プレイヤーが植物に近づく距離の閾値


enum TimeOfDay {
    MORNING,
    NIGHT
};

//------< グローバル変数 >-----------------------------------------------------
std::unique_ptr<Keyboard> keyboard;
std::unique_ptr<Mouse> mouse;
Mouse::ButtonStateTracker mouseTracker;

//------< 変数 >----------------------------------------------------------------
int plant_growth = 160 ;


int fertilizer_amount = 0;  // 肥料量
int herbicide_amount = 0;   // 除草剤量
static bool f_prev;




TimeOfDay current_time = MORNING;

// UIスプライト（仮）
//Sprite* plant;

// プレイヤーの座標（仮の値）
float player_x = 700.0f;
float player_y = 950.0f;

// 植物の座標（同じく仮の位置）
float plant_x = 700.0f;
float plant_y = 920.0f;

extern player play;
extern maps stege;
extern obj objs;
extern ongaku o;
title t;
serect s;

Sprite* sukop;


//------< 変数 >----------------------------------------------------------------

int game_state = 0;    // 状態
int game_timer = 0;    // タイマー
int game_title = 0;
int serect_state = 0;
//--------------------------------------
// 初期設定
//--------------------------------------
void game_init()
{
    serect_state = 0;
    game_title = 0;
    game_state = 0;
    game_timer = 0;
    current_time = MORNING;   
}



//--------------------------------------
// 更新処理
//--------------------------------------
void game_update()
{
    ShowCursor(FALSE);
    switch (game_state)
    {
    case 0:
        //////// ////////
        GameLib::setBlendMode(Blender::BS_ALPHA);
        o.init();
        sukop = sprite_load(L"./Data/Images/U_cursor.png");
        game_state++;
    case 1:
   
        t.init();
        game_state++;
    case 2:
        t.update(&game_title);
        t.render();
        if (game_title == 1)
        {
            game_state = 5;
            serect_state = 0;
        }
        if (game_title == 2) game_state++;
        if (game_title > 0) t.deinit();
        break;
    case 3:
        s.init();
        game_state++;
    case 4:
        s.update(&serect_state,&game_state);
        s.render();
        if (game_state == 5) s.deinit();
        break;
    case 5:
        ////////////////
        objs.init(serect_state);
        play.init(serect_state);
        stege.init(serect_state,game_title);
     
        game_state++;
    case 6:
        ////////  ////////
        if (!stege.gameover)
        {
            play.update(serect_state, game_title);
            objs.update();
        }
        stege.re(&game_state,serect_state);
        stege.syuuryou(&game_state, &serect_state, serect_state,game_title);
        game_render();
        break;
    }
    int getx = getCursorPosX();
    int gety = getCursorPosY();
    sprite_render(sukop, getx, gety);
    game_timer++;
}

//--------------------------------------
// 描画処理
//--------------------------------------
void game_render()
{
  GameLib::clear(0.0, 0.0, 0.0);
  stege.render(serect_state,game_title);
    play.render();
    objs.render();

    if (stege.gameover)
    {
        sprite_render(stege.gameoverspr, 0, 0);
    }
    if (stege.gorlhantei && serect_state < 9)
    {
        if (!stege.newstagehantei)
        {
            sprite_render(stege.newstege[0],
                stege.newstegepos.x, stege.newstegepos.y);
        }
        else
        {
            sprite_render(stege.newstege[1],
                stege.newstegepos.x, stege.newstegepos.y);
        }
    }
    if(stege.gameover || stege.gorlhantei)
    {
        if (!stege.taitoruhantei)
        {
            sprite_render(stege.taitoru[0], stege.taitorupos.x + 140, stege.taitorupos.y + 30,
                1, 1);
        }
        else sprite_render(stege.taitoru[1], stege.taitorupos.x, stege.taitorupos.y,
            2, 2);
    }
    if (stege.gameover)
    {
        if (!stege.restarthatei)
        {

            sprite_render(stege.retrai[0], stege.retraipos.x + 140, stege.retraipos.y + 30,
                1, 1);
         
        }
        else   sprite_render(stege.retrai[1], stege.retraipos.x, stege.retraipos.y,
            2, 2);
    }
}

//--------------------------------------
// 終了処理
//--------------------------------------
void game_deinit()
{


    stege.game_deinit();
    play.game_deinit();
    objs.game_deinit();
    

}

