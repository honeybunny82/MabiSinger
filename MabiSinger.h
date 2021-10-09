// MabiSinger.h : MABISINGER アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_MABISINGER_H__D8C58328_AAF3_469A_A957_3C46A5536878__INCLUDED_)
#define AFX_MABISINGER_H__D8C58328_AAF3_469A_A957_3C46A5536878__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CMabiSingerApp:
// このクラスの動作の定義に関しては MabiSinger.cpp ファイルを参照してください。
//

class CMabiSingerApp : public CWinApp
{
public:
	CMabiSingerApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CMabiSingerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CMabiSingerApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_MABISINGER_H__D8C58328_AAF3_469A_A957_3C46A5536878__INCLUDED_)
