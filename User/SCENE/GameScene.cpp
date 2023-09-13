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
	//外枠
	wakuSprite->Initialize(spriteCommon);
	wakuSprite->SetPozition({ 0,0 });
	wakuSprite->SetSize({ 1280.0f, 720.0f });
	spriteCommon->LoadTexture(3, "back.png");
	wakuSprite->SetTextureIndex(3);
	//ゲームルール説明
	setumeiSprite->Initialize(spriteCommon);
	setumeiSprite->SetPozition({ 1000,0 });
	setumeiSprite->SetSize({ 300.0f, 720.0f });
	spriteCommon->LoadTexture(4, "setumei.png");
	setumeiSprite->SetTextureIndex(4);
	//操作説明
	sousaSprite->Initialize(spriteCommon);
	sousaSprite->SetPozition({ 30,600 });
	sousaSprite->SetSize({ 200.0f, 100.0f });
	spriteCommon->LoadTexture(21, "sousa.png");
	sousaSprite->SetTextureIndex(21);
	//タイトル
	titleSprite->Initialize(spriteCommon);
	titleSprite->SetPozition({ 0,0 });
	titleSprite->SetSize({ 1280.0f, 720.0f });
	spriteCommon->LoadTexture(5, "Title.png");
	titleSprite->SetTextureIndex(5);
	//ステージセレクト
	selectSprite->Initialize(spriteCommon);
	selectSprite->SetPozition({ 0,0 });
	selectSprite->SetSize({ 1280.0f, 720.0f });
	spriteCommon->LoadTexture(22, "select.png");
	selectSprite->SetTextureIndex(22);
	//操作説明の選択枠
	takuSprite->Initialize(spriteCommon);
	takuSprite->SetPozition({ 137,106 });
	takuSprite->SetSize({ 145.0f, 186.0f });
	spriteCommon->LoadTexture(23, "taku.png");
	takuSprite->SetTextureIndex(23);
	//クリア
	clearSprite->Initialize(spriteCommon);
	clearSprite->SetPozition({ 0,0 });
	clearSprite->SetSize({ 1280.0f, 720.0f });
	spriteCommon->LoadTexture(20, "Clear.png");
	clearSprite->SetTextureIndex(20);
	//元素{
	HHSprite->Initialize(spriteCommon);
	HHSprite->SetPozition({ 500,600 });
	HHSprite->SetSize({ 300.0f, 100.0f });
	spriteCommon->LoadTexture(6, "HH.png");
	HHSprite->SetTextureIndex(6);

	H2OSprite->Initialize(spriteCommon);
	H2OSprite->SetPozition({ 500,600 });
	H2OSprite->SetSize({ 300.0f, 100.0f });
	spriteCommon->LoadTexture(15, "H2O.png");
	H2OSprite->SetTextureIndex(15);

	H2O2Sprite->Initialize(spriteCommon);
	H2O2Sprite->SetPozition({ 500,600 });
	H2O2Sprite->SetSize({ 300.0f, 100.0f });
	spriteCommon->LoadTexture(16, "H2O2.png");
	H2O2Sprite->SetTextureIndex(16);

	N2H4Sprite->Initialize(spriteCommon);
	N2H4Sprite->SetPozition({ 500,600 });
	N2H4Sprite->SetSize({ 300.0f, 100.0f });
	spriteCommon->LoadTexture(17, "N2H4.png");
	N2H4Sprite->SetTextureIndex(17);

	CH4Sprite->Initialize(spriteCommon);
	CH4Sprite->SetPozition({ 500,600 });
	CH4Sprite->SetSize({ 300.0f, 100.0f });
	spriteCommon->LoadTexture(18, "CH4.png");
	CH4Sprite->SetTextureIndex(18);

	CH4OSprite->Initialize(spriteCommon);
	CH4OSprite->SetPozition({ 500,600 });
	CH4OSprite->SetSize({ 300.0f, 100.0f });
	spriteCommon->LoadTexture(19, "CH4O.png");
	CH4OSprite->SetTextureIndex(19);
	//}

	//ステージ数
	stage1Sprite->Initialize(spriteCommon);
	stage1Sprite->SetPozition({ 50,50 });
	stage1Sprite->SetSize({ 100.0f, 400.0f });
	spriteCommon->LoadTexture(7, "stage1.png");
	stage1Sprite->SetTextureIndex(7);

	stage2Sprite->Initialize(spriteCommon);
	stage2Sprite->SetPozition({ 50,50 });
	stage2Sprite->SetSize({ 100.0f, 400.0f });
	spriteCommon->LoadTexture(8, "stage2.png");
	stage2Sprite->SetTextureIndex(8);

	stage3Sprite->Initialize(spriteCommon);
	stage3Sprite->SetPozition({ 50,50 });
	stage3Sprite->SetSize({ 100.0f, 400.0f });
	spriteCommon->LoadTexture(9, "stage3.png");
	stage3Sprite->SetTextureIndex(9);

	stage4Sprite->Initialize(spriteCommon);
	stage4Sprite->SetPozition({ 50,50 });
	stage4Sprite->SetSize({ 100.0f, 400.0f });
	spriteCommon->LoadTexture(10, "stage4.png");
	stage4Sprite->SetTextureIndex(10);

	stage5Sprite->Initialize(spriteCommon);
	stage5Sprite->SetPozition({ 50,50 });
	stage5Sprite->SetSize({ 100.0f, 400.0f });
	spriteCommon->LoadTexture(11, "stage5.png");
	stage5Sprite->SetTextureIndex(11);

	stage6Sprite->Initialize(spriteCommon);
	stage6Sprite->SetPozition({ 50,50 });
	stage6Sprite->SetSize({ 100.0f, 400.0f });
	spriteCommon->LoadTexture(12, "stage6.png");
	stage6Sprite->SetTextureIndex(12);

	stage7Sprite->Initialize(spriteCommon);
	stage7Sprite->SetPozition({ 50,50 });
	stage7Sprite->SetSize({ 100.0f, 400.0f });
	spriteCommon->LoadTexture(13, "stage7.png");
	stage7Sprite->SetTextureIndex(13);

	stage8Sprite->Initialize(spriteCommon);
	stage8Sprite->SetPozition({ 50,50 });
	stage8Sprite->SetSize({ 100.0f, 400.0f });
	spriteCommon->LoadTexture(14, "stage8.png");
	stage8Sprite->SetTextureIndex(14);


	// カメラ生成
	mainCamera = new Camera(WinApp::window_width, WinApp::window_height);
	camera1 = new Camera(WinApp::window_width, WinApp::window_height);
	camera2 = new Camera(WinApp::window_width, WinApp::window_height);
	camera3 = new Camera(WinApp::window_width, WinApp::window_height);

	mainCamera->SetEye({ 2.5f,-3.0f,4 });
	mainCamera->SetTarget({ 2.5f,-3.0f,10 });
	mainCamera->Update();

	ParticleManager::SetCamera(mainCamera);
	Object3d::SetCamera(mainCamera);
	FBXObject3d::SetCamera(mainCamera);

	skydomeMD = Model::LoadFromOBJ("skydome");
	skydome = Object3d::Create();
	skydome->SetModel(skydomeMD);
	skydome->wtf.scale = (Vector3{ 1000, 1000, 1000 });

	p = Model::LoadFromOBJ("Particle");
	playerMD = Model::LoadFromOBJ("H");
	block = Model::LoadFromOBJ("WoodenBox");




	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			obj[j][i] = new Object3d();
			obj[j][i]->SetModel(p);
			obj[j][i]->Initialize();
			obj[j][i]->wtf.scale = { 0.1f,0.1f,0.1f };
		}
	}

	//プレイヤー
	player_ = new Player();
	player_->Initialize(dxCommon, playerMD, input);
	player_->Reset(map);
	player_->SetCamera(mainCamera);

	elementMna = new ElementManager();
	elementMna->Initialize(input, map);
	elementMna->SetPlayer(player_);
	elementMna->Reset(map);

	//タイトル
	title_ = new Title();
	title_->Initialize(dxCommon, input);
	title_->SetCamera(mainCamera);

	audio = new Audio();
	audio->Initialize();
	audio->LoadWave("Title.wav");
	audio->LoadWave("game.wav");
	audio->LoadWave("open.wav");
	audio->LoadWave("clear.wav");
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

			if (soundCheckFlag == 0) {
				//タイトルBGM再生

				pSourceVoice[0] = audio->PlayWave("Title.wav");
				pSourceVoice[0]->SetVolume(0.3f);
				soundCheckFlag = 1;
			}
			
			//シーン切り替え
			if (input->TriggerKey(DIK_SPACE)) {
				sceneNo_ = SceneNo::STAGESELECT;
				//ステージ選択時の効果音
				pSourceVoice[1] = audio->PlayWave("open.wav");
				pSourceVoice[1]->SetVolume(0.4f);
				soundCheckFlag2 = 1;

			}
		}
		break;
	case SceneNo::STAGESELECT:
		if (input->TriggerKey(DIK_L)) {

			sceneNo_ = SceneNo::TITLE;
		}
		if (soundCheckFlag3 == 1) {
			//ゲームシーンの音楽を止める
			pSourceVoice[2]->Stop();
			soundCheckFlag3 = 0;
		}
		if (soundCheckFlag == 0) {
			//タイトルBGM再生

			pSourceVoice[0] = audio->PlayWave("Title.wav");
			pSourceVoice[0]->SetVolume(0.3f);
			soundCheckFlag = 1;
		}
		
		if (input->TriggerKey(DIK_A)) {
			if (stageNmb > 0) {
				selectCount--;
				stageNmb--;
			}
		}
		if (input->TriggerKey(DIK_D)) {
			if (stageNmb < 8) {
				selectCount++;
				stageNmb++;
			}
		}
		if (input->TriggerKey(DIK_W)) {
			if (stageNmb > 3) {
				selectCount -= 4;
				stageNmb -= 4;
			}
		}
		if (input->TriggerKey(DIK_S)) {
			if (stageNmb < 4) {
				selectCount += 4;
				stageNmb += 4;
			}
		}
		if (input->TriggerKey(DIK_SPACE)) {
			//ステージ選択時の効果音
			pSourceVoice[1] = audio->PlayWave("open.wav");
			pSourceVoice[1]->SetVolume(0.4f);
			soundCheckFlag2 = 1;
			
			sceneNo_ = SceneNo::GAME;
		}
		break;
	case SceneNo::GAME:
		if (sceneNo_ == SceneNo::GAME) {

			//タイトルの音楽を止める
			pSourceVoice[0]->Stop();
			soundCheckFlag = 0;


			if (soundCheckFlag3 == 0) {
				//ゲームBGM再生

				pSourceVoice[2] = audio->PlayWave("game.wav");
				pSourceVoice[2]->SetVolume(0.5f);
				soundCheckFlag3 = 1;
			}

			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 6; j++) {
					obj[i][j]->wtf.position = { ((float)i - 6.0f) * 1.0f, (5.0f - (float)j) * 1.0f,15.0f };
					obj[i][j]->Update();
				}
			}
			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 6; j++) {

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

			//マップ切り替え
			if (player_->GetFrame() >= 60) {
				if (input->TriggerKey(DIK_RIGHT) && map < mapMax) {
					stageCount++;
					map++;
					player_->Reset(map);
					elementMna->Reset(map);
				}
				else if (input->TriggerKey(DIK_LEFT) && map > 0) {
					stageCount--;
					map--;
					player_->Reset(map);
					elementMna->Reset(map);
				}
				//位置リセット
				if (input->TriggerKey(DIK_R)) {
					player_->Reset(map);
				}
			}
			if (stageCount >= 8) {
				stageCount = 8;
			}
			else if (stageCount <= 0) {
				stageCount = 1;
			}
			player_->Update();

			skydome->Update();

			elementMna->SetPlayer(player_);
			elementMna->Update(player_->GetWorldPosition());

			if (input->TriggerKey(DIK_L)) {
				
				sceneNo_ = SceneNo::STAGESELECT;
			}
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
	if (sceneNo_ == SceneNo::STAGESELECT) {
		selectSprite->Draw();
		takuSprite->Draw();
		if (selectCount == 1) {
			takuSprite->SetPozition({ 137,106 });
		}else if (selectCount == 2) {
			takuSprite->SetPozition({ 431,106 });
		}
		else if (selectCount == 3) {
			takuSprite->SetPozition({ 737,106 });
		}
		else if (selectCount == 4) {
			takuSprite->SetPozition({ 1042,106 });
		}
		else if (selectCount == 5) {
			takuSprite->SetPozition({ 137,456 });
		}
		else if (selectCount == 6) {
			takuSprite->SetPozition({ 431,456 });
		}
		else if (selectCount == 7) {
			takuSprite->SetPozition({ 737,456 });
		}
		else if (selectCount == 8) {
			takuSprite->SetPozition({ 1042,456 });
		}
	}

	if (sceneNo_ == SceneNo::GAME) {
		wakuSprite->Draw();
		setumeiSprite->Draw();
		sousaSprite->Draw();
		if (stageNmb == 0) {
			HHSprite->Draw();
			stage1Sprite->Draw();
		}
		else if (stageNmb == 1) {
			H2OSprite->Draw();
			stage2Sprite->Draw();
		}
		else if (stageNmb == 2) {
			H2O2Sprite->Draw();
			stage3Sprite->Draw();
		}
		else if (stageNmb == 3) {
			H2OSprite->Draw();
			stage4Sprite->Draw();
		}
		else if (stageNmb == 4) {
			H2O2Sprite->Draw();
			stage5Sprite->Draw();
		}
		else if (stageNmb == 5) {
			N2H4Sprite->Draw();
			stage6Sprite->Draw();
		}
		else if (stageNmb == 6) {
			CH4Sprite->Draw();
			stage7Sprite->Draw();
		}
		else if (stageNmb == 7) {
			CH4OSprite->Draw();
			stage8Sprite->Draw();
		}
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
		elementMna->Draw();
		//skydome->Draw();

		//3Dオブジェクト描画後処理
		Object3d::PostDraw();
		//クリア
		if (Clearflag == 1) {
			clearSprite->Draw();
		}

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