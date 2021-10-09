// MabiSingerDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "MabiSinger.h"
#include "MabiSingerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#define TARGET_CLASS_NAME	_T("Notepad")
#define TARGET_CLASS_NAME	_T("Mabinogi")
#define	FILE_LIST_MAX		20
#define	INI_SCT_FILELIST	_T("FileList")
#define	INI_SCT_SETTING		_T("Setting")
#define	INI_KEY_FNCKEY		_T("FncKey")
#define	INI_KEY_TOPMOST		_T("TopMost")
#define	INI_KEY_WINPOS		_T("WinPos")
#define	INI_KEY_SLEEP		_T("Sleep")
#define	INI_DEF_SLEEP		100

/////////////////////////////////////////////////////////////////////////////
// CMabiSingerDlg ダイアログ

CMabiSingerDlg::CMabiSingerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMabiSingerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMabiSingerDlg)
		// メモ: この位置に ClassWizard によってメンバの初期化が追加されます。
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_iSleep = 0;
}

void CMabiSingerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMabiSingerDlg)
	DDX_Control(pDX, IDC_CHK_TOPMOST, m_chkTopMost);
	DDX_Control(pDX, IDC_CMB_FNCKEY, m_cmbFncKey);
	DDX_Control(pDX, IDC_CMB_FILE, m_cmbFile);
	DDX_Control(pDX, IDC_LST_TEXT, m_lstText);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMabiSingerDlg, CDialog)
	//{{AFX_MSG_MAP(CMabiSingerDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SEND, OnBtnSend)
	ON_BN_CLICKED(IDC_BTN_OPEN, OnBtnOpen)
	ON_BN_CLICKED(IDC_BTN_CLEAR, OnBtnClear)
	ON_BN_CLICKED(IDC_CHK_TOPMOST, OnChkTopmost)
	ON_BN_CLICKED(IDC_BTN_UP, OnBtnUp)
	ON_BN_CLICKED(IDC_BTN_DOWN, OnBtnDown)
	ON_BN_CLICKED(IDC_BTN_ENTER, OnBtnEnter)
	ON_BN_CLICKED(IDC_BTN_PLAY, OnBtnPlay)
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop)
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_CMB_FILE, OnSelchangeCmbFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMabiPlayerDlg メンバ関数

BOOL CMabiSingerDlg::SetForeground()
{
	HWND hWnd = ::FindWindow( TARGET_CLASS_NAME, NULL );

	if( hWnd == NULL )
		return FALSE;

	::SetForegroundWindow( hWnd );

	// アクティブ移動後にウェイト
	Sleep( m_iSleep );

	return TRUE;
}

BOOL CMabiSingerDlg::SetClipboard( CString* pstrBuf )
{
	HGLOBAL	hMem;
	TCHAR*	pText;

	// クリップボード
	if( OpenClipboard() == FALSE )
		return FALSE;

	if( EmptyClipboard() == FALSE )
		goto ERROR_CLIP_CLOSE;

	// メモリ
	if( ( hMem = GlobalAlloc( GMEM_DDESHARE | GMEM_MOVEABLE, pstrBuf->GetLength() + 1 ) ) == NULL )
		goto ERROR_CLIP_CLOSE;

	if( ( pText = (TCHAR*)GlobalLock( hMem ) ) == NULL )
		goto ERROR_MEM_CLOSE;

	lstrcpy( pText, *pstrBuf );
	GlobalUnlock( hMem );

	SetClipboardData( CF_TEXT, hMem );
	CloseClipboard();

	return TRUE;

ERROR_MEM_CLOSE:
	GlobalFree( hMem );

ERROR_CLIP_CLOSE:
	CloseClipboard();

	return FALSE;
}

