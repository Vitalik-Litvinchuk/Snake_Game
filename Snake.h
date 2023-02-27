#pragma once
namespace Snake_Game
{
	class FieldPart
	{
	private:
		unsigned short x, y;
		char block;
	public:
		FieldPart()
		{
			x = 0;
			y = 0;
			block = '\0';
		}

		virtual bool isInvisible()
		{
			return true;
		};

		virtual bool isLogicElement()
		{
			return false;
		}

		virtual bool isDestroyable()
		{
			return false;
		}

		char getBlock()
		{
			return block;
		}

		unsigned short getX()
		{
			return x;
		}

		unsigned short getY()
		{
			return y;
		}

		void setBlock(char& block)
		{
			this->block = block;
		}

		void setX(unsigned short& x)
		{
			this->x = x;
		}

		void setY(unsigned short& y)
		{
			this->y = y;
		}

		void setCoords(unsigned short& x, unsigned short& y)
		{
			this->x = x;
			this->y = y;
		}
	};

	class Increaser
	{
	private:
		short points;
	public:
		Increaser(short points = 0)
		{
			this->points = points;
		}

		short getPoints()
		{
			return points;
		}
	};

	class SnakePart : public FieldPart
	{
	private:
		char direction;
	public:
		SnakePart()
		{
			char block = (char)219;
			setBlock(block);

			char direction = '\0';
			setDirection(direction);
		}

		char getDirection()
		{
			return direction;
		}

		void setDirection(char& direction)
		{
			this->direction = direction;
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
			return false;
		}

		SnakePart* operator= (SnakePart& snakepart)
		{
			unsigned short
				x = snakepart.getX(),
				y = snakepart.getY();

			this->setX(x);
			this->setY(y);

			char direction = snakepart.getDirection();

			this->setDirection(direction);

			return this;
		}
	};
}