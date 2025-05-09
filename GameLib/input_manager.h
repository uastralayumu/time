#ifndef INCLUDED_INPUT_MANAGER
#define INCLUDED_INPUT_MANAGER

#include <Windows.h>
#include "./DirectXTK-master/Inc/Keyboard.h"
#include "./DirectXTK-master/Inc/GamePad.h"

namespace GameLib
{
    namespace input
    {
        const int PAD_UP = (1 << 0);
        const int PAD_DOWN = (1 << 1);
        const int PAD_LEFT = (1 << 2);
        const int PAD_RIGHT = (1 << 3);
        const int PAD_START = (1 << 4);
        const int PAD_TRG1 = (1 << 5);
        const int PAD_TRG2 = (1 << 6);
        const int PAD_TRG3 = (1 << 7);
        const int PAD_SELECT = (1 << 8);
        const int PAD_TRG4 = (1 << 9);
        const int PAD_L1 = (1 << 10);
        const int PAD_R1 = (1 << 11);
        const int PAD_L2 = (1 << 12);
        const int PAD_R2 = (1 << 13);
        const int PAD_L3 = (1 << 14);
        const int PAD_R3 = (1 << 15);

        const int GAMEPAD_NUM = 4;

        enum GamePad {
            UP = 0, DOWN, RIGHT, LEFT,
            A = 4, B, X, Y,
            LSTICK, RSTICK,
            LSHOULDER, RSHOULDER,
            BACK, START
        };
    }

    struct PadAssign {
        int bit;
        int code;
    };

    class PadState {
    public:
        int state = 0;
        int trigger = 0;
        int triggerUp = 0;
        int repeat = 0;
        int old[8] = {};
        float leftX = 0.0f, leftY = 0.0f;
        float rightX = 0.0f, rightY = 0.0f;
        float left = 0.0f, right = 0.0f;
        PadAssign* keyAssign = nullptr;
        PadAssign* joyAssign = nullptr;
    };

    class InputManager {
    private:
        DirectX::Keyboard* keyboard = nullptr;  // シングルトン参照
        DirectX::GamePad* gamePad = nullptr;

        PadState pad[input::GAMEPAD_NUM] = {};
        POINT mousePos = {};

        void setKeyAssign(int no, PadAssign* data);
        void setJoyAssign(int no, PadAssign* data);

    public:
        InputManager() = default;
        ~InputManager() = default;

        void init(HWND hwnd);       // HWND を受け取るように変更
        void update(HWND hwnd);     // 入力更新

        PadState* getPadAddress() { return pad; }
        int getCursorPosX();
        int getCursorPosY();
    };
}

#endif
