#include "Application.h"



Application::Application()
	: _adModel(std::make_unique<AdModel>())
{
}


Application::~Application()
{
}

void Application::run()
{
	_adModel->Start();
}
