

enum eScene 
{
	SCENE_TITLE,
	SCENE_GAME,
	SCENE_RESULT,
	SCENE_LOGO,
};

class Scene;

class SceneManager
{
	
private:
	SceneManager();
	~SceneManager();

private:
	static SceneManager* _instance;

public:
	static SceneManager* GetInstance();

	void Render();
	void Update(int deltaTime);

	void KeyUp(unsigned int keyCode);
	void KeyDown(unsigned int keyCode);

	void ChangeScene(eScene sceneType);
	void DeInit();

private:
	Scene* _scene;
};