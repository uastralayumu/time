 #include "input_manager.h"

using namespace DirectX;
using namespace GameLib;

void InputManager::init(HWND hwnd)
{
    // シングルトンの取得
    keyboard = &Keyboard::Get();
    gamePad = &GamePad::Get();

    // ウィンドウハンドルのセット（必要）
    keyboard->SetWindow(hwnd);

    // ゲームパッドの初期状態クリア
    ZeroMemory(pad, sizeof(pad));

    // キー/パッドの割り当て（あなたの定義に従って）
    setKeyAssign(0, keyAssign00);
    setJoyAssign(0, joyAssign00);
    // 他のプレイヤー分も同様に設定…
}

void InputManager::update(HWND hwnd)
{
    auto kbState = keyboard->GetState();
    auto padState = gamePad->GetState(0);

    // 入力処理（略）…
}

int InputManager::getCursorPosX()
{
    GetCursorPos(&mousePos);
    return mousePos.x;
}

int InputManager::getCursorPosY()
{
    GetCursorPos(&mousePos);
    return mousePos.y;
}
