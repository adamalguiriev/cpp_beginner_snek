#pragma once

struct Location
{
	int x;
	int y;

	void operator += (const Location& val)
	{
		x += val.x;
		y += val.y;
	}

	void operator *= (const int val)
	{
		x *= val;
		y *= val;
	}

	Location operator + (const Location& val) const
	{
		return Location{ this->x + val.x, this->y + val.y };
	}

	Location operator - (int val) const
	{
		return Location{ this->x - val, this->y - val };
	}

	bool operator == (const Location& val) const
	{
		return (this->x == val.x && this->y == val.y);
	}

	bool operator == (const int val) const
	{
		return (this->x == val && this->y == val);
	}

	bool operator != (const int val) const
	{
		return !(*this == val);
	}

	//means further on the grid
	bool operator > (const Location& val) const
	{
		if (this->x > val.x || this->y > val.y)
		{
			return true;
		}

		return false;
	}

	bool operator >= (const Location& val) const
	{
		return (*this == val || *this > val);
	}

	bool operator < (const Location& val) const
	{
		if (this->x < val.x || this->y < val.y)
		{
			return true;
		}

		return false;
	}

	bool operator <= (const Location& val) const
	{
		return (*this == val) || (*this < val);
	}
};