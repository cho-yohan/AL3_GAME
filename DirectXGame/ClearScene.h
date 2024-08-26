#pragma once

#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"

class ClearScene {
public:
	~ClearScene();

	void Initialize();

	void Update();

	void Draw();

	bool IsFinished() const { return finished_; };

private:
	static inline const float kTimeTitleMove = 2.0f;

	ViewProjection viewProjection_;
	WorldTransform worldTransformTitle_;

	Model* modelTitle_ = nullptr;

	Player* player_ = nullptr;

	float counter_ = 0.0f;
	bool finished_ = false;
};