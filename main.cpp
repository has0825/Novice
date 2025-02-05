#include <Novice.h>
#include "Enemy.h"
#include <vector>
#include <string>

const char kWindowTitle[] = "LC1A16シミズグチ＿ハル";

struct Player {
    int x, y;
};

struct Bullet {
    int x, y;
    bool isActive;
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    Novice::Initialize(kWindowTitle, 1280, 720);

    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    Player player = { 640, 600 };
    std::vector<Bullet> bullets;
    std::vector<Enemy> enemies = {
        Enemy(100, 300, 5, 20, 1260),
        Enemy(500, 400, 5, 20, 1260)
    };

    while (Novice::ProcessMessage() == 0) {
        Novice::BeginFrame();
        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        if (keys[DIK_W]) player.y -= 5;
        if (keys[DIK_S]) player.y += 5;
        if (keys[DIK_A]) player.x -= 5;
        if (keys[DIK_D]) player.x += 5;

        if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0) {
            bullets.push_back({ player.x, player.y - 20, true });
        }

        for (auto& bullet : bullets) {
            if (bullet.isActive) {
                bullet.y -= 10;
                if (bullet.y < 0) {
                    bullet.isActive = false;
                }
            }
        }

        for (auto& enemy : enemies) {
            enemy.Update();
        }

        for (auto& bullet : bullets) {
            if (bullet.isActive) {
                for (auto& enemy : enemies) {
                    enemy.CheckCollision(bullet.x, bullet.y);
                    if (Enemy::allEnemiesDefeated) {
                        bullet.isActive = false;
                        break;
                    }
                }
            }
        }

        // Rキーで敵をリスポーン
        if (preKeys[DIK_R] == 0 && keys[DIK_R] != 0) {
            Enemy::ResetEnemies();
        }

        Novice::DrawEllipse(player.x, player.y, 32, 32, 0.0f, 0x00FF00FF, kFillModeSolid);

        for (auto& bullet : bullets) {
            if (bullet.isActive) {
                Novice::DrawEllipse(bullet.x, bullet.y, 10, 10, 0.0f, 0xFFFFFFFF, kFillModeSolid);
            }
        }

        for (auto& enemy : enemies) {
            enemy.Draw();
        }

        std::string enemyStatus = "All Enemies Defeated: " + std::to_string(Enemy::allEnemiesDefeated);
        Novice::ScreenPrintf(10, 10, enemyStatus.c_str(), 0xFFFFFFFF);

        Novice::ScreenPrintf(10, 30, "WASD : Move", 0xFFFFFFFF);
        Novice::ScreenPrintf(10, 50, "SPACE : Shoot", 0xFFFFFFFF);
        Novice::ScreenPrintf(10, 70, "R : Respawn Enemies", 0xFFFFFFFF);

        Novice::EndFrame();

        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
            break;
        }
    }

    Novice::Finalize();
    return 0;
}
