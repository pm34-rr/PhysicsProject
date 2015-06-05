#pragma once

#define theStorage Storage::getInstance()

class Storage
{
public:
	static Storage & getInstance();

	inline int	getNumOfSprings()	{ return _numOfSprings; }
	inline void setNumOfSprings( int n ) {_numOfSprings = n; }


protected:
	Storage();
	static Storage * _storage;

private:
	int	_numOfSprings;
};
