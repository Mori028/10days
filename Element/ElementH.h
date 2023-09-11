#pragma once
#include "Object3d.h"
#include "Model.h"

class ElementH
{
public:
	ElementH();
	~ElementH();

	void Initialize(Model* elementModel, Vector3 elementPos, int connectMaxNmb,int elementNmb);

	void Update(Vector3 playerPos);

	void Draw();

	Vector3 GetWorldPosition() { return elementH_->wtf.position; }

	bool ConnectMaxElement() { return connectMax_; }

	Vector3 GetWroldPosition() { return elementH_->wtf.position; }

	void ConnectElement() { ifConnect = true; }

	int GetElementNmb() { return elementNmb_; }

	void collectNmb(int Nmb);

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

};
