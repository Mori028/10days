#include "ElementManager.h"

ElementManager::ElementManager()
{
}

ElementManager::~ElementManager()
{
}

void ElementManager::Initialize()
{
	//Œ³‘fƒ‚ƒfƒ‹
	Model* elementModel_ = Model::LoadFromOBJ("C");
	//Œ³‘fƒ‚ƒfƒ‹
	Model* elementModel2_ = Model::LoadFromOBJ("H");
	//Œ³‘fƒ‚ƒfƒ‹
	Model* elementModel3_ = Model::LoadFromOBJ("N");
	//Œ³‘fƒ‚ƒfƒ‹
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
	//”»’è‘ÎÛA‚ÆB‚ÌÀ•W
	 Vector3 posA, posB;

	for (std::unique_ptr<ElementH>& element : elements) {
		//Œ³‘f‚·‚×‚Ä‚Ì“–‚½‚è”»’è
		for (const std::unique_ptr<ElementH>& element2 : elements) {

			//Œ³‘f1‚ÌÀ•W
			posA = element->GetWorldPosition();

			//Œ³‘f‚Q‚ÌÀ•W
			posB = element2->GetWorldPosition();

			bool flagA = element->ConnectMaxElement();
			bool flagB = element2->ConnectMaxElement();

			if (Collision::CircleCollision(posB,posA, 1.0f, 1.0f)) {
				if (flagA == false && flagB == false) {

					//‚Â‚È‚ª‚Á‚½‚©‚Ç‚¤‚©‚Ì”»’è
					element->ConnectElement();
					element2->ConnectElement();
					//‚Â‚È‚ª‚Á‚½Œ³‘f‚ÌŒÂ‘Ì”Ô†•Û‘¶
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

