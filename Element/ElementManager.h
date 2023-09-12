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
	void ExistenceEnemy(const Vector3& EnemyPos, int connectMax, int elementNmb, int modelNmb);

	void SetPlayer(Player* player) { player_ = player; }
	void Finalize();

private:

	std::list<std::unique_ptr<ElementH>> elements;
	//�G�����R�}���h
	std::stringstream elementPop;

	bool waitflag = false;
	int waitTimer = 0;
	Camera* camera_ = nullptr;

	Vector3 playerPos_;
	Player* player_ = nullptr;
	bool playerConnectFlag = false;

	//���f���f��
	Model* elementModelH_ = nullptr;
	//���f���f��
	Model* elementModelC_ = nullptr;
	//���f���f��
	Model* elementModelN_ = nullptr;
	//���f���f��
	Model* elementModelO_ = nullptr;



};
