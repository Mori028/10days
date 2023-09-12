#pragma once
#include "Collision.h"
#include "ElementH.h"
#include <list>
#include <memory>
#include <cassert>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

class Player;
class ElementManager
{
public:
	ElementManager();
	~ElementManager();

	void Initialize();

	void Update(Vector3 playerPos);

	void Draw();

	void ElementCollision();

	/// <summary>
	/// 元素のCSVの読み込み
	/// </summary>
	void LoadEnemyPopData();

	//CSVリセット
	void EnemyPopComandReset();

	/// <summary>
	/// 元素のCSVの解析
	/// </summary>
	void UpdateEnemyPopCommands();

	//元素の登録
	void ExistenceEnemy(const Vector3& EnemyPos, int connectMax, int elementNmb, int modelNmb);

	void SetPlayer(Player* player) { player_ = player; }
	void Finalize();

private:

	std::list<std::unique_ptr<ElementH>> elements;
	//敵発生コマンド
	std::stringstream elementPop;

	bool waitflag = false;
	int waitTimer = 0;
	Camera* camera_ = nullptr;

	Vector3 playerPos_;
	Player* player_ = nullptr;
	bool playerConnectFlag = false;

	//元素モデル
	Model* elementModelH_ = nullptr;
	//元素モデル
	Model* elementModelC_ = nullptr;
	//元素モデル
	Model* elementModelN_ = nullptr;
	//元素モデル
	Model* elementModelO_ = nullptr;



};
