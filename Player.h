#pragma once
#include "PlayerBullet.h"
#include"Input.h"
#include<list>

///< summary>
/// 自キャラ
///</summary>
class Player {
public:
	///< summary>
	/// 初期化
	///</summary>
	//デストラクタ
	~Player();
	
	/// 
	///< param name="model">モデル</param>
	///< param name="textureHandle">テクスチャハンドル</param>
	void Initialize(Model* model, uint32_t textureHandle);


	///< summary>
	/// 更新
	///</summary>
	void Updete();

	void Attack();

	
	///< summary>
	/// 描画
	///</summary>
	void Draw(ViewProjection& viewProjection);

private:
	// 弾
	std::list<PlayerBullet*> bullets_;
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// キーボード入力
	Input* input_ = nullptr;
};