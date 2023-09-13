#include "ElementManager.h"
#include "player.h"
#include "map.h"

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

void ElementManager::Initialize(Input* input, int map)
{
	assert(input);

	input_ = input;
	//���f���f��
	elementModelH_ = Model::LoadFromOBJ("Hmodel");
	//���f���f��
	elementModelC_ = Model::LoadFromOBJ("Cmodel");
	//���f���f��
	elementModelN_ = Model::LoadFromOBJ("Nmodel");
	//���f���f��
	elementModelO_ = Model::LoadFromOBJ("Omodel");
	//H
	//Hmodel_ = Model::LoadFromOBJ("Hmodel");
	//
	////C
	//Cmodel_ = Model::LoadFromOBJ("Cmodel");
	//
	////N
	//Nmodel_ = Model::LoadFromOBJ("Nmodel");
	//
	////O
	//Omodel_ = Model::LoadFromOBJ("Omodel");


	LoadEnemyPopData(map);

	//ExistenceEnemy(Vector3(3, 0, 15), 2, 1, 2);
	//ExistenceEnemy(Vector3(5, -3, 15), 1, 2, 2);
}

void ElementManager::Update(Vector3 playerPos)
{
	hitWall = false;
	ElementWallColl();
	for (std::unique_ptr<ElementH>& element : elements) {
		element->WallUpdate(elementWall);
		if (element->BlockMove()) {
			hitWall = true;
		}
	}
	for (std::unique_ptr<ElementH>& element : elements) {
		element->Update(playerPos, hitWall);
	}

	ElementCollision();
	UpdateEnemyPopCommands();
	aa = ClearFlag();
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
	Vector2 posA, posB;

	for (std::unique_ptr<ElementH>& element : elements) {
		//���f���ׂĂ̓����蔻��
		for (const std::unique_ptr<ElementH>& element2 : elements) {
			if (element != element2) {
				//���f1�̍��W
				posA = element->GetPlace();

				//���f�Q�̍��W
				posB = element2->GetPlace();

				bool flagA = element->ConnectMaxElement();
				bool flagB = element2->ConnectMaxElement();

				bool flagC = element->GetMoveOn();
				bool flagD = element2->GetMoveOn();

				if (flagA == false && flagB == false) {
					if (posA.y + 1 == posB.y && posA.x == posB.x) {
						//�Ȃ��������f�̌̔ԍ��ۑ�
						element->collectNmb(element2->GetElementNmb());
						element2->collectNmb(element->GetElementNmb());
					}
					if (posA.y - 1 == posB.y && posA.x == posB.x) {
						//�Ȃ��������f�̌̔ԍ��ۑ�
						element->collectNmb(element2->GetElementNmb());
						element2->collectNmb(element->GetElementNmb());
					}


					if (posA.y == posB.y && posA.x + 1 == posB.x) {
						//�Ȃ��������f�̌̔ԍ��ۑ�
						element->collectNmb(element2->GetElementNmb());
						element2->collectNmb(element->GetElementNmb());
					}
					if (posA.y == posB.y && posA.x - 1 == posB.x) {
						//�Ȃ��������f�̌̔ԍ��ۑ�
						element->collectNmb(element2->GetElementNmb());
						element2->collectNmb(element->GetElementNmb());
					}
				}
			}
		}
	}
	for (std::unique_ptr<ElementH>& element : elements) {

		//���f1�̍��W
		posA = element->GetPlace();

		//���f�Q�̍��W
		posB = player_->GatPlace();

		bool flagA = element->ConnectMaxElement();

		if (flagA == false && playerConnectFlag == false) {
			if (posA.y + 1 == posB.y && posA.x == posB.x) {
				//�Ȃ���������
				element->ConnectElement();
				//�Ȃ��������f�̌̔ԍ��ۑ�
				element->collectNmb(0);
				playerConnectFlag = true;
			}
			if (posA.y - 1 == posB.y && posA.x == posB.x) {
				//�Ȃ���������
				element->ConnectElement();
				//�Ȃ��������f�̌̔ԍ��ۑ�
				element->collectNmb(0);
				playerConnectFlag = true;
			}

			if (posA.y == posB.y && posA.x + 1 == posB.x) {
				//�Ȃ���������
				element->ConnectElement();
				//�Ȃ��������f�̌̔ԍ��ۑ�
				element->collectNmb(0);
				playerConnectFlag = true;
			}
			if (posA.y == posB.y && posA.x - 1 == posB.x) {
				//�Ȃ���������
				element->ConnectElement();
				//�Ȃ��������f�̌̔ԍ��ۑ�
				element->collectNmb(0);
				playerConnectFlag = true;
			}

		}
	}
}

