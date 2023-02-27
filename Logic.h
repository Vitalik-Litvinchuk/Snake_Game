#pragma once
#include "SnakeCore.h"
#include <iostream>
#include <random>
#include <conio.h>
#include <ctime>
#include <Windows.h>

using std::cout;
using std::endl;
using std::cin;
using std::swap;
using namespace Snake_Core;

enum Arrows
{
	Up_Arrow = 72,
	Down_Arrow = 80,
	Right_Arrow = 77,
	Left_Arrow = 75
};

void start();

void printField(Field&);

void printArea(Field&);

void randomGenerateApple(Field&);

bool move(Field&, Snake&, char);

bool directionValidation(char);

bool directionOppose(char, char);

void switchDirection(char, unsigned short&, unsigned short&, bool = false);

BOOL ShowConsoleCursor(BOOL);

void StartCursor(const SHORT = 0, const SHORT = 0);
