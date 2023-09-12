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
	/// Œ³‘f‚ÌCSV‚Ì“Ç‚İ‚İ
	/// </summary>
	void LoadEnemyPopData();

	//CSVƒŠƒZƒbƒg
	void EnemyPopComandReset();

	/// <summary>
	/// Œ³‘f‚ÌCSV‚Ì‰ğÍ
	/// </summary>
	void UpdateEnemyPopCommands();

	//Œ³‘f‚Ì“o˜^
	void ExistenceEnemy(const Vector3& EnemyPos, int connectMax, int elementNmb, int modelNmb);

	void SetPlayer(Player* player) { player_ = player; }
	void Finalize();

private:

	std::list<std::unique_ptr<ElementH>> elements;
	//“G”­¶ƒRƒ}ƒ“ƒh
	std::stringstream elementPop;

	bool waitflag = false;
	int waitTimer = 0;
	Camera* camera_ = nullptr;

	Vector3 playerPos_;
	Player* player_ = nullptr;
	bool playerConnectFlag = false;

	//Œ³‘fƒ‚ƒfƒ‹
	Model* elementModelH_ = nullptr;
	//Œ³‘fƒ‚ƒfƒ‹
	Model* elementModelC_ = nullptr;
	//Œ³‘fƒ‚ƒfƒ‹
	Model* elementModelN_ = nullptr;
	//Œ³‘fƒ‚ƒfƒ‹
	Model* elementModelO_ = nullptr;



};