void ElementManager::LoadEnemyPopData(int mapNmb)
{
	//�t�@�C�����J��
	std::ifstream file;
	if (mapNmb == 0) {
		file.open("Resources/stage1.csv");
	}
	else if (mapNmb == 1) {
		file.open("Resources/stage2.csv");
	}
	else if (mapNmb == 2) {
		file.open("Resources/stage3.csv");
	}
	else if (mapNmb == 3) {
		file.open("Resources/stage4.csv");
	}
	else if (mapNmb == 4) {
		file.open("Resources/stage5.csv");
	}
	else if (mapNmb == 5) {
		file.open("Resources/stage6.csv");
	}
	else if (mapNmb == 6) {
		file.open("Resources/stage7.csv");
	}
	else if (mapNmb == 7) {
		file.open("Resources/stage8.csv");
	}
	else
	{
		file.open("Resources/stage1.csv");
	}
	assert(file.is_open());

	//�t�@�C������e�𕶎���X�g���[���ɃR�s�[
	elementPop << file.rdbuf();

	//�t�@�C�������
	file.close();
}

void ElementManager::EnemyPopComandReset(int mapNmb)
{
	elementPop.str("");
	elementPop.clear(std::stringstream::goodbit);
	LoadEnemyPopData(mapNmb);
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
		newElement->Initialize(elementModelH_, EnemyPos, connectMax, elementNmb, input_, map_);
	}
	else if (modelNmb == 1) {
		newElement->Initialize(elementModelO_, EnemyPos, connectMax, elementNmb, input_, map_);
	}
	else if (modelNmb == 2) {
		newElement->Initialize(elementModelN_, EnemyPos, connectMax, elementNmb, input_, map_);
	}
	else if (modelNmb == 3) {
		newElement->Initialize(elementModelC_, EnemyPos, connectMax, elementNmb, input_, map_);
	}
	else if (modelNmb == 4) {
		newElement->Initialize(Hmodel_, EnemyPos, connectMax, elementNmb, input_, map_);
	}
	else if (modelNmb == 5) {
		newElement->Initialize(Omodel_, EnemyPos, connectMax, elementNmb, input_, map_);
	}
	else if (modelNmb == 6) {
		newElement->Initialize(Nmodel_, EnemyPos, connectMax, elementNmb, input_, map_);
	}
	else if (modelNmb == 7) {
		newElement->Initialize(Cmodel_, EnemyPos, connectMax, elementNmb, input_, map_);
	}
	else {
		newElement->Initialize(elementModelH_, EnemyPos, connectMax, elementNmb, input_, map_);
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

void ElementManager::Reset(int map,int stageNmb)
{
	Finalize();
	map_ = map;
	//�}�b�v�X�V
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (map == 0) {
				baseMap[j][i] = tutorialMap[j][i];
			}
			else if (map == 1) {
				baseMap[j][i] = map1[j][i];
			}
			else if (map == 2) {
				baseMap[j][i] = map2[j][i];
			}
		}
	}
	clearFrame = 0.0f; 
	clearFlag = false;
	playerConnectFlag = false;
	EnemyPopComandReset(stageNmb);
}

bool ElementManager::ClearFlag()
{
	if (clearFrame >= maxframe) {
		clearFlag = true;
		for (std::unique_ptr<ElementH>& element : elements) {
			if (element->ConnectMaxElement() == false) {
				clearFlag = false;
			}
		}
	}
	return clearFlag;
}

void ElementManager::ElementWallColl()
{
	//����Ώ�A��B�̍��W
	Vector2 posA, posB;
	if (frame < maxframe) {
		frame += oneframe;
	}
	if (clearFrame < maxframe) {
		clearFrame += oneframe;
	}
	else {
		frame = maxframe;
	}

	if (frame >= maxframe) {
		elementWall = false;
		for (std::unique_ptr<ElementH>& element : elements) {
			//���f���ׂĂ̓����蔻��
			for (const std::unique_ptr<ElementH>& element2 : elements) {
				if (element != element2) {
					//���f1�̍��W
					posA = element->GetPlace();

					//���f�Q�̍��W
					posB = element2->GetPlace();

					bool flagA = element->ConnectMaxElement();
					bool flagB = element2->ConnectMaxElement();

					bool flagC = element->GetMoveOn();
					bool flagD = element2->GetMoveOn();

					if (flagA == true && flagB == false && flagD == false) {
						if (input_->PushKey(DIK_A)) {
							if (posA.y == posB.y && posA.x - 1 == posB.x) {
								//���f�ɓ����������ǂ���
								element->HitElementTrue();
								element2->HitElementTrue();
							}

						}
						else if (input_->PushKey(DIK_D)) {
							if (posA.y == posB.y && posA.x + 1 == posB.x) {
								//���f�ɓ����������ǂ���
								element->HitElementTrue();
								element2->HitElementTrue();
							}

						}

						else if (input_->PushKey(DIK_W)) {
							if (posA.y - 1 == posB.y && posA.x == posB.x) {
								//���f�ɓ����������ǂ���
								element->HitElementTrue();
								element2->HitElementTrue();
							}
						}
						else if (input_->PushKey(DIK_S)) {
							if (posA.y + 1 == posB.y && posA.x == posB.x) {
								//���f�ɓ����������ǂ���
								element->HitElementTrue();
								element2->HitElementTrue();
							}
						}
					}
				}
			}
		}
	}
}

