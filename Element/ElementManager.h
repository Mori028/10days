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

private:

	std::list<std::unique_ptr<ElementH>> elements;
	//敵発生コマンド
	std::stringstream elementPop;

	bool waitflag = false;
	int waitTimer = 0;
	Camera* camera_ = nullptr;

	Vector3 playerPos_;

	//元素モデル
	Model* elementModel_ = nullptr;
	//元素モデル
	Model* elementModel2_ = nullptr;
	//元素モデル
	Model* elementModel3_ = nullptr;
	//元素モデル
	Model* elementModel4_ = nullptr;

};
