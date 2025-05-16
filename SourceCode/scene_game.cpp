//******************************************************************************
//
//
//      scene_game
//
//
//******************************************************************************

//----< インクルード >-----------------------------------------------------------
#include "all.h"
#include <sstream>
#include <memory>
#include <sstream>

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "player.h"
#include"map.h"
#include "obj.h"

//------< 定数 >----------------------------------------------------------------

extern player play;
extern maps stege;
extern obj objs;
//------< 変数 >----------------------------------------------------------------

int game_state = 0;    // 状態
int game_timer = 0;    // タイマー



//--------------------------------------
//  初期設定
//--------------------------------------
void game_init()
{

	game_state = 0;
	game_timer = 0;
}

//--------------------------------------
//  更新処理
//--------------------------------------
void game_update()
{
    using namespace input;

    switch (game_state)
    {
    case 0:
        //////// 初期設定 ////////
        play.init();
        stege.init();
        objs.init();
       
        game_state++;
    case 1:
        //////// パラメータの設定 ////////
        GameLib::setBlendMode(Blender::BS_ALPHA);

        game_state++;
        /*fallthrough*/
    case 2:
        //////// 通常時 ////////
        play.update();
        objs.update();
        //stege.update();
        break;
    }

    game_timer++;
}

//--------------------------------------
//  描画処理
//--------------------------------------
void game_render()
{
    GameLib::clear(0.0, 0.0, 0.0);
    stege.render();
    play.render();
    objs.render();
}

//--------------------------------------
//  終了処理
//--------------------------------------
void game_deinit()
{
    
}

