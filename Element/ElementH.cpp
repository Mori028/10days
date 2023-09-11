#include "ElementH.h"

ElementH::ElementH()
{
}

ElementH::~ElementH()
{
}

void ElementH::Initialize(Model* elementModel,Vector3 elementPos, int connectMaxNmb, int elementNmb)
{
	assert(elementModel);
	elementNmb_ = elementNmb;
	elementModel_ = elementModel;
	elementH_ = Object3d::Create();
	elementH_->wtf.position = elementPos;
	elementH_->SetModel(elementModel_);
	connectMaxNum_ = connectMaxNmb;
	for (int i = 0; i < 3; i++) {
		collectKinds[i] = { elementNmb_ };
	}
}

void ElementH::Update(Vector3 playerPos)
{
	if (ifConnect) {
		move = (playerPos - oldPlayerPos_);
	}
	if (connectNmb_ >= connectMaxNum_) {
		bool connectMax_ = true;
	}
	elementH_->wtf.position += move;
	elementH_->Update();
	oldPlayerPos_ = playerPos;
	
}

void ElementH::Draw()
{
	elementH_->Draw();
}

void ElementH::collectNmb(int Nmb)
{

		if (collectKinds[0] == elementNmb_ && elementNmb_ != Nmb) {
			collectKinds[0] = Nmb;
			connectNmb_++;
		}
		else if (collectKinds[1] == elementNmb_ && elementNmb_ != Nmb && collectKinds[0] != Nmb ) {
			collectKinds[1] = Nmb;
			connectNmb_++;
		}
		else if (collectKinds[2] == elementNmb_ && elementNmb_ != Nmb && collectKinds[0] != Nmb && collectKinds[1] != Nmb) {
			collectKinds[2] = Nmb;
			connectNmb_++;
		}
		
	
}






