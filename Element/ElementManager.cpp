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
	//�t�@�C�����J��
	std::ifstream file;
	file.open("Resources/enemyPop2.csv");
	assert(file.is_open());

	//�t�@�C������e�𕶎���X�g���[���ɃR�s�[
	elementPop << file.rdbuf();

	//�t�@�C�������
	file.close();
}

void ElementManager::EnemyPopComandReset()
{
	elementPop.str("");
	elementPop.clear(std::stringstream::goodbit);
	LoadEnemyPopData();
}

void ElementManager::UpdateEnemyPopCommands()
{
	if (waitflag)
	{
		waitTimer--;
		if (waitTimer <= 0)
		{
			//�ҋ@����
			waitflag = false;
		}
		return;
	}

	//1�s���̕����������ϐ�
	std::string line;

	//�R�}���h���s���[�v
	while (getline(elementPop, line))
	{
		//1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
		std::istringstream line_stream(line);

		std::string word;
		//,��؂�ōs�̐擪��������擾
		getline(line_stream, word, ',');

		//"//"����n�܂�s�̓R�����g
		if (word.find("//") == 0)
		{
			//�R�����g�s�͔�΂�
			continue;
		}

		//POP�R�}���h
		if (word.find("POP") == 0)
		{
			//x���W
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());
			//y���W
			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());
			//z���W
			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());
			//�ő�A����
			getline(line_stream, word, ',');
			float connectMax = (float)std::atof(word.c_str());
			//�̎���
			getline(line_stream, word, ',');
			float elementNmb = (float)std::atof(word.c_str());
			//���̃��f�����g����
			getline(line_stream, word, ',');
			float elementModelNmb = (float)std::atof(word.c_str());
			//�G�𔭐�������
			ExistenceEnemy(Vector3(x, y, z), connectMax, elementNmb, elementModelNmb);
		}

		//WAIT�R�}���h
		else if (word.find("WAIT") == 0)
		{
			getline(line_stream, word, ',');

			//�҂�����
			int32_t waitTime = atoi(word.c_str());

			//�ҋ@�J�n
			waitflag = true;
			waitTimer = waitTime;

			//�R�}���h���[�v�𔲂���
			break;
		}

	}
}

void ElementManager::ExistenceEnemy(const Vector3& EnemyPos,int connectMax,int elementNmb,int modelNmb)
{
	//�G�L�����̐���
	std::unique_ptr<ElementH> newElement = std::make_unique<ElementH>();
	if (modelNmb == 0) {
		newElement->Initialize(elementModel_, EnemyPos, connectMax, elementNmb);
	}
	else if (modelNmb == 1) {
		newElement->Initialize(elementModel2_, EnemyPos, connectMax, elementNmb);
	}
	else if (modelNmb == 2) {
		newElement->Initialize(elementModel3_, EnemyPos, connectMax, elementNmb);
	}
	else if (modelNmb == 3) {
		newElement->Initialize(elementModel4_, EnemyPos, connectMax, elementNmb);
	}
	

	//���X�g�ɓo�^����
	elements.push_back(std::move(newElement));
}

