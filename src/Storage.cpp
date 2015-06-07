#include "Storage.h"

#include "caction.h"

Storage * Storage::_storage = nullptr;

Storage & Storage::getInstance()
{
	if ( _storage == nullptr )
		_storage = new Storage;
	return *_storage;
}

Storage::Storage()
{
	_numOfSprings = 3;
}
