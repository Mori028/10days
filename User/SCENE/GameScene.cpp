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
	//外枠
	wakuSprite->Initialize(spriteCommon);
	wakuSprite->SetPozition({ 0,0 });
	wakuSprite->SetSize({ 1280.0f, 720.0f });
	spriteCommon->LoadTexture(3, "back.png");
	wakuSprite->SetTextureIndex(3);
	//ゲームルール説明
	setumeiSprite->Initialize(spriteCommon);
	setumeiSprite->SetPozition({ 0,0 });
	setumeiSprite->SetSize({ 320.0f, 680.0f });
	spriteCommon->LoadTexture(4, "setumei.png");
	setumeiSprite->SetTextureIndex(4);
	//タイトル
	titleSprite->Initialize(spriteCommon);
	titleSprite->SetPozition({ 0,0 });
	titleSprite->SetSize({ 1280.0f, 720.0f });
	spriteCommon->LoadTexture(5, "Title.png");
	titleSprite->SetTextureIndex(5);

	HHSprite->Initialize(spriteCommon);
	HHSprite->SetPozition({ 650,600 });
	HHSprite->SetSize({ 300.0f, 100.0f });
	spriteCommon->LoadTexture(6, "HH.png");
	HHSprite->SetTextureIndex(6);
	
	stage1Sprite->Initialize(spriteCommon);
	stage1Sprite->SetPozition({ 350,50 });
	stage1Sprite->SetSize({ 100.0f, 400.0f });
	spriteCommon->LoadTexture(7, "stage1.png");
	stage1Sprite->SetTextureIndex(7);
	// カメラ生成
	mainCamera = new Camera(WinApp::window_width, WinApp::window_height);
	camera1 = new Camera(WinApp::window_width, WinApp::window_height);
	camera2 = new Camera(WinApp::window_width, WinApp::window_height);
	camera3 = new Camera(WinApp::window_width, WinApp::window_height);
	
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
	player_->Initialize(dxCommon, playerMD, input);
	player_->SetCamera(mainCamera);

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			obj[i][j] = new Object3d();
			obj[i][j]->SetModel(p);
			obj[i][j]->Initialize();
			obj[i][j]->wtf.scale = { 0.1f,0.1f,0.1f };
		}
	}


	//タイトル
	title_ = new Title();
	title_->Initialize(dxCommon, input);
	title_->SetCamera(mainCamera);

}

void GameScene::Reset() {
	
}

/// <summary>
/// 毎フレーム処理
/// </summary>
void GameScene::Update() {
	switch (sceneNo_)
	{
	case SceneNo::TITLE:
		if (sceneNo_ == SceneNo::TITLE) {
			//シーン切り替え
			if (input->TriggerKey(DIK_SPACE) || input->ButtonInput(RT)) {
				sceneNo_ = SceneNo::GAME;
			}
		}
		break;
	case SceneNo::GAME:
		if (sceneNo_ == SceneNo::GAME) {
			mainCamera->SetEye({ -5,-5,5 });
			mainCamera->SetTarget({ -5,-2,10 });
			mainCamera->Update();

			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 6; j++) {
					obj[i][j]->wtf.position = { ((float)i - 6.0f) * 1.0f, (5.0f - (float)j) * 1.0f,15.0f };
					obj[i][j]->Update();
				}
			}
			player_->Update();

			skydome->Update();
		}
	}
}

/// <summary>
/// 描画
/// </summary>
void GameScene::Draw() {
	if (sceneNo_ == SceneNo::TITLE) {
		titleSprite->Draw();
	
	}
	if (sceneNo_ == SceneNo::GAME) {
		wakuSprite->Draw();
		setumeiSprite->Draw();
		HHSprite->Draw();
		stage1Sprite->Draw();
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