
// TestDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

#include <string>
using namespace std;

struct WndInfo
{
	wstring _className;
	wstring _titleName;
	RECT _rect;
};

// CTestDlg �Ի���
class CTestDlg : public CDialogEx
{
// ����
public:
	CTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSetHook();
	afx_msg void OnBnClickedUnhook();

public:
	void CallWndProcFun(LPCREATESTRUCT lpcw);
private:
};
