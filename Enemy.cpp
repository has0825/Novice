#include "Enemy.h"
#include <Novice.h>

// 静的メンバ変数の初期化
bool Enemy::allEnemiesDefeated = false;

Enemy::Enemy(int startX, int startY, int moveSpeed, int leftLimit, int rightLimit)
    : x(startX), y(startY), speed(moveSpeed), direction(1),
    leftLimit(leftLimit), rightLimit(rightLimit) {
}

void Enemy::Update() {
    if (allEnemiesDefeated) {
        return; // 全滅時は移動しない
    }

    // 左右に移動
    x += speed * direction;

    // 方向転換の条件を修正
    if (x <= leftLimit && direction == -1) {
        direction = 1; // 左端にいる時、左へ進もうとした場合のみ右へ
        x = leftLimit; // 境界を超えたら補正
    }
    if (x >= rightLimit && direction == 1) {
        direction = -1; // 右端にいる時、右へ進もうとした場合のみ左へ
        x = rightLimit; // 境界を超えたら補正
    }
}

void Enemy::Draw() {
    if (!allEnemiesDefeated) {
        Novice::DrawEllipse(x, y, 20, 20, 0.0f, 0xFF0000FF, kFillModeSolid);
    }
}

void Enemy::CheckCollision(int bulletX, int bulletY) {
    if (allEnemiesDefeated) {
        return;
    }

    // 簡易的な当たり判定（円同士）
    int dx = x - bulletX;
    int dy = y - bulletY;
    if (dx * dx + dy * dy <= 400) {
        allEnemiesDefeated = true;
    }
}

void Enemy::ResetEnemies() {
    allEnemiesDefeated = false;
}
