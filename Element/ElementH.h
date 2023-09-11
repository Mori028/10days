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

	//これ以上連結できないかどうか
	bool connectMax_ = false;
	//今連結している数
	int connectNmb_ = 0;
	//連結できる最大数
	int connectMaxNum_ = 0;
	//連結しているかどうか
	int ifConnect = false;
	//個体識別番号
	int elementNmb_ = 0;

	Vector3 oldPlayerPos_;
	Vector3 move = { 0,0,0 };

	int collectKinds[3];

};
