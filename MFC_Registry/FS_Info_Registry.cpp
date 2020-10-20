#include "pch.h"

CString GetRegFStrialText(DWORD dwType, DWORD dwSize, TCHAR* buf, CString csEntry);
const int DMAX_SIZE = 256;

/******************************************************
GetWindows10Version
レジストリからRegQueryValueExを使用してバージョン情報を取得する



戻り値
 バージョン情報（タイプ/サイズ/値）
******************************************************/

CString GetFStrialInformation()
{
	HKEY hKey = nullptr; //レジストリキーのハンドル
	LONG lRet;
	CString csRet = _T("");
	TCHAR buf[DMAX_SIZE];
	DWORD dwSize, dwType, dwVal = 0;

	lRet = RegOpenKeyEx(
		HKEY_LOCAL_MACHINE,
		_T("SOFTWARE\\inawashiro\\akahara\\umai32"),
		0,
		KEY_QUERY_VALUE | KEY_WOW64_64KEY,
		&hKey
	);
	//レジストリオープンエラー
	if (lRet != ERROR_SUCCESS)
	{
		csRet = _T("RegOpenKeyExエラー");
		goto lbl_Error;
	}
	//RegQueryValueExについてはDeveloperNetwork参照
	//// fishの値を取得 //////////
	dwSize = DMAX_SIZE;
	ZeroMemory(&buf, DMAX_SIZE * 2);
	lRet = RegQueryValueEx(
		hKey,
		_T("fish"),
		0,
		&dwType,
		(LPBYTE)buf,
		&dwSize
	);
	//fish 値取得エラー
	if (lRet != ERROR_SUCCESS)
	{
		csRet = _T("fishエラー");
		goto lbl_Error;
	}
	csRet = _T("【F-Search trialの情報】\r\n");
	csRet += GetRegFStrialText(dwType, dwSize, buf, _T("fish"));

lbl_Error:
	if (hKey != NULL)
	{
		//レジストリクローズ
		RegCloseKey(hKey);
	}
	return csRet;
}

CString GetRegFStrialText(DWORD dwType, DWORD dwSize, TCHAR* buf, CString csEntry)
{
	CString csRet = _T("\r\n=== ") + csEntry + _T(" ==========\r\n");
	CString cwk;
	int iwk;

	//読みだしたタイプに応じてサイズと値を設定
	//ここでは必要なタイプのみ設定するがタイプの詳細はDeveloperNetwork参照
	switch (dwType)
	{
	case REG_DWORD:
		iwk = (int)buf[0];
		cwk.Format(_T("   VALUE: %d\r\n   SIZE: %d  TYPE: REG_DWORD\r\n"), iwk, dwSize);
		break;
	case REG_SZ:
		cwk.Format(_T("   VALUE: %s\r\n   SIZE: %d  TYPE: REG_SZ\r\n"), buf, dwSize);
		break;
	}

	csRet += cwk;
	return csRet;
}