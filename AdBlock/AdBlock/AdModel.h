#pragma once

#include "EnumAdWindowsTool.h"
#include "ShellHook.h"
#include <thread>
#include <mutex>
#include <vector>
#include <map>
//���������


//������������״̬
enum MonitorState
{
	START = 0,     //����
	RUNNING = 1,   //����
	SUSPEND = 2,   //����
	STOP = 3       //ֹͣ
};

//
struct AdParamter
{
	WndParamter _wnd; //������Ϣ
	ProcessInfo _processInfo; //���ڽ�����Ϣ

	std::wstring _iconImagePath; //ͼ��ͼƬ·��
	std::wstring _firstCaptureImagePath; //�״ν�ͼͼƬ
};

//���ͳ��
struct AdDataStatistics
{
	AdParamter _ad;
	bool _remoteAd; //�豸�ɲ������
	UINT64 _historyInterceptCount; //��ʷ���ش������ƶ�ͬ������)
	UINT64 _localHistoryInterceptCount; //�豸��ʷ���ش�����������δ����ѧУ�����شӴ���ֻ�ڱ�����ʾ??)

};

class AdModel
{
public:
	AdModel();
	virtual ~AdModel();
public:
	//brief:�������������
	void Start();
	void SetAdMonitorState(const MonitorState& state);
private:
	//brief:���غڰ�����
	void LoadBlackAndWhiteList();
	//brief:����ڼ������������Ĺ�洰��
	void ClearAdWindows();
	//brief:�жϴ����Ƿ���Ҫ���غ�������
	void HandleWindows(const WndParamter& wp);
	//brief:��⵽���´��ڲ�����ʱ��ص�
	void GetCreateWindowsParamter(const WndParamter& wp);
	//brief:ö�����涥�����ڻص�����
	void EnumTopLevelWindows(const WndParamter& wp);
	//brief:�Ƿ��ڰ�����
	bool SearchInWhiteList(const AdParamter& ad);
	//brief:�Ƿ��ں�������
	bool SearchInBlackList(const AdParamter& ad);
protected:
	//brief:��������������ں���
	void SetupAdMonitor(HINSTANCE hInstance);
private:
	std::thread _adMonitor; //�������߳�
	MonitorState _state;    //����������״̬
	std::mutex _stateMutex; //״̬��

	std::shared_ptr<std::vector<AdParamter>> _whiteList; //������
	std::shared_ptr<std::vector<AdParamter>> _blackList; //������


	std::shared_ptr<std::map<AdParamter, AdDataStatistics>> _adIntercepted; //�������صĴ���ͳ��
	std::shared_ptr<std::map<AdParamter, AdDataStatistics>> _adNoIntercepted; //δ�������ص�ͳ��
	std::shared_ptr<std::vector<AdParamter>> _newAdList; //�·��ֵĹ�洰���б�
	//std::shared_ptr<std::map<AdParamter, bool>> _newAd;   //�·��ֵĹ�洰�� <����, �Ƿ�������>
	ULONG_PTR _gdiplusToken; //�����͹ر�DDI+�������
};

