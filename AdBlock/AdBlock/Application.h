#pragma once

#include <memory>
#include "AdModel.h"

class Application
{
public:
	Application();
	virtual ~Application();

public:
	//brief:应用程序运行入口 
	void run();
private:

	std::unique_ptr<AdModel> _adModel;
};

