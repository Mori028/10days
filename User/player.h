#pragma once
#include "DirectXCommon.h"
#include "Object3d.h"
#include "Input.h"
#include "Sprite.h"
#include "Camera.h"

#include "ParticleManager.h"
#include "Audio.h"
#include "FBXModel.h"
#include "FbxLoader.h"
#include "FBXObject3d.h"


class Player {
public:
	//向き
	enum Direction {
		Left,
		Right,
		Up,
		Down,
	};

	Player();
	~Player();

	void Initialize(DirectXCommon* dxCommon,Model* model, Input* input);
	void Reset(int map);
	void Update();

	void Draw();
	void FbxDraw();

	Vector3 bVelocity(Vector3& velocity, Transform& worldTransform);

	////ワールド座標を取得
	Vector3 GetWorldPosition();

	float GetFrame() { return frame; }

	/// <summary>
	/// ポジション
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(Vector3 pos) {fbxObject3d_->wtf.position = pos; };
	void SetCamera(Camera* cam) { camera = cam; };

	//イージング
	float easeOutCubic(float x) {
		return 1 - (float)pow(1 - x, 3);
	}

	Vector2 GatPlace() { return place; }
public:
	//音を止める関数
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };

private:
	const float PI = 3.141592f;
	Input* input_ = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Audio* audio = nullptr;
	SpriteCommon* spriteCommon_ = nullptr;
	//待機
	FBXModel* fbxModel_ = nullptr;
	FBXObject3d* fbxObject3d_ = nullptr;
	
	const float moveSpeed_ = 0.1f;
	const float rotaSpeed_ = 0.1f;

	Camera* camera = nullptr;
	Transform* camTransForm = nullptr;
	Vector3 targetPos;
	Vector3 eyePos;
	Vector3 centerPos;
	float targetTheta;
	float targetDistance = 10;
	float camMoveSpeed = 0.2f;
  
	Vector2 camRotaSpeed = { PI / 1800, PI / 1800};


	//ワールド座標を入れる変数
	Vector3 worldPos = {0.0f, 0.0f, 15.0f };

	Object3d* object = nullptr;
	Model* model_ = nullptr;
	Sprite* sprite = nullptr;
	Vector3 position = worldPos;

	//イージング用フレーム
	float maxframe = 60.0f;
	float frame = maxframe;
	float oneframe = 4.0f;

	//向き
	Direction direction = Direction::Up;
	//移動量
	float moveVal = 1.0f;
	//現在のマス
	Vector2 place = { 0,0 };
	
};