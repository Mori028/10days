#include"player.h"
#include "map.h"

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

void Player::Reset(int map) {

	//マップ更新
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (map == 0) {
				place = { 0,2 };
				baseMap[j][i] = tutorialMap[j][i];
			}
			else if (map == 1) {
				place = { 1,3 };
				baseMap[j][i] = map1[j][i];
			}
			else if (map == 2) {
				place = { 1,3 };
				baseMap[j][i] = map2[j][i];
			}
		}
	}

	worldPos.x = (float)place.x;
	worldPos.y = -(float)place.y;
	position.x = worldPos.x + moveVal - easeOutCubic(frame / maxframe) * moveVal;
	position.y = worldPos.y + moveVal - easeOutCubic(frame / maxframe) * moveVal;
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

		if (input_->PushKey(DIK_A) && place.x > 0) {
			if (baseMap[(int)place.y][(int)place.x - 1] == 0) {
				direction = Direction::Left;
				worldPos.x -= moveVal;
				place.x--;
				frame = 0;
			}
		}
		else if (input_->PushKey(DIK_D) && place.x < 5) {
			if (baseMap[(int)place.y][(int)place.x + 1] == 0) {
				direction = Direction::Right;
				worldPos.x += moveVal;
				place.x++;
				frame = 0;
			}
		}

		else if (input_->PushKey(DIK_W) && place.y > 0) {
			if (baseMap[(int)place.y - 1][(int)place.x] == 0) {
				direction = Direction::Up;
				worldPos.y += moveVal;
				place.y--;
				frame = 0;
			}
		}
		else if (input_->PushKey(DIK_S) && place.y < 5) {
			if (baseMap[(int)place.y + 1][(int)place.x] == 0) {
				direction = Direction::Down;
				worldPos.y -= moveVal;
				place.y++;
				frame = 0;
			}
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

	Vector3 pos;
	//ワールド行列の平行移動成分
	pos = object->wtf.position;

	return pos;
}

