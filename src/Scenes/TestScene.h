//
// Created by Ashty on 06.06.2021.
//

#ifndef RAYLIBSTARTER_TESTSCENE_H
#define RAYLIBSTARTER_TESTSCENE_H


class TestScene : public Scene {
public:
    TestScene();
    void Update() override;
    void Draw() override;
    ~TestScene() override = default;

protected:

private:
    std::unique_ptr<Tilemap> tilemap;
};



