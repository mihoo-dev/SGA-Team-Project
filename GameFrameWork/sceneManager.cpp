#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"



sceneManager::sceneManager()
{

}


sceneManager::~sceneManager()
{
}

DWORD CALLBACK loadingThread(LPVOID prc)
{
	//교체될 씬을 미리 초기화 해둔다
	sceneManager::_readyScene->init();

	//씬 교체를 해준다
	sceneManager::_currentScene = sceneManager::_readyScene;

	//로딩에 사용된 씬 해제
	sceneManager::_loadingScene->release();
	//로딩에 사용된 씬과 대기해뒀던 씬 초기화
	sceneManager::_loadingScene = NULL;
	sceneManager::_readyScene = NULL;

	//중요한건 쓸일이 없다는게 또르르르릌...

	return 0;
}

gameNode* sceneManager::_currentScene = NULL;
gameNode* sceneManager::_loadingScene = NULL;
gameNode* sceneManager::_readyScene = NULL;

HRESULT sceneManager::init()
{
	_currentScene = NULL;
	_loadingScene = NULL;
	_readyScene = NULL;

	return S_OK;
}

void sceneManager::release()
{

}

void sceneManager::update()	
{
	if (_currentScene) _currentScene->update();
}

void sceneManager::render()	
{
	if (_currentScene) _currentScene->render();
}


//씬 추가 함수        부를 씬 이름,    해당 씬
gameNode* sceneManager::addScene(string sceneName, gameNode* scene)
{
	if (!scene) return NULL;

	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

gameNode* sceneManager::addLoadingScene(string loadingSceneName, gameNode* scene)
{
	if (!scene) return NULL;

    _mLoadingSceneList.insert(make_pair(loadingSceneName, scene));

	return scene;
}


//씬 변경
HRESULT sceneManager::changeScene(string sceneName)
{
	//찾고자하는 씬의 키 값 대입
	mapSceneIter find = _mSceneList.find(sceneName);

	//못찾았으면
	if (find == _mSceneList.end()) return E_FAIL;
	if (find->second == _currentScene) return S_OK;

    
	//씬 체인지가 성공하면 init함수를 실행한다
	if (SUCCEEDED(find->second->init()))
	{
		//현재 씬이 있다면 기존의 씬은 해제
		if (_currentScene) _currentScene->release();

		//현재 씬에 바꾸려는 씬을 대입한다
		_currentScene = find->second;
		//이 구조는 나중에 여러분이 입맛에 따라 바꿔도 된다
		
		return S_OK;
	}

	return E_FAIL;
}

HRESULT sceneManager::changeScene(string sceneName, string loadingSceneName)
{
	//찾고자하는 씬의 키 값 대입
	mapSceneIter find = _mSceneList.find(sceneName);

	//못찾았으면
	if (find == _mSceneList.end()) return E_FAIL;
	if (find->second == _currentScene) return S_OK;

	//로딩에 사용할 씬 찾는다
	mapSceneIter findLoading = _mLoadingSceneList.find(loadingSceneName);

	if (findLoading == _mLoadingSceneList.end()) return changeScene(sceneName);

	//씬 체인지가 성공하면 init함수를 실행한다
	if (SUCCEEDED(findLoading->second->init()))
	{
		//현재 씬이 있다면 기존의 씬은 해제
		if (_currentScene) _currentScene->release();

		_loadingScene = findLoading->second;

        //현재 씬을 로딩씬으로 바꿔주고
        _currentScene = _loadingScene;
        //다음 씬을 저장
        _readyScene = find->second;

		//이 구조는 나중에 여러분이 입맛에 따라 바꿔도 된다

		//로딩에 사용한 쓰레드는 닫아준다
		CloseHandle(CreateThread(NULL, 0, loadingThread, NULL, 0, &_loadingThreadID));

		return S_OK;
	}

	return E_FAIL;
}


