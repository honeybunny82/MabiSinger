// MabiSinger.h : MABISINGER �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_MABISINGER_H__D8C58328_AAF3_469A_A957_3C46A5536878__INCLUDED_)
#define AFX_MABISINGER_H__D8C58328_AAF3_469A_A957_3C46A5536878__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CMabiSingerApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� MabiSinger.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CMabiSingerApp : public CWinApp
{
public:
	CMabiSingerApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CMabiSingerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����

	//{{AFX_MSG(CMabiSingerApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_MABISINGER_H__D8C58328_AAF3_469A_A957_3C46A5536878__INCLUDED_)
