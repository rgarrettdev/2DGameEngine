#ifndef UITEXTCOMPONENT
#define UITEXTCOMPONENT

#include <SDL.h>
#include <SDL_ttf.h>
#include "../EntityManager.h"
#include "../AssetManager.h"
#include "../Engine.h"

class UiTextComponent : public Component
{
public:
	UiTextComponent(int x, int y, std::string text, std::string fontFamily, const SDL_Color& colour) {
		this->position.x = x;
		this->position.y = y;
		this->content = text;
		this->fontFamily = fontFamily;
		this->colour = colour;
		SetUIText(content, fontFamily);
	}
	void SetUIText(std::string text, std::string fontFamily) {
		SDL_Surface* surface = TTF_RenderText_Blended(Engine::assetManager->GetFont(fontFamily), text.c_str(), colour);
		texture = SDL_CreateTextureFromSurface(Engine::renderer, surface);
		SDL_FreeSurface(surface);
		SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
	}

	void Render() override {
		FontManager::Draw(texture, position);
	}

private:
	SDL_Rect position;
	std::string content;
	std::string fontFamily;
	SDL_Color colour;
	SDL_Texture* texture;
};

#endif // !UITEXTCOMPONENT

