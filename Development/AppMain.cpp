#include"DxLib.h"
#include"Utility/InputControl.h"
#include "Scene/Scene.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrebInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{

	//�E�B���h�E���[�h�ŋN��
	ChangeWindowMode(TRUE);


	SetGraphMode(640, 480, 32);

	//Dx���C�u�����̏������̏���
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	Scene* scene = new Scene();
	int result = 0;

	SetDrawScreen(DX_SCREEN_BACK);

	try
	{
		scene->Initialize();

		while (ProcessMessage() != -1 && CheckHitKey(KEY_INPUT_ESCAPE) != TRUE)
		{
			InputControl::Update();

			scene->Update();

			ClearDrawScreen();

			scene->Draw();

			ScreenFlip();
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
	//Dx���C�t���̎g�p�̏I������
	DxLib_End();

	return result;

}