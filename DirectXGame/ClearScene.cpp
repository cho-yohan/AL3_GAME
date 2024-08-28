#define NOMINMAX

#include "DirectXCommon.h"
#include "Input.h"
#include "ClearScene.h"
#include <cmath>
#include <numbers>

ClearScene::~ClearScene() {
	delete modelTitle_;
}

void ClearScene::Initialize() {
	modelTitle_ = Model::CreateFromOBJ("text", true);
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	const float kTextTitle = 10.0f;
	worldTransformTitle_.Initialize();
	worldTransformTitle_.scale_ = {kTextTitle, kTextTitle, kTextTitle};
	worldTransformTitle_.rotation_.y = 0.99f * std::numbers::pi_v<float>;
}

void ClearScene::Update() {
	if (Input::GetInstance()->PushKey(DIK_SPACE)) {
		finished_ = true;
	}
	counter_ += 1.0f / 60.0f;
	counter_ = std::fmod(counter_, kTimeTitleMove);

	float angle = counter_ / kTimeTitleMove * 2.0f * std::numbers::pi_v<float>;

	worldTransformTitle_.translation_.y = std::sin(angle) + 10.0f;

	viewProjection_.TransferMatrix();
	worldTransformTitle_.UpdateMatrix();
}

void ClearScene::Draw() {
	DirectXCommon* dxCommon_ = DirectXCommon::GetInstance();
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	
	Model::PreDraw(commandList);
	modelTitle_->Draw(worldTransformTitle_, viewProjection_);
	Model::PostDraw();
}