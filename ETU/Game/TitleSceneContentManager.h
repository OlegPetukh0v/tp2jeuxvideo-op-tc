#pragma once
#include "ContentManager.h"
class TitleSceneContentManager : public ContentManager
{
public:
	TitleSceneContentManager();
	virtual bool loadContent() override;
	const sf::Texture& getBackgroundTexture() const;
private:
	sf::Texture menuImage;
};
