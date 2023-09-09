#include "ElementManager.h"

ElementManager::ElementManager()
{
}

ElementManager::~ElementManager()
{
}

void ElementManager::Initialize()
{
	//���f���f��
	Model* elementModel_ = Model::LoadFromOBJ("C");
	//���f���f��
	Model* elementModel2_ = Model::LoadFromOBJ("H");
	//���f���f��
	Model* elementModel3_ = Model::LoadFromOBJ("N");
	//���f���f��
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
	//����Ώ�A��B�̍��W
	 Vector3 posA, posB;

	for (std::unique_ptr<ElementH>& element : elements) {
		//���f���ׂĂ̓����蔻��
		for (const std::unique_ptr<ElementH>& element2 : elements) {

			//���f1�̍��W
			posA = element->GetWorldPosition();

			//���f�Q�̍��W
			posB = element2->GetWorldPosition();

			bool flagA = element->ConnectMaxElement();
			bool flagB = element2->ConnectMaxElement();

			if (Collision::CircleCollision(posB,posA, 1.0f, 1.0f)) {
				if (flagA == false && flagB == false) {

					//�Ȃ��������ǂ����̔���
					element->ConnectElement();
					element2->ConnectElement();
					//�Ȃ��������f�̌̔ԍ��ۑ�
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

