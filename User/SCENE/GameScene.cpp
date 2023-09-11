#include "GameScene.h"
#include "map.h"

/// <summary>
	/// コンストクラタ
	/// </summary>
GameScene::GameScene() {
}

/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene() {
	delete spriteCommon;
	delete mainCamera;
	delete camera1;
	delete camera2;
	delete camera3;
	delete player_;
	delete skydome;
	delete skydomeMD;
}

/// <summary>
/// 初期化
/// </summary>
void GameScene::Initialize(DirectXCommon* dxCommon, Input* input) {
	// nullチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	this->input = input;

	//スプライト共通部分の初期化
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);

	// カメラ生成
	mainCamera = new Camera(WinApp::window_width, WinApp::window_height);
	camera1 = new Camera(WinApp::window_width, WinApp::window_height);
	camera2 = new Camera(WinApp::window_width, WinApp::window_height);
	camera3 = new Camera(WinApp::window_width, WinApp::window_height);
	mainCamera->SetEye({ 2.5f,-7.0f,5 });
	mainCamera->SetTarget({ 2.5f,-5.0f,10 });
	mainCamera->Update();
	ParticleManager::SetCamera(mainCamera);
	Object3d::SetCamera(mainCamera);
	FBXObject3d::SetCamera(mainCamera);

	skydomeMD = Model::LoadFromOBJ("skydome");
	skydome = Object3d::Create();
	skydome->SetModel(skydomeMD);
	skydome->wtf.scale = (Vector3{ 1000, 1000, 1000 });

	p = Model::LoadFromOBJ("Particle");
	playerMD = Model::LoadFromOBJ("ster");
	block = Model::LoadFromOBJ("WoodenBox");

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			obj[j][i] = new Object3d();
			obj[j][i]->SetModel(p);
			obj[j][i]->Initialize();
			obj[j][i]->wtf.scale = {0.1f,0.1f,0.1f};
		}
	}

	//プレイヤー
	player_ = new Player();
	player_->Initialize(dxCommon, playerMD,input);
	player_->Reset(map);
	player_->SetCamera(mainCamera);

	
}

void GameScene::Reset() {
	
}

/// <summary>
/// 毎フレーム処理
/// </summary>
void GameScene::Update() {

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++){

			//マップ更新
			if (map == 0) {
				baseMap[j][i] = tutorialMap[j][i];
			}
			else if (map == 1) {
				baseMap[j][i] = map1[j][i];
			}
			else if (map == 2) {
				baseMap[j][i] = map2[j][i];
			}

			obj[j][i]->wtf.position = { ((float)i) * 1.0f, (5.0f - (float)j) * 1.0f - 5.0f,15.0f };

			if (baseMap[j][i] == 0) {
				obj[j][i]->wtf.scale = { 0.1f,0.1f,0.1f };
				obj[j][i]->SetModel(p);
			}
			if (baseMap[j][i] == 1) {
				obj[j][i]->wtf.scale = { 0.5f,0.5f,0.5f };
				obj[j][i]->SetModel(block);

			}
			obj[j][i]->Update();
		}
	}

	player_->Update();
	skydome->Update();

	//マップ切り替え
	if (input->TriggerKey(DIK_RIGHT) && map < mapMax) {
		map++;
		player_->Reset(map);
	}
	else if (input->TriggerKey(DIK_LEFT) && map > 0) {
		map--;
		player_->Reset(map);
	}
	//位置リセット
	if (input->TriggerKey(DIK_R)) {
		player_->Reset(map);
	}
}

/// <summary>
/// 描画
/// </summary>
void GameScene::Draw() {

	/// <summary>
	/// 3Dオブジェクトの描画
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// <summary>
	//3Dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon->GetCommandList());
	//// 3Dオブクジェクトの描画
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			obj[j][i]->Draw();
		}
	}
	player_->Draw();
	//skydome->Draw();

	//3Dオブジェクト描画後処理
	Object3d::PostDraw();


	//// パーティクル UI FBX スプライト描画
	//player_->FbxDraw();
}

Vector3 GameScene::bVelocity(Vector3& velocity, Transform& worldTransform)
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