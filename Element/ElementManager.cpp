#include "ElementManager.h"

ElementManager::ElementManager()
{
}

ElementManager::~ElementManager()
{
}

void ElementManager::Initialize()
{
	//元素モデル
	Model* elementModel_ = Model::LoadFromOBJ("C");
	//元素モデル
	Model* elementModel2_ = Model::LoadFromOBJ("H");
	//元素モデル
	Model* elementModel3_ = Model::LoadFromOBJ("N");
	//元素モデル
	Model* elementModel4_ = Model::LoadFromOBJ("O");
}

void ElementManager::Update(Vector3 playerPos)
{
	for (std::unique_ptr<ElementH>& element : elements) {
		element->Update(playerPos);
	}
}

void ElementManager::Draw()
{
	for (std::unique_ptr<ElementH>& element : elements) {
		element->Draw();
	}
}

void ElementManager::ElementCollision()
{
	//判定対象AとBの座標
	 Vector3 posA, posB;

	for (std::unique_ptr<ElementH>& element : elements) {
		//元素すべての当たり判定
		for (const std::unique_ptr<ElementH>& element2 : elements) {

			//元素1の座標
			posA = element->GetWorldPosition();

			//元素２の座標
			posB = element2->GetWorldPosition();

			bool flagA = element->ConnectMaxElement();
			bool flagB = element2->ConnectMaxElement();

			if (Collision::CircleCollision(posB,posA, 1.0f, 1.0f)) {
				if (flagA == false && flagB == false) {

					//つながったかどうかの判定
					element->ConnectElement();
					element2->ConnectElement();
					//つながった元素の個体番号保存
					element->collectNmb(element2->GetElementNmb());
					element2->collectNmb(element->GetElementNmb());

				}
			}
		}
	}
}

void ElementManager::LoadEnemyPopData()
{
	//ファイルを開く
	std::ifstream file;
	file.open("Resources/enemyPop2.csv");
	assert(file.is_open());

	//ファイルを内容を文字列ストリームにコピー
	elementPop << file.rdbuf();

	//ファイルを閉じる
	file.close();
}

void ElementManager::EnemyPopComandReset()
{
	elementPop.str("");
	elementPop.clear(std::stringstream::goodbit);
	LoadEnemyPopData();
}

void ElementManager::UpdateEnemyPopCommands()
{
	if (waitflag)
	{
		waitTimer--;
		if (waitTimer <= 0)
		{
			//待機完了
			waitflag = false;
		}
		return;
	}

	//1行分の文字列を入れる変数
	std::string line;

	//コマンド実行ループ
	while (getline(elementPop, line))
	{
		//1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		std::string word;
		//,区切りで行の先頭文字列を取得
		getline(line_stream, word, ',');

		//"//"から始まる行はコメント
		if (word.find("//") == 0)
		{
			//コメント行は飛ばす
			continue;
		}

		//POPコマンド
		if (word.find("POP") == 0)
		{
			//x座標
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());
			//y座標
			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());
			//z座標
			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());
			//最大連結数
			getline(line_stream, word, ',');
			float connectMax = (float)std::atof(word.c_str());
			//個体識別
			getline(line_stream, word, ',');
			float elementNmb = (float)std::atof(word.c_str());
			//何のモデルを使うか
			getline(line_stream, word, ',');
			float elementModelNmb = (float)std::atof(word.c_str());
			//敵を発生させる
			ExistenceEnemy(Vector3(x, y, z), connectMax, elementNmb, elementModelNmb);
		}

		//WAITコマンド
		else if (word.find("WAIT") == 0)
		{
			getline(line_stream, word, ',');

			//待ち時間
			int32_t waitTime = atoi(word.c_str());

			//待機開始
			waitflag = true;
			waitTimer = waitTime;

			//コマンドループを抜ける
			break;
		}

	}
}

void ElementManager::ExistenceEnemy(const Vector3& EnemyPos,int connectMax,int elementNmb,int modelNmb)
{
	//敵キャラの生成
	std::unique_ptr<ElementH> newElement = std::make_unique<ElementH>();
	if (modelNmb == 0) {
		newElement->Initialize(elementModel_, EnemyPos, connectMax, elementNmb);
	}
	else if (modelNmb == 1) {
		newElement->Initialize(elementModel2_, EnemyPos, connectMax, elementNmb);
	}
	else if (modelNmb == 2) {
		newElement->Initialize(elementModel3_, EnemyPos, connectMax, elementNmb);
	}
	else if (modelNmb == 3) {
		newElement->Initialize(elementModel4_, EnemyPos, connectMax, elementNmb);
	}
	

	//リストに登録する
	elements.push_back(std::move(newElement));
}

