#include "DxLib.h"
#include "Effect.h"
#include "SceneBase.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultScene.h"
#include "Utility.h"
#include "UserInput.h"
//しーんを作るのに必要
SceneBase* MakeScene(SceneType _NowSceneType);
//ひとつ前のシーン
SceneType prevSceneType = SceneType::TITLE;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	ChangeWindowMode(true);

	// DirectX11を使用するようにする。(DirectX9も可、一部機能不可)
	// Effekseerを使用するには必ず設定する。
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// 画面の解像度と色ビット深度を設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);
	SetZBufferBitDepth(24);


	// １メートルに相当する値を設定する
	Set3DSoundOneMetre(16.0f);
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	//Effekseerを初期化する
	if (Effect_Initialize() == -1) 
	{
		DxLib_End();
		return -1;
	}

	// 描画先を裏画面に変更
	SetDrawScreen(DX_SCREEN_BACK);
	//今のシーン
	SceneType nowSceneType = SceneType::TITLE;
	//シーンを生成
	SceneBase* scene = new TitleScene;

	UserInput* userInput = new UserInput;

	//ゲームループ エスケープキーを押したら終了
	while (ProcessMessage() == 0 && !CheckHitKey(KEY_INPUT_ESCAPE))
	{

#ifdef _DEBUG
		clsDx(); // printfDx の結果をリセットするための関数.
#endif	// ここでDEBUG用の処理を終了.
		
		//更新
		userInput->Update();
		nowSceneType = scene->Update();
		Effect_Update();

		//画面を初期化する
		ClearDrawScreen();

		scene->Draw();//描画
		Effect_Draw();
		//裏画面の内容を表画面に反映させる
		ScreenFlip();
		//Updateで次のシーンに更新したなら
		if (nowSceneType != prevSceneType)
		{
			SAFE_DELETE(scene);//シーンの開放
			//新しいシーンの作成
			scene = MakeScene(nowSceneType);
		}
		//直前のシーンを記録
		prevSceneType = nowSceneType;
	}
	
	SAFE_DELETE(userInput);
	SAFE_DELETE(scene);
	Effect_Finalize();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
/// <summary>
/// 新しく使うシーンを確保
/// </summary>
/// <param name="_NowSceneType"></param>
/// <returns></returns>
SceneBase* MakeScene(SceneType _NowSceneType)
{
	SceneBase* retScene = nullptr;
	switch (_NowSceneType)
	{
	case SceneType::RELOAD:
		retScene = MakeScene(prevSceneType);
		break;
	case SceneType::TITLE:
		retScene = new TitleScene;
		break;
	case SceneType::PLAY:
		retScene = new PlayScene;
		break;
	case SceneType::RESULT:
		retScene = new ResultScene;
		break;
	default:
		break;
	}
	return retScene;
}
