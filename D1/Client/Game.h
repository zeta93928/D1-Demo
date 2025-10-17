#pragma once

class Actor;

class Game : public IEngine
{
public:
	Game();
	virtual ~Game();

	/* Start IEngine Interface */
	virtual bool Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
	/* End IEngine Interface */

private:
	
};


