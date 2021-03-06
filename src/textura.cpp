#include "../include/textura.h"
#include <iostream>

using namespace std;

SDL_Texture* Textura::loadTexture() {
	// Textura final
	SDL_Texture* newTexture = NULL;

	// Carrega imagem a partir de um caminho
	SDL_Surface* loadedSurface = IMG_Load(this->pPath.c_str());
	if (loadedSurface == NULL) {
		cout << "Unable to load image " << this->pPath.c_str() << ". SDL_Image Error: " << IMG_GetError() << endl;
	} else {
		// Cria textura dos pixels da superficie
		newTexture = SDL_CreateTextureFromSurface(this->pRenderer, loadedSurface);
		if ( newTexture == NULL) {
			cout << "Unable to create texture from " << this->pPath.c_str() << ". SDL Error: " << SDL_GetError() << endl;
		}

		// Deleta a superficie
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

Textura::Textura(string path, SDL_Renderer* renderer, int x, int y, int w, int h):pPath(path) {
	this->pRenderer = renderer;
	this->pTexture = this->loadTexture();
	this->recFormat.x = x;
	this->recFormat.y = y;
	this->recFormat.w = w;
	this->recFormat.h = h;
}

SDL_Point Textura::getSize() const {
	return {this->recFormat.w, this->recFormat.h};
}
void Textura::setSize(int w, int h) {
	this->recFormat.w = w;
	this->recFormat.h = h;
}

SDL_Point Textura::getPosition() const {
	return {this->recFormat.x, this->recFormat.y};
}
void Textura::setPosition(SDL_Point coord) {
	this->recFormat.x = coord.x;
	this->recFormat.y = coord.y;
}
SDL_Texture* Textura::getTexture() const {
	return this->pTexture;
}
void Textura::render() {
	SDL_RenderCopy(this->pRenderer, this->pTexture, NULL, &this->recFormat);
}
