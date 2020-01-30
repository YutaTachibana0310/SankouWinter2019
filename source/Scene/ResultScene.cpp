//=====================================
//
//ResultScene.cpp
//�@�\:���U���g�V�[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "ResultScene.h"
#include "../../Framework/Camera/Camera.h"
#include "../../Framework/PostEffect/BloomController.h"
#include "../../Framework/Tool/DebugWindow.h"

#include "../Viewer/Result/ResultViewer.h"
#include "../System/ScoreRanking.h"
#include "../Viewer/Result/RankingViewer.h"

/**************************************
�O���[�o���ϐ�
***************************************/
const float BloomPower[] = { 0.9f, 0.9f, 0.2f };		//�u���[���̋���
const float BloomThrethold[] = { 0.95f, 0.95f, 0.95f };		//�u���[����������P�x��臒l

/**************************************
����������
***************************************/
void ResultScene::Init()
{
	sceneCamera = new Camera();
	Camera::SetMainCamera(sceneCamera);

	viewer = new ResultViewer();
	ranking = new ScoreRanking();
	rankViewer = new RankingViewer();
	bloom = new BloomController();

	bloom->SetPower(BloomPower[0], BloomPower[1], BloomPower[2]);
	bloom->SetThrethold(BloomThrethold[0], BloomThrethold[1], BloomThrethold[2]);

	ranking->CheckUpdate();

	auto rankingContainer = ranking->GetRanking();
	rankViewer->SetRanking(rankingContainer);
}

/**************************************
�I������
***************************************/
void ResultScene::Uninit()
{
	SAFE_DELETE(sceneCamera);
	SAFE_DELETE(viewer);
	SAFE_DELETE(ranking);
	SAFE_DELETE(rankViewer);
	SAFE_DELETE(bloom);
}

/**************************************
�X�V����
***************************************/
void ResultScene::Update()
{
	sceneCamera->Update();
	viewer->Update();
	rankViewer->Update();
}

/**************************************
�`�揈��
***************************************/
void ResultScene::Draw()
{
	sceneCamera->Set();
	viewer->Draw();
	rankViewer->Draw();

	bloom->Draw(renderTexture);
}
