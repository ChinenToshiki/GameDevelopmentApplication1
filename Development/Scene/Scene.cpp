#include"Scene.h"
#include"../Utility/InputControl.h"
#include"../Object/Player/Player.h"
#include "../Object/Enemy/Enemy.h"
#include"../Object/Enemy/Bullet.h"
#include"../Object/Player/Bom.h"
#include <DxLib.h>

// *****定数設定*****
#define ScoreDraw_Left_x   (200)
#define ScoreDraw_Right_x  (ScoreDraw_Left_x  + 60)
#define ScoreDraw_Upper_y  (670)
#define ScoreDraw_Botom_y  (ScoreDraw_Upper_y + 50)
/*---------------------------------------------------*/
#define HightScore_Left_x  (620)
#define HightScore_Right_x (HightScore_Left_x+ 80)

Scene::Scene() :
	objects(),
	player(nullptr),
	Score(),
	Timer(60),
	EnemyCount(),
	isFinish(false)
{
	for (int i = 0; i < 10; i++)
	{
		NumberImage[i] = NULL;
	}
}

Scene::~Scene()
{
	Finalize();
}

void Scene::Initialize()
{
	//背景画像
	BackGround = LoadGraph("Resource/Images/BackGround.png");

	//スコア関係
	ScoreText[0] = LoadGraph("Resource/Images/Evaluation/Perfect.png");
	ScoreText[1] = LoadGraph("Resource/Images/Evaluation/GOOD.png");
	ScoreText[2] = LoadGraph("Resource/Images/Evaluation/OK.png");
	ScoreText[3] = LoadGraph("Resource/Images/Evaluation/BAD.png");

	ScoreImage = LoadGraph("Resource/Images/Score/sc.png");
	HightScoreImage = LoadGraph("Resource/Images/Score/hs.png");

	//タイマー関係
	TimerImage = LoadGraph("Resource/Images/TimeLimit/timer-03.png");

	//その他イラスト
	LoadDivGraph("Resource/Images/Score/Number_ALL.png", 10, 5, 2, 160, 214, NumberImage);
	EndText = LoadGraph("Resource/Images/Evaluation/Finish.png");

	//プレイヤーのインスタンスを保存
	player = CreateObject<Player>(Vector2D(320.0f, 50.0f));
}

void Scene::Update()
{
	if (isFinish == false)
	{
		for (int i = 0; i < objects.size(); i++)
		{
			objects.at(i)->Update();
		}

		for (int i = 0; i < objects.size(); i++)
		{
			for (int j = i + 1; j < objects.size(); j++)
			{
				HitCheckObject(objects[i], objects[j]);
			}
		}

		//時間を加算
		TimeCount();

		//エネミーを生成する
		if (EnemyCount < 20 && 20 > GetRand(EnemyCount * 100))
		{
			CreateObject<Enemy>(Vector2D(SpawnRand(), (float)GetRand(300) + 300.0f))->SetPlayer(player);
			EnemyCount++;
		}

		if (Timer < 0)
		{
			Finish();
		}
	}
	else {

	}
}

float Scene::SpawnRand()
{
	//右か左かを設定する
	if (GetRand(1) == 0)
	{
		return 0.0f;
	}
	else {
		return 920.0f;
	}

}

//スポーン上限値を減らす
void Scene::DownEnemyCount()
{
	EnemyCount--;
}

//タイマーを減らす
void Scene::DownTimer()
{
	this->Timer -= Timer/12;
}

void Scene::Finish()
{
	objects.clear();
	isFinish = true;
}

//AnimCountと同じような動き
void Scene::TimeCount()
{
	TimerCount++;

	if (TimerCount > 60)
	{
		TimerCount = 0;
		Timer -= 1;
	}
}



void Scene::Draw() const
{
	DrawGraph(0, 0, BackGround, true);

	if (isFinish == false)
	{
		for (GameObject* obj : objects)
		{
			obj->Draw();
		}
	}
	else {
		DrawGraph(460, 360, EndText, TRUE);
	}

	//TimerとScoreを表示する
	DrawExtendGraph(30, 670, 80, 720, TimerImage, TRUE);
	DrawExtendGraph(ScoreDraw_Left_x, ScoreDraw_Upper_y, ScoreDraw_Right_x,  ScoreDraw_Botom_y, ScoreImage     , TRUE);
	DrawUI();
	DrawExtendGraph(HightScore_Left_x,ScoreDraw_Upper_y, HightScore_Right_x, ScoreDraw_Botom_y, HightScoreImage, TRUE);
}

//TimerとScoreを表示する
void Scene::DrawUI()const 
{	
	int i = 0;
	//-----------Timer-----------//
	char SetTimer[2] = { 0,0 };
	int time = Timer;
	SetTimer[0] = time / 10;
	time = time - (time / 10)*10;
	SetTimer[1] = time;

	for (i = 0; i < 2; i++)
	{
			DrawExtendGraph(100 + 30 * i, ScoreDraw_Upper_y, 120 + 30 * i, ScoreDraw_Botom_y, NumberImage[SetTimer[i]], TRUE);
	}

	//----------- Score-----------//
	//スコアの数値を分割 
	char SetScore[5] = { 0,0,0,0,0 };
	int score = Score;
	i = 0; int j = 10000;
	//表示する桁数
	while(j > 0)
	{
			SetScore[i] = score / j;
			score -= (score / j)*j ;
			i++;
			j = j / 10;
	}
	//スコアの描画処理
	if (Score == 0)
	{
		SetScore[0] = -1;
		SetScore[1] = -1;
		SetScore[2] = -1;
		SetScore[3] = -1;
		SetScore[4] = -1;
	}
	else if (Score < 10)
	{
		SetScore[0] = -1;
		SetScore[1] = -1;
		SetScore[2] = -1;
		SetScore[3] = -1;

	}
	else if (Score < 100)
	{
		SetScore[0] = -1;
		SetScore[1] = -1;
		SetScore[2] = -1;
	}
	else if (Score < 1000)
	{
		SetScore[0] = -1;
		SetScore[1] = -1;
	}
	else {
		SetScore[0] = -1;
	}

	//追記.スコアもタイムも桁が変わる際にその桁以外のを消すことによって表示を簡略化している。時間があれば直したい、

	for (i = 0; i < 5; i++)
	{
		if (SetScore[i] > -1)
		{
			DrawExtendGraph(280 + 30 * i, ScoreDraw_Upper_y, 300 + 30 * i, ScoreDraw_Botom_y, NumberImage[SetScore[i]], TRUE);
		}
	}

}


void Scene::Finalize()
{
	DeleteGraph(BackGround);
	DeleteGraph(ScoreImage);
	DeleteGraph(HightScoreImage);

	if (objects.empty())
	{
		return;
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects.at(i)->Finalize();
		objects.erase(objects.begin() + i);
	}

	objects.clear();
}

//Enemy側からスコアを加算するための関数
void Scene::ScoreUpdate(int HitScore)
{
	this->Score += HitScore;
}

#ifdef D_PIVOT_CENTER
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{

	Vector2D diff = a->GetLocation() - b->GetLocation();

	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	{
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}
#else
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	Vector2D a_lower_right = a->GetLocation() + a->GetBoxSize();
	Vector2D b_lower_right = b->GetLocation() + b->GetBoxSize();

	if ((a->GetLocation().x < b_lower_right.x) &&
		(a->GetLocation().y < b_lower_right.y) &&
		(a_lower_right.x > b->GetLocation().x) &&
		(a_lower_right.y > b->GetLocation().y))
	{
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}
#endif //D_PIVOT_CENTER