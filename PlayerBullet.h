﻿#include "Model.h"
#include "WorldTransform.h"
///自キャラの弾

class PlayerBullet {
public:
	
	/// <summary>
	/// 
	/// </summary>
	/// <param name="model"></param>
	/// <param name="position">初期座標</param>
	void Initialize(Model* model, const Vector3& position,const Vector3& velocity);

	/// 更新
	void Update();
	
	/// 描画
	void Draw(const ViewProjection& viewProjection);

	bool IsDead() const { return isDead_; }

private:
	//速度
	Vector3 velocity_;
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//寿命
	static const int32_t kLifeTime = 60 * 5;
	//デスタイマー
	int32_t deathTimer_ = kLifeTime;
	//デスフラグ
	bool isDead_ = false;
	
};






