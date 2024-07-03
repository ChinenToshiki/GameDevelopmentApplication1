#include"DxLib.h"
#include"Utility/InputControl.h"
#include "Scene/Scene.h"

//画面デカくするわ
#define GraphSize 920, 720
//これデフォルトの大きさや
#define elseGraphSize 640,480

#define FPS (60)
#define FrameTime (1000/FPS)

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrebInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{

	//ウィンドウモードで起動
	ChangeWindowMode(TRUE);

	//Windowサイズの設定
	SetGraphMode(GraphSize, 32);

	//Dxライブラリの初期化の処理
	if (DxLib_Init() == -1)
	{
		return -1;
	}



	SetDrawScreen(DX_SCREEN_BACK);

	Scene* scene = new Scene();
	int result = 0;

	try
	{
		scene->Initialize();

		while (ProcessMessage() != -1 && CheckHitKey(KEY_INPUT_ESCAPE) != TRUE)
		{
			{
				// フレーム開始時刻を取得
				int startTime = GetNowCount();

				// 現在の時間から経過時間を計算
				int elapsedTime = GetNowCount() - startTime;

			InputControl::Update();

			scene->Update();

			ClearDrawScreen();

			scene->Draw();

			ScreenFlip();


			// 待機時間を計算
			int waitTime = FrameTime - elapsedTime;
			if (waitTime > 0) {
				WaitTimer(waitTime);
			}
			}

		}
	}
	catch (const char* error_log)
	{
		OutputDebugString(error_log);
		result = -1;
	}

	if (scene != nullptr)
	{
		scene->Finalize();
		delete scene;
		scene = nullptr;
	}
	//Dxライフらりの使用の終了処理
	DxLib_End();

	return result;

}