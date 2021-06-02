#include "NeutralArea.h"

void NeutralArea::Update() {


    for (const auto& x: enemies) {
    x->Update();
    }
}

void NeutralArea::Draw() {
    for (const auto& x: enemies) {
        x->Draw();
    }
}

NeutralArea::NeutralArea() {

}
