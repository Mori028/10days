#pragma once

//マップ横幅
static const int mapWidth = 6;
//マップ縦幅
static const int mapHeight = 6;
//総マップ数
static const int mapMax = 2;

//マップ
static int baseMap[mapHeight][mapWidth] = {
	{0,0,0,0,0,0},
	{0,0,0,0,0,0},
	{0,0,0,0,0,0},
	{0,0,0,0,0,0},
	{0,0,0,0,0,0},
	{0,0,0,0,0,0},
};

static int tutorialMap[mapHeight][mapWidth]{
	{1,0,0,0,0,1},
	{0,0,0,0,0,0},
	{0,0,0,0,0,0},
	{0,0,0,0,0,0},
	{0,0,0,0,0,0},
	{1,0,0,0,0,1},
};

static int map1[mapHeight][mapWidth]{
	{0,0,0,1,0,1},
	{0,0,0,0,0,0},
	{0,0,0,0,0,0},
	{0,0,1,0,0,1},
	{0,0,0,1,0,0},
	{1,0,0,0,0,0},
};

static int map2[mapHeight][mapWidth]{
	{0,0,0,0,0,0},
	{0,0,0,0,0,0},
	{0,0,0,0,0,0},
	{0,0,1,0,0,0},
	{0,0,0,0,0,0},
	{0,0,1,0,0,0},
};