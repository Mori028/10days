#pragma once
#include "DirectXCommon.h"
#include "Object3d.h"
#include "Input.h"
#include "Camera.h"


class Title {
public:
	Title();
	~Title();

	void Initialize(DirectXCommon* dxCommon, Input* input);
	void Update();

	void Draw();

	Vector3 bVelocity(Vector3& velocity, Transform& worldTransform);

	////ワールド座標を取得
	Vector3 GetWorldPosition();

	/// <summary>
	/// ポジション
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(Vector3 pos) { HObj_->wtf.position = pos; };
	void SetCamera(Camera* cam) { camera = cam; };

private:
	const float PI = 3.141592f;
	Input* input_ = nullptr;
	DirectXCommon* dxCommon = nullptr;

	Object3d* HObj_ = nullptr;
	Model* HModel_ = nullptr;
	const float moveSpeed_ = 0.03f;
	const float rotaSpeed_ = 0.1f;

	Camera* camera = nullptr;
	Transform* camTransForm = nullptr;
	Vector3 targetPos;
	Vector3 eyePos;
	Vector3 centerPos;
	float targetTheta;
	float targetDistance = 10;
	float camMoveSpeed = 0.2f;

	Vector2 camRotaSpeed = { PI / 1800, PI / 1800 };


	//ワールド座標を入れる変数
	Vector3 worldPos;

};