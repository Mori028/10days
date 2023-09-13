#include "ElementManager.h"
#include "player.h"

ElementManager::ElementManager()
{
}

ElementManager::~ElementManager()
{
	delete elementModelH_;
	delete elementModelC_;
	delete elementModelN_;
	delete elementModelO_;
}

void ElementManager::Initialize()
{
	//���f���f��
	elementModelH_ = Model::LoadFromOBJ("H");
	//���f���f��
	elementModelC_ = Model::LoadFromOBJ("C");
	//���f���f��
	elementModelN_ = Model::LoadFromOBJ("N");
	//���f���f��
	elementModelO_ = Model::LoadFromOBJ("O");
	//H
	Hmodel_ = Model::LoadFromOBJ("Hmodel");
	HObj_ = Object3d::Create();
	HObj_->SetModel(Hmodel_);
	HObj_->wtf.position = { 0,0,0 };
	HObj_->wtf.scale = { 1.0f,1.0f,1.0f };
	//C
	Cmodel_ = Model::LoadFromOBJ("Cmodel");
	CObj_ = Object3d::Create();
	CObj_->SetModel(Hmodel_);
	CObj_->wtf.position = { 0,0,0 };
	CObj_->wtf.scale = { 1.0f,1.0f,1.0f };
	//N
	Nmodel_ = Model::LoadFromOBJ("Nmodel");
	NObj_ = Object3d::Create();
	NObj_->SetModel(Hmodel_);
	NObj_->wtf.position = { 0,0,0 };
	NObj_->wtf.scale = { 1.0f,1.0f,1.0f };
	//O
	Omodel_ = Model::LoadFromOBJ("Omodel");
	OObj_ = Object3d::Create();
	OObj_->SetModel(Hmodel_);
	OObj_->wtf.position = { 0,0,0 };
	OObj_->wtf.scale = { 1.0f,1.0f,1.0f };

	ExistenceEnemy(Vector3(-3, 0,15), 2, 1, 2);
	ExistenceEnemy(Vector3(-5, 0, 15), 1, 2, 2);
}

void ElementManager::Update(Vector3 playerPos)
{
	for (std::unique_ptr<ElementH>& element : elements) {
		element->Update(playerPos);
	}
	
	ElementCollision();
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

			if (Collision::CircleCollision(posB, posA, 0.5f, 0.5f)) {
				if (flagA == false && flagB == false) {

					////�Ȃ��������ǂ����̔���
					//element->ConnectElement();
					//element2->ConnectElement();
					//�Ȃ��������f�̌̔ԍ��ۑ�
					element->collectNmb(element2->GetElementNmb());
					element2->collectNmb(element->GetElementNmb());

				}
			}
		}
	}
	for (std::unique_ptr<ElementH>& element : elements) {

		//���f1�̍��W
		posA = element->GetWorldPosition();

		//���f�Q�̍��W
		posB = player_->GetWorldPosition();

		bool flagA = element->ConnectMaxElement();

		if (Collision::CircleCollision(posB, posA, 0.5f, 0.5f)) {
			if (flagA == false && playerConnectFlag == false) {

				//�Ȃ���������
				element->ConnectElement();
				//�Ȃ��������f�̌̔ԍ��ۑ�
				element->collectNmb(0);
				playerConnectFlag = true;

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
			int connectMax = (int)std::atof(word.c_str());
			//�̎���
			getline(line_stream, word, ',');
			int elementNmb = (int)std::atof(word.c_str());
			//���̃��f�����g����
			getline(line_stream, word, ',');
			int elementModelNmb = (int)std::atof(word.c_str());
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

void ElementManager::ExistenceEnemy(const Vector3& EnemyPos, int connectMax, int elementNmb, int modelNmb)
{
	//�G�L�����̐���
	std::unique_ptr<ElementH> newElement = std::make_unique<ElementH>();
	if (modelNmb == 0) {
		newElement->Initialize(elementModelH_, EnemyPos, connectMax, elementNmb);
	}
	else if (modelNmb == 1) {
		newElement->Initialize(elementModelC_, EnemyPos, connectMax, elementNmb);
	}
	else if (modelNmb == 2) {
		newElement->Initialize(elementModelN_, EnemyPos, connectMax, elementNmb);
	}
	else if (modelNmb == 3) {
		newElement->Initialize(elementModelO_, EnemyPos, connectMax, elementNmb);
	}
	else {
		newElement->Initialize(elementModelH_, EnemyPos, connectMax, elementNmb);
	}


	//���X�g�ɓo�^����
	elements.push_back(std::move(newElement));
}

void ElementManager::Finalize()
{
	for (std::unique_ptr<ElementH>& element : elements) {
		element->TrueDeath();
	}
	elements.remove_if([](std::unique_ptr<ElementH>& element) {
		return element->IsDeath();
		});
}

