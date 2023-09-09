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
}

void ElementManager::EnemyPopComandReset()
{
}

void ElementManager::UpdateEnemyPopCommands()
{
}

void ElementManager::ExistenceEnemy(const Vector3& EnemyPos)
{
}

