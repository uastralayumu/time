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
int plant_growth = 0;


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
    
  

    switch (game_state)
    {
    case 0:


        //////// �p�����[�^�̐ݒ� ////////
        GameLib::setBlendMode(Blender::BS_ALPHA);
        o.init();

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
        //////// �����ݒ� ////////
        play.init(serect_state);
        stege.init(serect_state);
        objs.init(serect_state);

        // 時間切り替えのトリガー：ここではFキーで切り替え
        f_prev = false;
       
        game_state++;
    case 6:
        //////// �ʏ펞 ////////
        play.update();
        objs.update();
        stege.re(&game_state);
        game_render();
        break;
    }

    game_timer++;
}

//--------------------------------------
// 描画処理
//--------------------------------------
void game_render()
{
  GameLib::clear(0.0, 0.0, 0.0);
  stege.render();


    play.render();
    objs.render();

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

