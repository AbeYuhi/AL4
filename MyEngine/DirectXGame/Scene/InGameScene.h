#pragma once
#include <sstream>
#include "DirectXGame/Base/WinApp/WinApp.h"
#include "DirectXGame/Base/DirectXCommon/DirectXCommon.h"
#include "DirectXGame/Manager/ImGuiManager.h"
#include "DirectXGame/Manager/InputManager.h"
#include "DirectXGame/Manager/AudioManager.h"
#include "DirectXGame/Manager/ParticleManager.h"
#include "DirectXGame/Manager/RandomManager.h"
#include "DirectXGame/Manager/CollisionManager.h"
#include "DirectXGame/Object/Triangle.h"
#include "DirectXGame/Object/Sprite.h"
#include "DirectXGame/Object/Plane.h"
#include "DirectXGame/Object/Sphere.h"
#include "DirectXGame/Object/Model.h"
#include "DirectXGame/Object/WireFrameBox.h"
#include "DirectXGame/GameObject/Camera/MainCamera.h"
#include "DirectXGame/GameObject/Camera/InGameCamera.h"
#include "DirectXGame/GameObject/Camera/DebugCamera.h"
#include "DirectXGame/GameObject/Camera/RailCamera.h"
#include "DirectXGame/GameObject/Camera/SpriteCamera.h"
#include "DirectXGame/GameObject/Light/LightObject.h"
#include "DirectXGame/GameObject/Particle/testParticle.h"
#include "DirectXGame/GameObject/Entity/Player/Player.h"
#include "DirectXGame/GameObject/Entity/Enemy/Enemy.h"
#include "DirectXGame/GameObject/Skydome/Skydome.h"
#include "DirectXGame/Scene/IScene.h"

class InGameScene : public IScene {
public:
	InGameScene();
	~InGameScene();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

	void AddBulletEnemy(std::unique_ptr<EnemyBullet> enemyBullet);

	void PopEnemy(Vector3 enemyPos);

	void LoadEnemyPopData();

	void UpdateEnemyPopCommands();

	void CheckCollisionPair(Collider* colliderA, Collider* colliderB);

private:
	//基本機能
	WinApp* winApp_;
	DirectXCommon* directXCommon_;
	InputManager* input_;
	AudioManager* audioManager_;
	RandomManager* randomManager_;
	MainCamera* mainCamera_;
	SpriteCamera* spriteCamera_;
	//ゲームカメラ
	std::unique_ptr<InGameCamera> gameCamera_;
	//デバッグカメラ
	std::unique_ptr<DebugCamera> debugCamera_;
	bool isDebugCamera_;
	//レールカメラ
	std::unique_ptr<RailCamera> railCamera_;

	//ライト
	std::unique_ptr<LightObject> lightObj_;

	//ブレンドモード
	int blendMode_;

	//
	std::unique_ptr<CollisionManager> collisionManager_;

	std::unique_ptr<Player> player_;
	std::list < std::unique_ptr<Enemy>> enemys_;

	std::stringstream enemyPopCommands_;
	bool isWait_;
	int waitTime_;
	//弾
	std::list<std::unique_ptr<EnemyBullet>> enemyBullets_;

	std::unique_ptr<Skydome> skydome_;
};