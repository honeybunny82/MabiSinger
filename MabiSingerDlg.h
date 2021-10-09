// MabiSingerDlg.h : ヘッダー ファイル
//

#if !defined(AFX_MABISINGERDLG_H__C4BD6DB5_644A_43AA_97C2_14D0B7ABA0DC__INCLUDED_)
#define AFX_MABISINGERDLG_H__C4BD6DB5_644A_43AA_97C2_14D0B7ABA0DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMabiSingerDlg ダイアログ

class CMabiSingerDlg : public CDialog
{
// 構築
public:
	CMabiSingerDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CMabiSingerDlg)
	enum { IDD = IDD_MABISINGER_DIALOG };
	CButton		m_chkTopMost;
	CComboBox	m_cmbFncKey;
	CComboBox	m_cmbFile;
	CListBox	m_lstText;
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CMabiSingerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	HICON m_hIcon;

	CString	m_strIniFile;
	int		m_iSleep;

	std::vector<CString>	m_strFilePath_v;
	std::vector<CString>	m_strTextBuf_v;

	BOOL	SetForeground();
	BOOL	SetClipboard( CString* );
	void	SendKeycode( WORD, WORD = 0 );

	void	GetIniFilePath();
	void	ReadIniFile();
	void	WriteIniFile();
	void	AddFileName( CString* );
	void	SetFileList();

	BOOL	ReadTextFile( CString* );


	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CMabiSingerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnSend();
	afx_msg void OnBtnOpen();
	afx_msg void OnBtnClear();
	afx_msg void OnChkTopmost();
	afx_msg void OnBtnUp();
	afx_msg void OnBtnDown();
	afx_msg void OnBtnEnter();
	afx_msg void OnBtnPlay();
	afx_msg void OnBtnStop();
	afx_msg void OnClose();
	afx_msg void OnSelchangeCmbFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_MABISINGERDLG_H__C4BD6DB5_644A_43AA_97C2_14D0B7ABA0DC__INCLUDED_)
