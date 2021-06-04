#include "NeutralArea.h"

void NeutralArea::Update() {


    for (const auto& x: enemies) {
    x->Update();
    }
}

void NeutralArea::Draw() {
    ClearBackground(WHITE);
    DrawRectangle(-1000, GetScreenHeight(), 2000, 300);

    for (const auto& x: enemies) {
        x->Draw();
    }
}

NeutralArea::NeutralArea() {
    
}
