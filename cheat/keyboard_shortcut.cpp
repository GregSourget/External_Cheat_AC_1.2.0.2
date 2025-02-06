#include "cheat.h"
#include <Windows.h>
#include <iostream>
#include <thread>

void listenForHotkeys() {
    while (true) {
        if (GetAsyncKeyState('A') & 0x8000) {
            if (cheat::isAimBotOn) {
                cheat::aimbotoff();
            }
            else {
                cheat::aimboton();
            }

            while (GetAsyncKeyState('A') & 0x8000) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

int main() {
    std::thread hotkeyThread(listenForHotkeys);
    hotkeyThread.detach();

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
