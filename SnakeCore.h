#pragma once
#include "Snake.h"
#include <vector>

using std::vector;

namespace Snake_Core
{
	class Field
	{
	private:
		Snake_Game::FieldPart*** field;
		unsigned short size;
	public:
		Field(unsigned short size)
		{
			this->size = size;

			field = new Snake_Game::FieldPart * *[size];

			for (size_t i = 0; i < size; i++)
			{
				field[i] = new Snake_Game::FieldPart * [size];

				for (size_t b = 0; b < size; b++)
					field[i][b] = new Snake_Game::FieldPart();
			}
		}

		Snake_Game::FieldPart***& getField()
		{
			return field;
		}

		unsigned short getSize()
		{
			return size;
		}

		~Field()
		{
			for (size_t i = 0; i < this->size; i++)
				delete[] field[i];

			delete[] field;
		}

		template<typename T>
		Snake_Game::FieldPart**& operator[](T index)
		{
			return field[index];
		}
	};

	class Snake
	{
		vector<Snake_Game::SnakePart*> snake;
	public:
		Snake()
		{
			Snake_Game::SnakePart* sp = new Snake_Game::SnakePart();
			snake.push_back(sp);
		}

		vector<Snake_Game::SnakePart*>& getSnake()
		{
			return snake;
		}

		Snake_Game::SnakePart*& getLast()
		{
			return snake.at(snake.size() - 1);
		}

		inline size_t size()
		{
			return snake.size();
		}

		inline void push_back(Snake_Game::SnakePart*& snakePart)
		{
			snake.push_back(snakePart);
		}

		inline void pop_back()
		{
			snake.pop_back();
		}

		Snake_Game::SnakePart*& operator[] (int index)
		{
			return snake[index];
		}
	};

	class Apple : public Snake_Game::FieldPart, public Snake_Game::Increaser
	{
	public:
		Apple() : Snake_Game::Increaser(1)
		{
			char block = char(15);
			setBlock(block);
		}

		bool isInvisible() override
		{
			return false;
		};

		bool isLogicElement() override
		{
			return true;
		}

		bool isDestroyable() override
		{
			return true;
		}
	};
}