void CMabiSingerDlg::SendKeycode( WORD wVk, WORD wVkWith /*=0*/ )
{
	INPUT	sInput[4];
	int		iIdx = 0;

	if( wVkWith != 0 )
	{
		sInput[0].type			= INPUT_KEYBOARD;
		sInput[0].ki.wVk		= wVkWith;
		sInput[0].ki.wScan		= MapVirtualKey( wVkWith, 0 );
		sInput[0].ki.dwFlags	= 0;

		sInput[3].type			= INPUT_KEYBOARD;
		sInput[3].ki.wVk		= wVkWith;
		sInput[3].ki.wScan		= MapVirtualKey( wVkWith, 0 );
		sInput[3].ki.dwFlags	= KEYEVENTF_KEYUP;

		iIdx = 1;
	}

	sInput[iIdx].type			= INPUT_KEYBOARD;
	sInput[iIdx].ki.wVk			= wVk;
	sInput[iIdx].ki.wScan		= MapVirtualKey( wVk, 0 );
	sInput[iIdx].ki.dwFlags		= 0;

	sInput[iIdx + 1].type		= INPUT_KEYBOARD;
	sInput[iIdx + 1].ki.wVk		= wVk;
	sInput[iIdx + 1].ki.wScan	= MapVirtualKey( wVk, 0 );
	sInput[iIdx + 1].ki.dwFlags	= KEYEVENTF_KEYUP;

	SendInput( ( iIdx + 1 ) * 2, sInput, sizeof(INPUT) );
}

void CMabiSingerDlg::GetIniFilePath()
{
	// 設定ファイルのパスを作成
	TCHAR	szPath[_MAX_PATH];
	TCHAR	szDrive[_MAX_DRIVE];
	TCHAR	szDir[_MAX_DIR];
	TCHAR	szFile[_MAX_FNAME];

	GetModuleFileName( NULL, szPath, sizeof(szPath) );
	_splitpath( szPath, szDrive, szDir, szFile, NULL );

	m_strIniFile.Format( _T("%s%s%s.ini"), szDrive, szDir, szFile );
}

void CMabiSingerDlg::ReadIniFile()
{
	// ファイル名のリスト
	TCHAR	szPath[_MAX_PATH];
	CString	strBuf;

	m_strFilePath_v.clear();

	for( int i = 0; i < FILE_LIST_MAX; i++ )
	{
		strBuf.Format( _T("File%02d"), i );
		GetPrivateProfileString( INI_SCT_FILELIST, strBuf, _T(""), szPath, sizeof(szPath), m_strIniFile );

		strBuf = szPath;
		if( strBuf.IsEmpty() == FALSE )
			m_strFilePath_v.push_back( strBuf );
	}

	SetFileList();

	// ファンクションキー
	int iFncKey = GetPrivateProfileInt( INI_SCT_SETTING, INI_KEY_FNCKEY, 0, m_strIniFile );

	m_cmbFncKey.SetCurSel( iFncKey );

	// 最前面
	int iTopMost = GetPrivateProfileInt( INI_SCT_SETTING, INI_KEY_TOPMOST, 0, m_strIniFile );

	m_chkTopMost.SetCheck( iTopMost );
	OnChkTopmost();

	// ウィンドウ位置
	TCHAR	szPos[20];
	int		iPosX, iPosY;

	GetPrivateProfileString( INI_SCT_SETTING, INI_KEY_WINPOS, _T(""), szPos, sizeof(szPos), m_strIniFile );
	strBuf = szPos;

	if( strBuf.IsEmpty() == FALSE )
	{
		CRect oRect;

		sscanf( strBuf, _T("%d,%d"), &iPosX, &iPosY );

		GetWindowRect( &oRect );
		oRect.OffsetRect( iPosX - oRect.left, iPosY - oRect.top );
		MoveWindow( &oRect );
	}

	// スリープ
	m_iSleep = GetPrivateProfileInt( INI_SCT_SETTING, INI_KEY_SLEEP, INI_DEF_SLEEP, m_strIniFile );
}

