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
	void ExistenceEnemy(const Vector3& EnemyPos);

private:

	std::list<std::unique_ptr<ElementH>> elements;
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
