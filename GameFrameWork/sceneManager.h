#pragma once
#include "singletonBase.h"
#include <map>

//gameNode 전방선언
class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
public:
	typedef map<string, gameNode*>				mapSceneList;
	typedef map<string, gameNode*>::iterator	mapSceneIter;

private:
	static gameNode* _currentScene;	//현재 씬
	static gameNode* _loadingScene;	//로딩 씬(혹시 몰라서)
	static gameNode* _readyScene;	//로딩끝난다음 체인지 해줄 대기 씬(호옥시 몰라서2)

	mapSceneList _mSceneList;			//씬 리스트
	mapSceneList _mLoadingSceneList;	//로딩 씬 리스트 (나중에 니네가 잘 만들어바밤)

	DWORD _loadingThreadID;				//호오오옥 시이이 몰라서 넣어놓는 로딩 쓰레드용 ID

public:
	sceneManager();
	~sceneManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//씬 추가 함수        부를 씬 이름,    해당 씬
	gameNode* addScene(string sceneName, gameNode* scene);
	gameNode* addLoadingScene(string loadingSceneName, gameNode* scene);

	//씬 변경
	HRESULT changeScene(string sceneName);
	HRESULT changeScene(string sceneName, string loadingSceneName);


	//프렌드 남발하면 결코 안되는 아주 좋은(?) 것
	//객체의 private까지 바로 접근을 허용케 해준다
	//함수 friend가 있고 클래스 friend가 있다
	//무적권 한 번은 꼭 사용해야 한다면 하나 정도는 써주자
	friend DWORD CALLBACK loadingThread(LPVOID prc);
};

