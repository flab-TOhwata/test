﻿
// MFC_RegistryDlg.h : ヘッダー ファイル
//

#pragma once


// CMFCRegistryDlg ダイアログ
class CMFCRegistryDlg : public CDialog
{
// コンストラクション
public:
	CMFCRegistryDlg(CWnd* pParent = nullptr);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_REGISTRY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRegistrySet();
	afx_msg void OnBnClickedRegistryFstrial();
	afx_msg void OnBnClickedRegistrywritetest();
};
