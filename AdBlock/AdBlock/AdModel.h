#pragma once

#include "EnumAdWindowsTool.h"
#include "ShellHook.h"
#include <thread>
#include <mutex>
#include <vector>
#include <map>
//广告拦截器


//广告监视器运行状态
enum MonitorState
{
	START = 0,     //启动
	RUNNING = 1,   //运行
	SUSPEND = 2,   //挂起
	STOP = 3       //停止
};

//
struct AdParamter
{
	WndParamter _wnd; //窗口信息
	ProcessInfo _processInfo; //窗口进程信息

	std::wstring _iconImagePath; //图标图片路径
	std::wstring _firstCaptureImagePath; //首次截图图片
};

//广告统计
struct AdDataStatistics
{
	AdParamter _ad;
	bool _remoteAd; //设备可操作广告
	UINT64 _historyInterceptCount; //历史拦截次数（云端同步数据)
	UINT64 _localHistoryInterceptCount; //设备历史拦截次数（断网或未关联学校后，拦截从次数只在本地显示??)

};

class AdModel
{
public:
	AdModel();
	virtual ~AdModel();
public:
	//brief:启动广告拦截器
	void Start();
	void SetAdMonitorState(const MonitorState& state);
private:
	//brief:加载黑白名单
	void LoadBlackAndWhiteList();
	//brief:清除在监视器启动器的广告窗口
	void ClearAdWindows();
	//brief:判断窗口是否需要拦截函数过滤
	void HandleWindows(const WndParamter& wp);
	//brief:检测到有新窗口产生的时候回调
	void GetCreateWindowsParamter(const WndParamter& wp);
	//brief:枚举桌面顶级窗口回调函数
	void EnumTopLevelWindows(const WndParamter& wp);
	//brief:是否在白名单
	bool SearchInWhiteList(const AdParamter& ad);
	//brief:是否在黑名单中
	bool SearchInBlackList(const AdParamter& ad);
protected:
	//brief:启动广告监视器入口函数
	void SetupAdMonitor(HINSTANCE hInstance);
private:
	std::thread _adMonitor; //广告监视线程
	MonitorState _state;    //监视器运行状态
	std::mutex _stateMutex; //状态锁

	std::shared_ptr<std::vector<AdParamter>> _whiteList; //白名单
	std::shared_ptr<std::vector<AdParamter>> _blackList; //黑名单


	std::shared_ptr<std::map<AdParamter, AdDataStatistics>> _adIntercepted; //开启拦截的窗口统计
	std::shared_ptr<std::map<AdParamter, AdDataStatistics>> _adNoIntercepted; //未开启拦截的统计
	std::shared_ptr<std::vector<AdParamter>> _newAdList; //新发现的广告窗口列表
	//std::shared_ptr<std::map<AdParamter, bool>> _newAd;   //新发现的广告窗口 <数据, 是否开启拦截>
	ULONG_PTR _gdiplusToken; //启动和关闭DDI+库的令牌
};

