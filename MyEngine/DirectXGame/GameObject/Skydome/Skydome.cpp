#include "Skydome.h"

Skydome::Skydome(){}
Skydome::~Skydome(){}

void Skydome::Initialize() {
	model_ = Model::Create("Skydome");
	modelInfo_.Initialize();
	modelInfo_.worldTransform_.data_.scale_ *= 50;
}

void Skydome::Update() {
	
	modelInfo_.Update();
}

void Skydome::Draw() {
	model_->Draw(modelInfo_);
}