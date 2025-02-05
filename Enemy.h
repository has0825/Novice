#pragma once

class Enemy {
public:
    int x, y;       // 敵の座標
    int speed;      // 移動速度
    int direction;  // 移動方向（1: 右, -1: 左）
    int leftLimit;  // 左の限界
    int rightLimit; // 右の限界

    static bool allEnemiesDefeated; // 全ての敵が倒れたか

    Enemy(int startX, int startY, int moveSpeed, int leftLimit, int rightLimit);
    void Update();
    void Draw();
    void CheckCollision(int bulletX, int bulletY);
    static void ResetEnemies(); // 敵をリスポーンさせる
};
