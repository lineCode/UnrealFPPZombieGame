#pragma once

template<class  T>
class TMockBuilder
{
public:
	virtual T* Construct() { return NewObject<T>(); }
};
