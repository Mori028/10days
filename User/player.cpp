#include"player.h"

Player::Player() {

}

Player::~Player() {

	//FBXオブジェクト解放
	delete fbxObject3d_;
	delete fbxModel_;
}

void Player::Initialize(DirectXCommon* dxCommon, Model* model, Input* input) {
	// nullptrチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	input_ = input;
	camTransForm = new Transform();
	model_ = model;
	fbxModel_ = FbxLoader::GetInstance()->LoadModelFromFile("stand");
	
	// デバイスをセット
	FBXObject3d::SetDevice(dxCommon->GetDevice());
	// グラフィックスパイプライン生成
	FBXObject3d::CreateGraphicsPipeline();

	//待機
	fbxObject3d_ = new FBXObject3d;
	fbxObject3d_->Initialize();
	fbxObject3d_->SetModel(fbxModel_);
	fbxObject3d_->wtf.position = { 0.0f,-0.3f,0.0f };
	fbxObject3d_->wtf.scale = { 0.1f,0.1f,0.1f };
	fbxObject3d_->PlayAnimation(1.0f,true);

	object = new Object3d();
	object->Initialize();
	object->SetModel(model_);
	object->wtf.position = worldPos;
	object->wtf.scale = { 1.0f,1.0f,1.0f };
}

void Player::Update() {
	//イージング用フレーム
	if (frame < maxframe) {
		frame += oneframe;
	}
	else {
		frame = maxframe;
	}

	//キー入力で移動
	if (frame >= maxframe) {
		if (input_->PushKey(DIK_A)) {
			direction = Direction::Left;
			frame = 0;
			worldPos.x -= moveVal;
		}
		else if (input_->PushKey(DIK_D)) {
			direction = Direction::Right;
			frame = 0;
			worldPos.x += moveVal;
		}

		else if (input_->PushKey(DIK_W)) {
			direction = Direction::Up;
			frame = 0;
			worldPos.y += moveVal;
		}
		else if (input_->PushKey(DIK_S)) {
			direction = Direction::Down;
			frame = 0;
			worldPos.y -= moveVal;
		}
	}

	//移動にイージングを掛ける
	if (direction == Direction::Left) {
		position.x = worldPos.x + moveVal - easeOutCubic(frame / maxframe) * moveVal;
	}
	else if(direction == Direction::Right) {
		position.x = worldPos.x - moveVal + easeOutCubic(frame / maxframe) * moveVal;
	}
	else if (direction == Direction::Up) {
		position.y = worldPos.y - moveVal + easeOutCubic(frame / maxframe) * moveVal;
	}
	else if (direction == Direction::Down) {
		position.y = worldPos.y + moveVal - easeOutCubic(frame / maxframe) * moveVal;
	}

	//fbxObject3d_->Update();
	object->wtf.position = position;
	object->Update();
}

void Player::Draw() {
	//sprite->Draw();
	object->Draw();
	
}

void Player::FbxDraw(){
	
	//fbxObject3d_->Draw(dxCommon->GetCommandList());
}

Vector3 Player::bVelocity(Vector3& velocity, Transform& worldTransform)
{
	Vector3 result = { 0,0,0 };

	//内積
	result.z = velocity.x * worldTransform.matWorld.m[0][2] +
		velocity.y * worldTransform.matWorld.m[1][2] +
		velocity.z * worldTransform.matWorld.m[2][2];

	result.x = velocity.x * worldTransform.matWorld.m[0][0] +
		velocity.y * worldTransform.matWorld.m[1][0] +
		velocity.z * worldTransform.matWorld.m[2][0];

	result.y = velocity.x * worldTransform.matWorld.m[0][1] +
		velocity.y * worldTransform.matWorld.m[1][1] +
		velocity.z * worldTransform.matWorld.m[2][1];

	return result;
}

Vector3 Player::GetWorldPosition(){
	fbxObject3d_->wtf.UpdateMat();
	//ワールド行列の平行移動成分
	worldPos.x = fbxObject3d_->wtf.matWorld.m[3][0];
	worldPos.y = fbxObject3d_->wtf.matWorld.m[3][1];
	worldPos.z = fbxObject3d_->wtf.matWorld.m[3][2];

	return worldPos;
}

