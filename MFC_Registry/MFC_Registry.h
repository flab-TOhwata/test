
// MFC_Registry.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CMFCRegistryApp:
// このクラスの実装については、MFC_Registry.cpp を参照してください
//

class CMFCRegistryApp : public CWinApp
{
public:
	CMFCRegistryApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CMFCRegistryApp theApp;
