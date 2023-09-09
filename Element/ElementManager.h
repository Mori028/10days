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

private:

	std::list<std::unique_ptr<ElementH>> elements;
	//“G”­¶ƒRƒ}ƒ“ƒh
	std::stringstream elementPop;

	bool waitflag = false;
	int waitTimer = 0;
	Camera* camera_ = nullptr;

	Vector3 playerPos_;

	//Œ³‘fƒ‚ƒfƒ‹
	Model* elementModel_ = nullptr;
	//Œ³‘fƒ‚ƒfƒ‹
	Model* elementModel2_ = nullptr;
	//Œ³‘fƒ‚ƒfƒ‹
	Model* elementModel3_ = nullptr;
	//Œ³‘fƒ‚ƒfƒ‹
	Model* elementModel4_ = nullptr;

};
