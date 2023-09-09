#include "GameScene.h"


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
	mainCamera->SetEye({ -5,-5,5 });
	mainCamera->SetTarget({ -5,-2,10 });
	mainCamera->Update();
	ParticleManager::SetCamera(mainCamera);
	Object3d::SetCamera(mainCamera);
	FBXObject3d::SetCamera(mainCamera);

	skydomeMD = Model::LoadFromOBJ("skydome");
	skydome = Object3d::Create();
	skydome->SetModel(skydomeMD);
	skydome->wtf.scale = (Vector3{ 1000, 1000, 1000 });

	//プレイヤー
	spriteCommon->LoadTexture(0, "hill.png");
	spriteCommon->LoadTexture(1, "hihill.png");

	p = Model::LoadFromOBJ("Particle");
	playerMD = Model::LoadFromOBJ("ster");
	player_ = new Player();
	player_->Initialize(dxCommon, playerMD,input);
	player_->SetCamera(mainCamera);

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			obj[i][j] = new Object3d();
			obj[i][j]->SetModel(p);
			obj[i][j]->Initialize();
			obj[i][j]->wtf.scale = {0.1f,0.1f,0.1f};
		}
	}
	
}

void GameScene::Reset() {
	
}

/// <summary>
/// 毎フレーム処理
/// </summary>
void GameScene::Update() {

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++){
			obj[i][j]->wtf.position = { ((float)i - 6.0f) * 1.0f, (5.0f - (float)j) * 1.0f,15.0f };
			obj[i][j]->Update();
		}
	}
	player_->Update();

	skydome->Update();
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
			obj[i][j]->Draw();
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