void CMabiSingerDlg::WriteIniFile()
{
	// ファイル名のリスト
	CString	strBuf, strPath;
	int		iCnt = (int)m_strFilePath_v.size();

	for( int i = 0; i < FILE_LIST_MAX; i++ )
	{
		strBuf.Format( _T("File%02d"), i );

		if( i < iCnt )
			WritePrivateProfileString( INI_SCT_FILELIST, strBuf, m_strFilePath_v[i], m_strIniFile );
		else
			WritePrivateProfileString( INI_SCT_FILELIST, strBuf, _T(""), m_strIniFile );
	}

	// ファンクションキー
	strBuf.Format( _T("%d"), m_cmbFncKey.GetCurSel() );
	WritePrivateProfileString( INI_SCT_SETTING, INI_KEY_FNCKEY, strBuf, m_strIniFile );

	// 最前面
	strBuf.Format( _T("%d"), m_chkTopMost.GetCheck() );
	WritePrivateProfileString( INI_SCT_SETTING, INI_KEY_TOPMOST, strBuf, m_strIniFile );

	// ウィンドウ位置
	CRect oRect;

	GetWindowRect( &oRect );

	strBuf.Format( _T("%d,%d"), oRect.left, oRect.top );
	WritePrivateProfileString( INI_SCT_SETTING, INI_KEY_WINPOS, strBuf, m_strIniFile );

	// スリープ
	strBuf.Format( _T("%d"), m_iSleep );
	WritePrivateProfileString( INI_SCT_SETTING, INI_KEY_SLEEP, strBuf, m_strIniFile );
}

void CMabiSingerDlg::AddFileName( CString* pstrFile )
{
	// 既存のバッファを検索
	int iCnt = (int)m_strFilePath_v.size();
	for( int i = 0; i < iCnt; i++ )
	{
		if( m_strFilePath_v[i].CompareNoCase( *pstrFile ) == 0 )
		{
			// 先頭にある場合はそのまま終了
			if( i == 0 )
				return;

			// 一旦削除
			m_strFilePath_v.erase( m_strFilePath_v.begin() + i );
		}
	}

	// 20件を超える場合は最後を削除
	if( m_strFilePath_v.size() >= FILE_LIST_MAX )
		m_strFilePath_v.erase( m_strFilePath_v.end() - 1 );

	// 先頭に挿入
	m_strFilePath_v.insert( m_strFilePath_v.begin(), *pstrFile );


}

void CMabiSingerDlg::SetFileList()
{
	TCHAR	szDrive[_MAX_DRIVE];
	TCHAR	szDir[_MAX_DIR];
	TCHAR	szFile[_MAX_FNAME];
	TCHAR	szExt[_MAX_EXT];
	CString	strBuf;

	m_cmbFile.ResetContent();

	int iCnt = (int)m_strFilePath_v.size();

	for( int i = 0; i < iCnt; i++ )
	{
		_splitpath( m_strFilePath_v[i], szDrive, szDir, szFile, szExt );
		strBuf.Format( _T("%s%s (%s%s)"), szFile, szExt, szDrive, szDir );

		m_cmbFile.AddString( strBuf );
	}
}

