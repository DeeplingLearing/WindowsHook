#include "AdModel.h"

AdModel::AdModel()
    : _state(MonitorState::STOP)
{
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    Gdiplus::GdiplusStartup(&_gdiplusToken, &gdiplusStartupInput, NULL);
}

AdModel::~AdModel()
{
    if (_adMonitor.joinable())
    {
        _adMonitor.join();
    }

    Gdiplus::GdiplusShutdown(_gdiplusToken);
}

void AdModel::Start()
{
    //加载黑白名单
    //LoadBlackAndWhiteList();
    //清除启动器启动前的广告窗口
    ClearAdWindows();

    //启动桌面窗口监视器
    HINSTANCE hInstance = GetModuleHandleW(NULL);
    _adMonitor = std::thread(std::bind(&AdModel::SetupAdMonitor, this, hInstance));
}

void AdModel::SetAdMonitorState(const MonitorState & state)
{
    std::lock_guard<std::mutex> lock(_stateMutex);
    _state = state;
}

void AdModel::ClearAdWindows()
{
    //枚举EnumWindows为阻塞函数
    EnumAdWindowsTool::SetCallback(std::bind(&AdModel::EnumTopLevelWindows, this, std::placeholders::_1));
    EnumAdWindowsTool::EnumTopLevelWindows();
}

void AdModel::HandleWindows(const WndParamter & wp)
{
    //1、是否在白名单中

    //2、是否在黑名单中

    //3、判断窗口是否为可疑窗口
}

void AdModel::GetCreateWindowsParamter(const WndParamter & wp)
{
    //判断窗口是否需要拦截
    HandleWindows(wp);

    wchar_t debug[1024] = { 0 };

    wsprintfW(debug, L"hwnd:%d\tclass:%s\ttitle:%s\tret:(%d, %d, %d, %d)\n", wp._hwnd, wp._class.c_str(), wp._text.c_str(), wp._rect.left, wp._rect.top, wp._rect.right, wp._rect.bottom);
    OutputDebugStringW(debug);
}

void AdModel::EnumTopLevelWindows(const WndParamter & wp)
{
    //判断窗口是否需要拦截
    HandleWindows(wp);
    wchar_t debug[1024] = { 0 };
    wsprintfW(debug, L"hwnd:%d\tclass:%s\ttitle:%s\tret:(%d, %d, %d, %d)\n", wp._hwnd, wp._class.c_str(), wp._text.c_str(), wp._rect.left, wp._rect.top, wp._rect.right, wp._rect.bottom);
    OutputDebugStringW(debug);
}

void AdModel::SetupAdMonitor(HINSTANCE hInstance)
{
    if (MonitorState::STOP != _state)
    {
        OutputDebugStringW(L"广告监视器已经开启!");
        return;
    }

    ShellHook shellHook;
    if (!shellHook.SetShellHook(hInstance))
    {
        OutputDebugStringW(L"安装钩子失败!");
        return;
    }

    shellHook._callback = std::bind(&AdModel::GetCreateWindowsParamter, this, std::placeholders::_1);

    _state = MonitorState::RUNNING;

    MSG msg;
    while (GetMessageW(&msg, NULL, 0, 0)) //这里是阻塞的，等有窗口消息的时候才会返回
    {
        if (MonitorState::RUNNING == _state)
        {
            //开启拦截
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else if (MonitorState::START == _state || MonitorState::SUSPEND == _state)
        {
            //开启拦截器但是未开启拦截或暂停拦截
        }
        else
        {
            //关闭广告弹出拦截器
            break;
        }
    }
}
