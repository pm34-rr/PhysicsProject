#pragma once

#define theStorage Storage::getInstance()

class Storage
{
public:
	static Storage & getInstance();

	inline int	getNumOfSprings()	{ return _numOfSprings; }
	inline void setNumOfSprings( int n ) {_numOfSprings = n; }

	inline int getPeriod()			{ return _period; }
	inline void setPeriod( int p )  { _period = p; }

protected:
	Storage();
	static Storage * _storage;

private:
	int	_numOfSprings;
	int _period;
};
