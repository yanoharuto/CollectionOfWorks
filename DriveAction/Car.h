#pragma once
#include "Item.h"
#include "CpuCarMode.h"
#include "DxLib.h"
#include "Actor.h"
#include "Wheels.h"
#include "CarNeighborhoodExamineInfo.h"
#include "CarParamater.h"
#include "InputDirection.h"
#include "ItemInfo.h"
#include "AutoDriveInfo.h"
#include "HitCheckExamineObjectInfo.h"
#include "ObjPosAndDir.h"
#include "Timer.h"
/// <summary>
/// 車の加速とか減速とかするよ。どの向きに加速するかとかはwheelsからとってくるよ
/// </summary>
class Car abstract :public Actor
{

public:
	Car();
	/// <summary>
	/// 初期位置や方角とか
	/// </summary>
	/// <param name="firstPos"></param>
	/// <param name="firstDir"></param>
	/// <param name="destinationPos"></param>
	/// <param name="soundPlayer"></param>
	Car(CarInfomation param);
    virtual ~Car();
	/// <summary>
    /// 更新（移動処理）
    /// </summary>
	virtual void Update(){};
	/// <summary>
	/// 衝突処理
	/// </summary>
	/// <param name="conflictInfo">ぶつかったかオブジェクトの情報</param>
	virtual void ConflictProccess(ConflictExamineResultInfo conflictInfo)override;
	/// <summary>
	/// 今の速度は最大速度の何割なのか所得出来る
	/// </summary>
	/// <returns></returns>
	float GetTotalAccelPowerPercent();
	/// <summary>
	/// 今の速度
	/// </summary>
	/// <returns></returns>
	float GetTotalAccelPower();
	/// <summary>
	/// 自動運転
	/// </summary>
	/// <param name="deltaTime"></param>
	/// <param name="outsideHitFlag"></param>
	void AutoDrive();
	/// <summary>
    /// カメラ等に渡したい情報を返す
    /// </summary>
	/// <returns></returns>
	ObjInfo GetCarPosAndDir();
	/// <summary>
	/// 移動する前のポジションを渡す
	/// </summary>
	/// <returns></returns>
	HitCheckExamineObjectInfo GetHitCheckExamineInfo() override;
	/// <summary>
	/// 落下
	/// </summary>
	/// <param name="deltaTime"></param>
	void UpDown();
protected:
	/// <summary>
	/// 共通更新
	/// </summary>
	/// <param name="deltaTime"></param>
	/// <param name="destinationPos"></param>
	/// <param name="itemInfo"></param>
	void CommonUpdate();

	/// <summary>
	/// 車がぶつかった時の関数
	/// </summary>
	/// <param name="conflictObjPos">ぶつかったオブジェクトの位置</param>
	/// <param name="conflictObjRad">ぶつかったオブジェクトの半径</param>
	virtual void ConflictReaction(const ConflictExamineResultInfo conflictInfo);
	/// <summary>
	/// 車がダメージ判定のある物体にぶつかった時の関数
	/// </summary>
	/// <param name="deltaTime"></param>
	/// <param name="conflictInfo"></param>
	virtual void DamageReaction(const ConflictExamineResultInfo conflictInfo);
	/// <summary>
	/// 主に車が攻撃を受けた後に無敵時間を解除する関数
	/// </summary>
	/// <param name="conflictObjPos">ぶつかったオブジェクトの位置</param>
	/// <param name="conflictObjRad">ぶつかったオブジェクトの半径</param>
	virtual void PostDamageProccess();
	/// <summary>
	/// 進む方向と速さを更新する
	/// </summary>
	/// <param name"deltaTime">経過時間</param>
	/// <param name="accelVec">次の更新までに進む方向と速さ</param>
	void UpdateVelocity(const VECTOR accelVec);
	/// <summary>
	/// modelの描画場所を更新
	/// </summary>
	void UpdateMV1Pos() override;
	/// <summary>
	/// 車を回転させる
	/// </summary>
	void ModelSetMatrix() override;
	/// <summary>
	/// このフレームの間に進む量を出す
	/// </summary>
	/// <param name="handleDir">入力された方向</param>
	/// <param name="outsideHitFlag">コースの外にいるか</param>
	/// <param name="deltaTime">経過時間</param>
	/// <param name="soundPlayer">音を出すやつ</param>
	/// <returns>進む量</returns>
	VECTOR GetAccelVec(InputInfo inputDir);
	/// <summary>
	/// 運転中になる音を再生する
	/// </summary>
	/// <param name="inputDir"></param>
	/// <param name="soundPlayer"></param>
	void PlayDriveSound(InputInfo inputDir);
	/// <summary>
	/// ぶつかった時の効果音を鳴らす
	/// </summary>
	void PlayConflictSound();
	/// <summary>
	/// ぶつかった時のエフェクトを出す
	/// </summary>
	void PlayConflictEffect();
	/// <summary>
	/// タイヤに渡す情報の初期化
	/// </summary>
	void InitWheelArgumentCarInfo();

	//車のパラメーター
	CarInfomation carParam;

	//走っているときに出るエフェクト
	int runEffect = -1;
	//ぶつかった時に出てくるエフェクト
	int conflictEffect = -1;
	//曲がったりするときに傾く速度
	const float twistZRotaSpeed = 1.7f * RAGE;
	//最大傾き度
	const float twistZMaxRota = 27.0f * RAGE;
	//縦に回転する
	float twistZRota = 0.0f;
	//速さ
	float accelPower = 0;
	//最初のY座標
	float firstPosY = 0;
	//コサインに使う
	float cosValue = 0;
	//cosValueに毎回足す
	float cosAddValue = 0.05f;
	//上下に動く速度
	float updownSpeed = 2.0f;
	//ダメージを受けた時の操作不可能時間
	float damageReactionTime = -1.0f;
	//modelのおおきさ
	float modelSize = 1.0f;
	//目的地に向かうときに曲がるか判断する
	float turnProccesAngularLine = 5.0f;
	//チェックポイントに当たってるか
	bool isGoalConflict = false;
	//地面に降りているか
	bool isOnGround = true;
	//ダメージ
	bool isDamage = false;
	//これ以下の速度になってたらaccelPowerを0にするよ
	static const float stopAccelLine;
	// なにもしない時の減速.
	static const float defaultDecel;
	// ブレーキ時の減速.
	static const float breakDecel;
	// グリップの減速.
	static const float gripDecel;
	// 障害物にぶつかったときの減速率.
	static const float colideDecel;
	//降りる速度
	static const float fallSpeed;
	//ダメージを受けた時の操作不可能時間の合計
	static const float setDamageReactionTime;
	//煙のエフェクト
	static const std::string smokeEffectResource;
	//ぶつかった時のエフェクト
	static const std::string conflictEffectResource;
	//風のエフェクト
	static const std::string windEffectResource;
	//止まった時の効果音
	static const std::string breakeSEPass;
	//ぶつかった時の効果音
	static const std::string carClashSEPass;
	//クラクションの効果音
	static const std::string carHornSEPass;
	//運転中の効果音
	static const std::string drivingSEPass;
	//ダメージを受けた後の無敵時間
	Timer* damageCoolTimer;
	//タイヤ
	Wheels* wheels;
	//ぶつかった物体との方向
	VECTOR collVec = {};
	//ひとつ前のポジション
	VECTOR prevPos = {};
	//タイヤに渡したい情報
	WheelArgumentCarInfo wheelArgumentCarInfo = {};
	AutoDriveInfo autoDriveP = {};
};
