#include <thread>
#include <chrono>
#include <iostream>
#include "Game.h"

int main() {
    Game game{};

 /*   std::chrono::milliseconds timespan(3000);
    std::this_thread::sleep_for(timespan);
    
    game.CalculateDeltaTime();
    game.ResetTime();*/

    while (game.IsRunning()) {
        game.CaptureInput();
        game.Update();
        game.LateUpdate();
        game.Draw();
        game.CalculateDeltaTime();
    }
}
