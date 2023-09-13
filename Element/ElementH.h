#pragma once
#include "Object3d.h"
#include "Model.h"
#include "Input.h"

class ElementH
{
public:
	//����
	enum Direction {
		Left,
		Right,
		Up,
		Down,
	};
	ElementH();
	~ElementH();

	void Initialize(Model* elementModel, Vector3 elementPos, int connectMaxNmb,int elementNmb,Input* input,int map);

	void Update(Vector3 playerPos, bool hitBlocks);

	void Draw();


	Vector3 GetWorldPosition() { return elementH_->wtf.position; }

	bool ConnectMaxElement() { return connectMax_; }

	Vector3 GetWroldPosition() { return elementH_->wtf.position; }

	void ConnectElement() { ifConnect = true; }

	int GetElementNmb() { return elementNmb_; }

	void collectNmb(int Nmb);

	void TrueDeath() { isDeath = true; };

	bool IsDeath() { return isDeath; }

	bool BlockMove() { return hitBlock; }

	Vector2 GetPlace() { return place; }

	bool GetMoveOn() { return ifConnect; }

	void WallUpdate(bool elementHit);

	//�C�[�W���O
	float easeOutCubic(float x) {
		return 1 - (float)pow(1 - x, 3);
	}
	void HitElementTrue() { hitElement = true; }

private:


	Object3d* elementH_ = nullptr;
	Model* elementModel_ = nullptr;

	//����ȏ�A���ł��Ȃ����ǂ���
	bool connectMax_ = false;
	//���A�����Ă��鐔
	int connectNmb_ = 0;
	//�A���ł���ő吔
	int connectMaxNum_ = 0;
	//�A�����Ă��邩�ǂ���
	int ifConnect = false;
	//�̎��ʔԍ�
	int elementNmb_ = 0;

	Vector3 oldPlayerPos_;
	Vector3 move = { 0,0,0 };

	int collectKinds[3];

	bool isDeath = false;

	//���݂̃}�X
	Vector2 place = { 0,0 };

	Input* input_ = nullptr;

	bool hitBlock = false;

	//�C�[�W���O�p�t���[��
	float maxframe = 60.0f;
	float frame = maxframe;
	float oneframe = 4.0f;
	float intFlame = 0;

	bool moveOn = false;

	Vector3 worldPosition = { 0,0,15 };
	Vector3 position = worldPosition;
	//�ړ���
	float moveVal = 1.0f;
	//����
	Direction direction = Direction::Up;

	bool hitElement = false;
};
