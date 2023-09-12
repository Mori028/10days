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

	HModel_ = Model::LoadFromOBJ("Boll");
	HObj_ = Object3d::Create();
	HObj_->SetModel(HModel_);
	HObj_->wtf.position = { 0.0f,0.0f,10.0f };
	HObj_->wtf.scale = { 1.0f,1.0f,1.0f };

	
}

void Title::Update() {

	HObj_->Update();

}

void Title::Draw() {
	HObj_->Draw();
}