#include "Model.h"
#include "WorldTransform.h"
///自キャラの弾

class PlayerBullet {
public:
	
	/// <summary>
	/// 
	/// </summary>
	/// <param name="model"></param>
	/// <param name="position">初期座標</param>
	void Initialize(Model* model, const Vector3& position);

	/// 更新
	void Update();
	
	/// 描画
	void Draw(const ViewProjection& viewProjection);;

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;



};






