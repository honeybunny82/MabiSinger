// MabiSinger.cpp : �A�v���P�[�V�����p�N���X�̒�`���s���܂��B
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
// CMabiSingerApp �N���X�̍\�z

CMabiSingerApp::CMabiSingerApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// �B��� CMabiSingerApp �I�u�W�F�N�g

CMabiSingerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMabiSingerApp �N���X�̏�����

BOOL CMabiSingerApp::InitInstance()
{
	// �W���I�ȏ���������

#ifdef _AFXDLL
	Enable3dControls();			// ���L DLL ���� MFC ���g���ꍇ�͂������R�[�����Ă��������B
#else
	Enable3dControlsStatic();	// MFC �ƐÓI�Ƀ����N����ꍇ�͂������R�[�����Ă��������B
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

	// �_�C�A���O�������Ă���A�v���P�[�V�����̃��b�Z�[�W �|���v���J�n������́A
	// �A�v���P�[�V�������I�����邽�߂� FALSE ��Ԃ��Ă��������B
	return FALSE;
}
