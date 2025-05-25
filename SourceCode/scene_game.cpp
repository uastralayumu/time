//******************************************************************************
//
//      scene_game.cpp
//
//******************************************************************************

#include "all.h"
#include <sstream>

#include <cmath>  // 距離計算に使用

using namespace DirectX;
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


//------< 定数 >----------------------------------------------------------------
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

bool show_ui_icon = false;
bool show_ui_menu = false;
TimeOfDay current_time = MORNING;

// UIスプライト（仮）
Sprite* plant;
Sprite* ui_icon;
Sprite* ui_menu;

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


int game_title = 0;
int serect_state = 0;

//------< 変数 >----------------------------------------------------------------

int game_state = 0;    // 状態
int game_timer = 0;    // タイマー

//--------------------------------------
// 初期設定
//--------------------------------------
void game_init()
{

    serect_state = 0;
    game_title = 0;

    game_state = 0;
    game_timer = 0;
    plant_growth = 0;
    fertilizer_amount = 0;
    herbicide_amount = 0;
    current_time = MORNING;
    
    
}

//--------------------------------------
// 散布UIの処理
//--------------------------------------
void handle_spraying_ui()
{
    // プレイヤーと植物の距離を計算
    float dx = player_x - plant_x;
    float dy = player_y - plant_y;
    float dist = std::sqrt(dx * dx + dy * dy);

    // プレイヤーが近づいたら UI アイコンを表示
    show_ui_icon = (dist < UI_DISTANCE_THRESHOLD);

    // UI アイコンが表示されていてクリックされたらメニューを表示（ここは仮処理）
    if (show_ui_icon && mouseTracker.leftButton == Mouse::ButtonStateTracker::PRESSED) {
        show_ui_menu = true;
    }

    // メニューが表示されている間に肥料/除草剤量を決定（ここでは仮に数値を固定）
    if (show_ui_menu) {
        fertilizer_amount = 2; // 仮の入力
        herbicide_amount = 1;  // 仮の入力
        show_ui_menu = false;  // 入力後は閉じる
    }
}

//--------------------------------------
// 朝 → 夜の切り替えと成長処理
//--------------------------------------
void update_growth_logic()
{
    if (current_time == NIGHT) {
        // 肥料による成長処理
        plant_growth += fertilizer_amount;
        if (plant_growth > PLANT_GROWTH_MAX) plant_growth = PLANT_GROWTH_MAX;

        // 除草剤による減少処理
        plant_growth -= herbicide_amount;
        if (plant_growth < PLANT_GROWTH_MIN) plant_growth = PLANT_GROWTH_MIN;

        // リセット
        fertilizer_amount = 0;
        herbicide_amount = 0;

        // 次は朝
        current_time = MORNING;
    }


	game_state = 0;
	game_timer = 0;

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
        plant = sprite_load(L"./Data/Images/plant_kari.png");
         // 散布UI処理
        handle_spraying_ui();

        // 成長・除草処理（夜）
        update_growth_logic();

        // 時間切り替えのトリガー：ここではFキーで切り替え
        f_prev = false;
       
        game_state++;
    case 6:
        //////// �ʏ펞 ////////
        play.update();
        objs.update();
        stege.re(&game_state);
        game_render();
        //stege.update();
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

    sprite_render(plant, 700, 920 - plant_growth);

    //if (show_ui_icon) {
    //    sprite_render(ui_icon, plant_x + 50, plant_y - 50); // UIマーク
    //}

    //if (show_ui_menu) {
    //    sprite_render(ui_menu, 600, 400); // 散布量選択用UI
    //}

    
   
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
    safe_delete(plant);
}

