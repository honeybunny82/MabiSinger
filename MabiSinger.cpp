// MabiSinger.cpp : アプリケーション用クラスの定義を行います。
//

#include "stdafx.h"
#include "MabiSinger.h"
#include "MabiSingerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMabiSingerApp

BEGIN_MESSAGE_MAP(CMabiSingerApp, CWinApp)
	//{{AFX_MSG_MAP(CMabiSingerApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMabiSingerApp クラスの構築

CMabiSingerApp::CMabiSingerApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CMabiSingerApp オブジェクト

CMabiSingerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMabiSingerApp クラスの初期化

BOOL CMabiSingerApp::InitInstance()
{
	// 標準的な初期化処理

#ifdef _AFXDLL
	Enable3dControls();			// 共有 DLL 内で MFC を使う場合はここをコールしてください。
#else
	Enable3dControlsStatic();	// MFC と静的にリンクする場合はここをコールしてください。
#endif

	CMabiSingerDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// ダイアログが閉じられてからアプリケーションのメッセージ ポンプを開始するよりは、
	// アプリケーションを終了するために FALSE を返してください。
	return FALSE;
}
