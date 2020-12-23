#pragma once
#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <iostream>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include <time.h>
#include "SDL_mixer.h"
#define FPS 60
#define WIDTH 1024
#define HEIGHT 768
//#define SPEED 5;

using namespace std;

class Sprite
{
protected:
	SDL_Rect m_src; //Source rectangle
	SDL_Rect m_dst; //Destination rectangle

public:
	void SetReks(const SDL_Rect s, const SDL_Rect d)
	{
		m_src = s;
		m_dst = d;
	}
	SDL_Rect* GetSrc() { return &m_src; }
	SDL_Rect* GetDst() { return &m_dst; }
	~Sprite()
	{
		cout << "destroyed";
	}
};


class Enemy : Sprite
{
private:
	SDL_Rect m_dst;
public:
	
	Enemy()
	{
		
		m_src = { 0,0,665,665 };
		m_dst ={ 1300,rand() % 720,100,100};

	}
	void Render(SDL_Renderer* rend,SDL_Texture* eTex)
	{
		SDL_RenderCopyEx(rend, eTex, &m_src, &m_dst, -90.0, NULL, SDL_FLIP_NONE);
	}
	SDL_Rect* GetRekt()
	{
		return &m_dst;
	}
	void SetDest(int a)
	{
		
	}
};
class Asteroid : Sprite
{
private:
	SDL_Rect m_dst;
	int asteroidAng = rand() % 180;
	int rotateSpeed = rand() % 5;

public:

	Asteroid()
	{

		m_src = { 0,0,800,800 };
		m_dst = { 1300,(rand() % 8) *100,100,100 };

	}
	void Render(SDL_Renderer* rend, SDL_Texture* eTex)
	{
		SDL_RenderCopyEx(rend, eTex, &m_src, &m_dst,asteroidAng, NULL, SDL_FLIP_NONE);
	}
	SDL_Rect* GetRekt()
	{
		return &m_dst;
	}
	void SetDest(int a)
	{

	}
	void Update()
	{
		asteroidAng += rotateSpeed;
	}
};


class Bullet
{
private:
	SDL_Rect m_rect;// Single rectangle for destination.
public:
	
	Bullet(SDL_Point spawnloc = { 512,384 })// Non-default constructor.
	{
		cout << "you got the bullet!" <<& (*this);
		this->m_rect.x = spawnloc.x;// this-> is optional.
		this->m_rect.y = spawnloc.y;
		this->m_rect.w = 7;
		this->m_rect.h = 7;
		//m_rect = {spawnLoc.x,spawnLoc.y,4,4};//short way
	}
	~Bullet()//Destructor
	{
		cout << "De-allocating Bullet at " << &(*this) << endl;
	}
	void Update()
	{
		this->m_rect.x += 10;//number is translation
	}
	void UpdateE()
	{
		this->m_rect.x -= 10;
	}
	void Setloc(SDL_Point loc)
	{
		m_rect.x = loc.x;
		m_rect.y = loc.y;
	}
	void Render(SDL_Renderer* rend)
	{
		SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
		SDL_RenderFillRect(rend, &m_rect);
	}
	void RenderE(SDL_Renderer* rendE)
	{
		SDL_SetRenderDrawColor(rendE, 255, 0, 0, 255);
		SDL_RenderFillRect(rendE, &m_rect);
	}
		
	SDL_Rect* GetRekt(){ return &m_rect; };
};

class Engine
{
private: // private properties 
	bool m_running = false;
	Uint32 m_start, m_end, m_delta, m_fps;
	const Uint8* m_keystates;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	
	SDL_Texture* m_pTexture;//Player texture.
	SDL_Texture* m_pBGTexture;//Background texture.
	SDL_Texture* m_eTexture;//Enemy texture.
	SDL_Texture* m_astTexture;
	Sprite m_player, m_bg1, m_bg2;

	//SDL_Rect m_dest; // Rectangle struct  with four integers: x y w(width) h(height).
	int m_speed = 5;
	vector<Bullet*> m_bullets,m_eBullets;
	vector<Enemy*> m_enemys;
	vector<Asteroid*> m_asteroids;
	int timerSpawn=0, timerShoot = 0,timerAsteroid = 0;

	Mix_Chunk* m_pShot = nullptr;
	Mix_Chunk* m_eShot = nullptr;
	Mix_Chunk* m_explosion = nullptr;
	Mix_Chunk* m_astrExplosion = nullptr;
	Mix_Music* m_ihtimaller = nullptr;



private: // private method prototypes.
	int Init(const char* title, int xPos, int yPos, int width, int height, int flags);
	void Clean();
	void Wake();
	void HandleEvent();
	bool KeyDown(SDL_Scancode c);
	void Update();
	void Render();
	void Sleep();


public: // public method prototypes.
	int Run();

};

#endif // !_ENGINE_H_

//Reminder: you can ONLY have declarations in headers, not logical code.