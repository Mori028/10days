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
#include "Input.h"

class Player;
class ElementManager
{
public:
	ElementManager();
	~ElementManager();

	void Initialize(Input* input, int map);

	void Update(Vector3 playerPos);

	void Draw();

	void ElementCollision();

	/// <summary>
	/// 元素のCSVの読み込み
	/// </summary>
	void LoadEnemyPopData(int mapNmb);

	//CSVリセット
	void EnemyPopComandReset(int mapNmb);

	/// <summary>
	/// 元素のCSVの解析
	/// </summary>
	void UpdateEnemyPopCommands();

	//元素の登録
	void ExistenceEnemy(const Vector3& EnemyPos, int connectMax, int elementNmb, int modelNmb);

	void SetPlayer(Player* player) { player_ = player; }
	void Finalize();

	void Reset(int map, int stageNmb);

	bool ClearFlag();

	void ElementWallColl();

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

	Input* input_ = nullptr;

	int map_ = 0;

	bool hitWall = false;
	
	bool clearFlag = false;

	bool aa = false;

	float maxframe = 60.0f;
	float frame = maxframe;
	float oneframe = 4.0f;

	float clearFrame = 0.0f;

	//元素に当たっているか
	bool elementWall = false;

	//H
	Object3d* HObj_ = nullptr;
	Model* Hmodel_ = nullptr;
	//C
	Object3d* CObj_ = nullptr;
	Model* Cmodel_ = nullptr;
	//N
	Object3d* NObj_ = nullptr;
	Model* Nmodel_ = nullptr;
	//O
	Object3d* OObj_ = nullptr;
	Model* Omodel_ = nullptr;



};