BOOL CMabiSingerDlg::ReadTextFile( CString* pstrFile )
{
	// ファイルを読み込んでバッファに保存
	CStdioFile	oFile;
	CString		strBuf;

	if( oFile.Open( *pstrFile, CFile::modeRead | CFile::typeText ) == 0 )
	{
		MessageBox( _T("ファイルが読み込めませんでした。") );

		return FALSE;
	}

	m_strTextBuf_v.clear();

	while( oFile.ReadString( strBuf ) )
		m_strTextBuf_v.push_back( strBuf );

	// リストへ表示
	m_lstText.ResetContent();

	for( int i = 0; i < (int)m_strTextBuf_v.size(); i++ )
	{
		strBuf.Format( _T("%03d %s"), i + 1, m_strTextBuf_v[i] );
		m_lstText.AddString( strBuf );
	}

	m_lstText.SetCurSel( 0 );

	// ファイル履歴
	AddFileName( pstrFile );
	SetFileList();
	m_cmbFile.SetCurSel( 0 );

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CMabiSingerDlg メッセージ ハンドラ

BOOL CMabiSingerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定
	
	// ファンクションキーのリストを作成
	CString strBuf;

	for( int i = 1; i <= 12; i++ )
	{
		strBuf.Format( _T("F%d"), i );
		m_cmbFncKey.AddString( strBuf );
	}

	// 設定ファイルを読み込み
	GetIniFilePath();
	ReadIniFile();

	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

void CMabiSingerDlg::OnClose() 
{
	// 終了前に設定ファイルを保存
	WriteIniFile();

	CDialog::OnClose();
}

void CMabiSingerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画用のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// クライアントの矩形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンを描画します。
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CMabiSingerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// 開く
void CMabiSingerDlg::OnBtnOpen() 
{
	// ファイル選択ダイアログを表示
	CString		strPath;
	CFileDialog	oDlg( TRUE, _T("txt"), NULL, OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, 
					  _T("テキストファイル (*.txt)|*.txt|すべてのファイル (*.*)|*.*||") );

	if( oDlg.DoModal() != IDOK )
		return;

	strPath = oDlg.GetPathName();

	if( ReadTextFile( &strPath ) == FALSE )
	{
		m_cmbFile.SetCurSel( -1 );
		m_lstText.ResetContent();
	}
}

// ファイルコンボ変更
void CMabiSingerDlg::OnSelchangeCmbFile() 
{
	int iSel = m_cmbFile.GetCurSel();

	if( iSel < 0 || iSel >= (int)m_strFilePath_v.size() )
		return;

	CString strPath = m_strFilePath_v[iSel];

	if( ReadTextFile( &strPath ) == FALSE )
	{
		// リストから削除
		m_strFilePath_v.erase( m_strFilePath_v.begin() + iSel );
		SetFileList();

		m_cmbFile.SetCurSel( -1 );
		m_lstText.ResetContent();
	}
}

// 送信
void CMabiSingerDlg::OnBtnSend()
{
	// 選択されたテキストを取得
	CString	strText;
	int		iSel = m_lstText.GetCurSel();

	if( iSel == -1 )
	{
		if( m_lstText.GetCount() == 0 )
			return;

		iSel = 0;
	}

	strText = m_strTextBuf_v[iSel];

	// クリップボードに保存
	if( SetClipboard( &strText ) == FALSE )
		return;

	// ウィンドウアクティブ
	if( SetForeground() == FALSE )
		return;

	// キー送信
	SendKeycode( 'V', VK_CONTROL );
	SendKeycode( VK_RETURN );

	// アクティブ復帰
//	::SetForegroundWindow( m_hWnd );

	// 次の行を選択
	++iSel;

	if( iSel >= m_lstText.GetCount() )
	{
		m_lstText.SetCurSel( 0 );

		MessageBox( _T("最後まで送信しました。") );
	}
	else
		m_lstText.SetCurSel( iSel );
}

// 上へ
void CMabiSingerDlg::OnBtnUp() 
{
	int iSel = m_lstText.GetCurSel();

	if( iSel - 1 < 0 )
		return;

	m_lstText.SetCurSel( iSel - 1 );
}

// 下へ
void CMabiSingerDlg::OnBtnDown() 
{
	int iSel = m_lstText.GetCurSel();

	if( iSel + 1 >= m_lstText.GetCount() )
		return;

	m_lstText.SetCurSel( iSel + 1 );
}

// 改行
void CMabiSingerDlg::OnBtnEnter() 
{
	// ウィンドウアクティブ
	if( SetForeground() == FALSE )
		return;

	// キー送信
	SendKeycode( VK_RETURN );

	// アクティブ復帰
//	::SetForegroundWindow( m_hWnd );
}

// 行クリア
void CMabiSingerDlg::OnBtnClear() 
{
	// ウィンドウアクティブ
	if( SetForeground() == FALSE )
		return;

	// キー送信
//	SendKeycode( 'A', VK_CONTROL );		// チャットが開いていないと自動戦闘切り替えになる
	SendKeycode( VK_END );
	SendKeycode( VK_HOME, VK_SHIFT );
	SendKeycode( VK_BACK );

	// アクティブ復帰
//	::SetForegroundWindow( m_hWnd );
}

// 演奏
void CMabiSingerDlg::OnBtnPlay() 
{
	int iSel = m_cmbFncKey.GetCurSel();

	// ウィンドウアクティブ
	if( SetForeground() == FALSE )
		return;

	// キー送信
	SendKeycode( VK_F1 + iSel );

	// アクティブ復帰
//	::SetForegroundWindow( m_hWnd );
}

// 停止
void CMabiSingerDlg::OnBtnStop() 
{
	// ウィンドウアクティブ
	if( SetForeground() == FALSE )
		return;

	// キー送信
	SendKeycode( VK_ESCAPE );

	// アクティブ復帰
//	::SetForegroundWindow( m_hWnd );
}

// 常に最前面
void CMabiSingerDlg::OnChkTopmost() 
{
	if( m_chkTopMost.GetCheck() == 1 )
		SetWindowPos( &wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
	else
		SetWindowPos( &wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
}
