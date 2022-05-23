#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <string>
#include "LoaderParams.h"

// 抽象基类
class GameObject
{
public:
	virtual void load(const LoaderParams* pParams) = 0;
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;

protected:
	// “数据加载”不再使用函数，而是交由专门的类处理
	GameObject() {}
	virtual ~GameObject() {}
};

#endif // __GAMEOBJECT_H__