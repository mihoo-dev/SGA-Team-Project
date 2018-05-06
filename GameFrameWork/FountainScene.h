#pragma once
#include "gameNode.h"

class PlayerManager;

class FountainScene :	public gameNode
{
private:
	image*			_background;
	image*			_fountain;
	image*			_nymph1;
	image*			_nymph1Idle;
	image*			_nymph2;
	image*			_nymph2Idle;

	animation*		_aniFountain;
	animation*		_aniNymph1;
	animation*		_aniNymph1Idle;
	animation*		_aniNymph2;
	animation*		_aniNymph2Idle;

	PlayerManager*	_pm;

	BOOL			_dance;

	int				_endingCreditY;

	//페이드 화면
	int					_alpha;
	BOOL				_sceneStart;
	BOOL                _sceneChange;

public:
	FountainScene();
	~FountainScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void SceneStart();
	void CreditEnd();
	void GoEndScene();

	void UpCredit();
};

