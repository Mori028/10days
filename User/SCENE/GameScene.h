#pragma once

#include "DirectXCommon.h"
#include "Input.h"
#include "Audio.h"
#include <string>
#include "Object3d.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "Model.h"

#include "Matrix4.h"
#include "Camera.h"

#include "ParticleManager.h"
#include"Player.h"
#include "ElementManager.h"
#include <Title.h>


/// <summary>
/// ゲームシーン
/// </summary>
class GameScene
{
private: // 静的メンバ変数
	//static const int debugTextTexNumber = 0;

public: // メンバ関数

	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, Input* input);

	void Reset();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	Vector3 bVelocity(Vector3& velocity, Transform& worldTransform);

public:
	//音を止める関数
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };


private: // メンバ変数 (固定)
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;

	SpriteCommon* spriteCommon = nullptr;
	Audio* audio = nullptr;


private:	//メンバ変数
	const float PI = 3.141592f;

	//シーン切り替え
	enum class SceneNo {
		TITLE, //タイトル
		GAME, //ゲームシーン
	};
	//ゲーム制作中はgameシーンにする
	SceneNo sceneNo_ = SceneNo::TITLE;

	Sprite* wakuSprite = new Sprite();

	Sprite* setumeiSprite = new Sprite();

	Sprite* titleSprite = new Sprite();

	Sprite* HHSprite = new Sprite();

	Sprite* stage1Sprite = new Sprite();

	//カメラ
	Camera* mainCamera = nullptr;
	Camera* camera1 = nullptr;
	Camera* camera2 = nullptr;
	Camera* camera3 = nullptr;

	//プレイヤー
	Player* player_ = nullptr;

	//タイトル
	Title* title_ = nullptr;

	//背景や床
	Object3d* skydome = nullptr;
	Model* skydomeMD = nullptr;
	
	Object3d* obj[6][6];
	Model* playerMD = nullptr;
	Model* block = nullptr;
	Model* p = nullptr;
	//UI

	//ゲームフロー

	int map = 0;
	ElementManager* elementMna = nullptr;
};