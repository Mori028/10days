#pragma once
#include "Collision.h"
#include "ElementH.h"

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
	void ExistenceEnemy(const Vector3& EnemyPos);

private:

	std::list<std::unique_ptr<ElementH>> elements;
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
