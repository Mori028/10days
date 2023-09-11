#include"Title.h"

Title::Title() {

}

Title::~Title() {

}

void Title::Initialize(DirectXCommon* dxCommon, Input* input) {
	// nullptrチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	input_ = input;
	camTransForm = new Transform();

	HModel_ = Model::LoadFromOBJ("H");
	HObj_ = Object3d::Create();
	HObj_->SetModel(HModel_);
	HObj_->wtf.position = worldPos;
	HObj_->wtf.scale = { 0.3f,0.3f,0.3f };

	
}

void Title::Update() {

	HObj_->Update();

}

void Title::Draw() {
	HObj_->Draw();
}