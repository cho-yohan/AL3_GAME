#include "CameraController.h"
#include "Player.h"
#include <algorithm>

/// 初期化
void CameraController::Initialize() { viewProjection_.Initialize(); }

/// 更新
void CameraController::Update() {

	// 追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	Vector3 targetVelocity = target_->GetVelocity();

	destination_.x = viewProjection_.translation_.x;                                                             // X座標は現在のカメラの位置に保持
	destination_.y = targetWorldTransform.translation_.y + targetOffset_.y * targetVelocity.y + targetOffset_.y; // Y座標をプレイヤーの上下の動きに合わせる
	destination_.z = viewProjection_.translation_.z;                                                             // Z座標は現在のカメラの位置に保持

	viewProjection_.translation_.x = Lerp(viewProjection_.translation_.x, destination_.x, kInterpolationRate_);
	viewProjection_.translation_.y = Lerp(viewProjection_.translation_.y, destination_.y, kInterpolationRate_);
	viewProjection_.translation_.z = Lerp(viewProjection_.translation_.z, destination_.z, kInterpolationRate_);

	// 追従対象が画面外に出ないように補正
	viewProjection_.translation_.x = std::clamp(viewProjection_.translation_.x, targetWorldTransform.translation_.x + targetMargin.left, targetWorldTransform.translation_.x + targetMargin.right);
	viewProjection_.translation_.y = std::clamp(viewProjection_.translation_.y, targetWorldTransform.translation_.y + targetMargin.bottom, targetWorldTransform.translation_.y + targetMargin.top);

	// 移動範囲制限
	viewProjection_.translation_.x = std::clamp(viewProjection_.translation_.x, movableArea_.left, movableArea_.right);
	viewProjection_.translation_.y = std::clamp(viewProjection_.translation_.y, movableArea_.bottom, movableArea_.top);

	// 行列を更新する
	viewProjection_.UpdateMatrix();
}

void CameraController::Reset() {

	// 追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();

	// 追従対象とオフセットからカメラの座標を計算
	viewProjection_.translation_.x = targetWorldTransform.translation_.x + targetOffset_.x;
	viewProjection_.translation_.y = targetWorldTransform.translation_.y + targetOffset_.y;
	viewProjection_.translation_.z = targetWorldTransform.translation_.z + targetOffset_.z;
}