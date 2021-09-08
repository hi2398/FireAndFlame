#include <cstdlib>
#include <memory>
#include <iostream>

#include "raylib.h"

#include "Global.h"
#include "config.h"
#include "helper.h"
#include "Scenes/Endscreen.h"
#include "Scenes/Tutorial.h"
#include "Scenes/MainMenu.h"
#include "Scenes/NeutralArea.h"
#include "Scenes/FinalBoss.h"
#include "Scenes/AreaThree.h"
#include "Scenes/TraitorBossScene.h"
#include "Scenes/IceBossScene.h"
#include "Scenes/AreaOne.h"
#include "Scenes/AreaTwo.h"
#include "Scenes/MinerBossScene.h"


std::shared_ptr<PlayerCharacter> playerCharacter;
std::shared_ptr<PlayerController> playerController;
std::shared_ptr<HUD> hud;
std::shared_ptr<SceneManager> sceneManager;
std::shared_ptr<SoundManager> soundManager;


int main() {
if  constexpr(DEBUG_BUILD){
    std::cout << "\n=============================\n";
    std::cout << "\n=====DEBUG BUILD ENABLED=====\n";
    std::cout << "\n=============================\n";
}

    // Enable config flags for resizable window and vertical synchro
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
    InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);
    Image windowIcon= LoadImage("assets/graphics/flame.png");
    SetWindowIcon(windowIcon);
    SetWindowMinSize(Game::ScreenWidth / 2, Game::ScreenHeight / 2);
    // Set game to run at 60 frames-per-second
    SetTargetFPS(60);

    // Render texture initialization, used to hold the rendering result so we can easily resize it
    RenderTexture2D target = LoadRenderTexture(Game::ScreenWidth, Game::ScreenHeight);
    // Texture scale filter to use
    SetTextureFilter(target.texture, TEXTURE_FILTER_ANISOTROPIC_16X);
    //Init Audio
    InitAudioDevice();
    SetAudioStreamBufferSizeDefault(8192);

	playerCharacter = std::make_shared<PlayerCharacter>();
	playerController = std::make_shared<PlayerController>();
    hud = std::make_shared<HUD>();
    soundManager = std::make_shared<SoundManager>();


	sceneManager = std::make_shared<SceneManager>(std::make_unique<MainMenu>(SceneEnums::Default));



#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif


    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Compute required framebuffer scaling
        float scale = MIN((float) GetScreenWidth() / Game::ScreenWidth, (float) GetScreenHeight() / Game::ScreenHeight);
        // Update virtual mouse (clamped mouse value behind game screen)
        Vector2 mouse = GetMousePosition();
        Vector2 virtualMouse = {0};
        virtualMouse.x =
                (mouse.x - (static_cast<float>(GetScreenWidth()) - (Game::ScreenWidth * scale)) * 0.5f) / scale;
        virtualMouse.y =
                (mouse.y - (static_cast<float>(GetScreenHeight()) - (Game::ScreenHeight * scale)) * 0.5f) / scale;
        virtualMouse = ClampValue(virtualMouse, {0, 0}, {static_cast<float>(Game::ScreenWidth),
                                                         static_cast<float>(Game::ScreenHeight)});
        sceneManager->Update(virtualMouse);

        BeginDrawing();

        ClearBackground(BLACK); // Letterbox color

        // Draw everything in the render texture, note this will not be rendered on screen, yet
        BeginTextureMode(target);
        ClearBackground(BLACK);

        sceneManager->Draw();
		
        EndTextureMode();

        // Draw RenderTexture2D to window, properly scaled
        DrawTexturePro(target.texture,
                       {0.0f, 0.0f, (float) target.texture.width, (float) -target.texture.height},
                       {(static_cast<float>(GetScreenWidth()) - ((float) Game::ScreenWidth * scale)) * 0.5f,
                        (static_cast<float>(GetScreenHeight()) - ((float) Game::ScreenHeight * scale)) * 0.5f,
                        (float) Game::ScreenWidth * scale, (float) Game::ScreenHeight * scale},
                       {0, 0}, 0.0f, WHITE);

        EndDrawing();
    } // Main game loop end

    // De-Initialization here...
    CloseAudioDevice();
    // Unload render texture
    UnloadRenderTexture(target);

    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}