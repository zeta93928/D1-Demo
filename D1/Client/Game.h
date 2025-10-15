#pragma once

class Actor;

class Game : public IEngine
{
public:
	Game();
	virtual ~Game();

	/* Start IEngine Interface */
	virtual bool __stdcall Init() override;
	virtual void __stdcall Update() override;
	virtual void __stdcall Render() override;
	virtual void __stdcall Release() override;
	/* End IEngine Interface */

private:
	ActorRef m_actor = nullptr;
};


