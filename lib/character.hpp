// 自机、敌机等角色
// TODO: 如何设计敌机的射击方案等？
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

