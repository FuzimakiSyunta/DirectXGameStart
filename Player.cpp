#include "Player.h"
#include <cassert>
#include"ImGuiManager.h"

void Player::Initialize(Model* model, uint32_t textureHandle) {
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;

	worldTransform_.Initialize();
	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	// x,y,z方向のスケーリングを設定
	worldTransform_.scale_ = {5.0f, 5.0f, 5.0f};
	// x,y,z方向の回転を設定
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	//x,y,z方向
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
	//ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
}

void Player::Updete() {
#pragma region MyRegion

	// worldTransform_.matWorld_=
	// MakeAffineMatrix(worldTransform_.scale_,worldTransform_.rotation_,worldTransform_.translation_);
	//

	//// スケーリング行列を宣言
	// Matrix4x4 matScale; // 4行4列

	// matScale.m[0][0] = worldTransform_.scale_.x;
	// matScale.m[1][1] = worldTransform_.scale_.y;
	// matScale.m[2][2] = worldTransform_.scale_.z;
	// matScale.m[3][3] = 1;

	//

	//// x軸回転行列を宣言
	// Matrix4x4 matRotX;
	// matRotX.m[0][0] = 1;
	// matRotX.m[1][1] = cosf(worldTransform_.rotation_.x);
	// matRotX.m[2][1] = -sinf(worldTransform_.rotation_.x);
	// matRotX.m[1][2] = sinf(worldTransform_.rotation_.x);
	// matRotX.m[2][2] = cosf(worldTransform_.rotation_.x);
	// matRotX.m[3][3] = 1;

	//// y軸回転行列を宣言
	// Matrix4x4 matRotY;
	// matRotY.m[1][1] = cosf(worldTransform_.rotation_.y);
	// matRotY.m[0][0] = 1;
	// matRotY.m[2][1] = -sinf(worldTransform_.rotation_.y);
	// matRotY.m[1][2] = sinf(worldTransform_.rotation_.y);
	// matRotY.m[2][2] = cosf(worldTransform_.rotation_.y);
	// matRotY.m[3][3] = 1;

	//// z軸回転行列を宣言
	// Matrix4x4 matRotZ;
	// matRotZ.m[1][1] = cosf(worldTransform_.rotation_.z);
	// matRotZ.m[0][0] = 1;
	// matRotZ.m[2][1] = -sinf(worldTransform_.rotation_.z);
	// matRotZ.m[1][2] = sinf(worldTransform_.rotation_.z);
	// matRotZ.m[2][2] = cosf(worldTransform_.rotation_.z);
	// matRotZ.m[3][3] = 1;

	// Matrix4x4 rotateXMatrix = MakeRotateXMatrix(worldTransform_.rotation_.x);
	// Matrix4x4 rotateYMatriy = MakeRotateYMatrix(worldTransform_.rotation_.y);
	// Matrix4x4 rotateZMatriz = MakeRotateZMatrix(worldTransform_.rotation_.z);
	// Matrix4x4 m = Multiply(rotateXMatrix, Multiply(rotateYMatriy, rotateZMatriz));

	////平行移動行列を宣言
	// Matrix4x4 matTrans;

	// matTrans.m[0][0] = 1;
	// matTrans.m[1][1] = 1;
	// matTrans.m[2][2] = 1;
	// matTrans.m[3][3] = 1;
	// matTrans.m[3][0] = worldTransform_.translation_.x;
	// matTrans.m[3][1] = worldTransform_.translation_.y;
	// matTrans.m[3][2] = worldTransform_.translation_.z;

	////worldTransform_.matWorld_ = Multiply(matScale, Multiply(m, matTrans));
	// Matrix4x4 worldMatrix =
	// MakeAffineMatrix(worldTransform_.scale_,worldTransform_.rotation_,worldTransform_.translation_);

	//// 行列の転送 行列の計算後に行う
	// worldTransform_.TransferMatrix();

	// worldTransform_.matWorld_;

	////1]worldTransform_.matWorld_ = worldTransform_.scale_ * worldTransform_.rotation_ *
	///worldTransform_.matWorld_;

	//// 行列を定数バッファに転送
	// worldTransform_.TransferMatrix();
#pragma endregion


	// キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};


	// キャラクターの移動速さ
	const float kCaracterSpeed = 0.3f;


	// 押した方向で移動ベクトルを変更(左右)
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCaracterSpeed;
		
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCaracterSpeed;
	}
	// 移動した方向で移動ベクトルを変更(上下)
	if (input_->PushKey(DIK_UP)) {
		move.y += kCaracterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCaracterSpeed;
	}
	// キャラクターの回転速さ
	const float KRotspeed = 0.02f;
	//回転
	if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y += KRotspeed;
	} else if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= KRotspeed;
	}
	
	if (input_->PushKey(DIK_S)) {
		worldTransform_.rotation_.x+= KRotspeed;
	} else if (input_->PushKey(DIK_W)) {
		worldTransform_.rotation_.x -= KRotspeed;
	}
	

	//移動限界座標
	const float kMoveLimitX = 30;
	const float kMoveLimitY = 16;
	//範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x,-kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitX);



	// 座標移動(ベクトルの加算)
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);
	
	// ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();

		// ImGuiで値を入力する変数
	float inputFloat3[3] = {
	    worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z};

	float PlayerPos[3] = {
	    worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z};

	// キャラの攻撃
	Attack();
	// 弾更新
	if (bullet_) {
		bullet_->Update();
	}


	//キャラクターの座標を画面表示する処理
	ImGui::Begin("Debug1");
	//float3入力ボックス
	ImGui::InputFloat3("InputFloat3", inputFloat3);
	// float3スライダー
	ImGui::SliderFloat3("SliderFloat3", PlayerPos, -30.0f, 30.0f);
	
	ImGui::End();

	worldTransform_.translation_.x = PlayerPos[0];
	worldTransform_.translation_.y = PlayerPos[1];
	worldTransform_.translation_.z = PlayerPos[2];


	
}
void Player::Attack()
{
	if (input_->PushKey(DIK_SPACE)) {
		//弾を生成、初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldTransform_.translation_);
		//弾を登録する
		bullet_ = newBullet;
	}
}
             


void Player::Draw(ViewProjection& viewProjection) {
	
	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	// 弾描画
	if (bullet_) {
		bullet_->Draw(viewProjection);
	}     
}
