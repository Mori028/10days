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
	/// ���f��CSV�̓ǂݍ���
	/// </summary>
	void LoadEnemyPopData();

	//CSV���Z�b�g
	void EnemyPopComandReset();

	/// <summary>
	/// ���f��CSV�̉��
	/// </summary>
	void UpdateEnemyPopCommands();

	//���f�̓o�^
	void ExistenceEnemy(const Vector3& EnemyPos);

private:

	std::list<std::unique_ptr<ElementH>> elements;
	Vector3 playerPos_;

	//���f���f��
	Model* elementModel_ = nullptr;
	//���f���f��
	Model* elementModel2_ = nullptr;
	//���f���f��
	Model* elementModel3_ = nullptr;
	//���f���f��
	Model* elementModel4_ = nullptr;
};
