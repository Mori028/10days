#pragma once

//�}�b�v����
static const int mapWidth = 6;
//�}�b�v�c��
static const int mapHeight = 6;
//���}�b�v��
static const int mapMax = 2;

//�}�b�v
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