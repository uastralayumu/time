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
int game_state = 0;
int game_timer = 0;
int plant_growth = 0;



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
//------< 変数 >----------------------------------------------------------------





//--------------------------------------
// 初期設定
//--------------------------------------
void game_init()
{

    game_state = 0;
    game_timer = 0;
    plant_growth = 0;
    
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
       /* plant = sprite_load(L"./Data/Images/plant_kari.png");*/
        
        //////// 初期設定 ////////
        play.init();
        stege.init();
        objs.init();
       
        game_state++;
    case 1:
        //////// パラメータの設定 ////////

        GameLib::setBlendMode(Blender::BS_ALPHA);
        game_state++;

      
    case 2:
        //////// 通常時 ////////
        play.update();
        objs.update();
        

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
//sprite_render(plant, 700, 920 - plant_growth) ;
    play.render();
    objs.render();

}

//--------------------------------------
// 終了処理
//--------------------------------------
void game_deinit()
{
   
    //safe_delete(plant);
    
}

