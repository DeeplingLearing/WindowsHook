#pragma once

#include <memory>
#include "AdModel.h"

class Application
{
public:
	Application();
	virtual ~Application();

public:
	//brief:Ӧ�ó���������� 
	void run();
private:

	std::unique_ptr<AdModel> _adModel;
};

