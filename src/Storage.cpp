#include "Storage.h"

Storage * Storage::_storage = nullptr;

Storage & Storage::getInstance()
{
	if ( _storage == nullptr )
		_storage = new Storage;
	return *_storage;
}

Storage::Storage()
{

}
