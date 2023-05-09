// 自机、敌机等角色
// for various player/enemy, create directories to store the derived classes
#pragma once
#include <string>
#include "object.hpp" 
#include "enums.hpp"

extern const unsigned int WINDOW_WIDTH;
extern const unsigned int WINDOW_HEIGHT;

class Character : public Object {
public:
	virtual void destory() = 0;
};

