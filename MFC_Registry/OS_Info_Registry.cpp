#include "pch.h"

CString GetRegDataText(DWORD dwType, DWORD dwSize, TCHAR* buf, CString csEntry);
const int DMAX_SIZE = 256;

/******************************************************
GetWindows10Version
レジストリからRegQueryValueExを使用してバージョン情報を取得する



戻り値
 バージョン情報（タイプ/サイズ/値）
******************************************************/
CString GetWindows10Version()
{
    HKEY hKey = nullptr; //レジストリキーのハンドル
    LONG lRet;
    CString csRet = _T("");
    TCHAR buf[DMAX_SIZE];
    DWORD dwSize, dwType, dwVal = 0;

    //レジストリオープン
    lRet = RegOpenKeyEx(
        HKEY_LOCAL_MACHINE,
        _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion"),
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
    //// プロダクト(OS)を取得 //////////
    dwSize = DMAX_SIZE;
    ZeroMemory(&buf, DMAX_SIZE * 2);
    lRet = RegQueryValueEx(
        hKey,
        _T("ProductName"),
        0,
        &dwType,
        (LPBYTE)buf,
        &dwSize
    );
    //プロダクト 値取得エラー
    if (lRet != ERROR_SUCCESS)
    {
        csRet = _T("RegQueryValueEx(ProductName)エラー");
        goto lbl_Error;
    }
    csRet = _T("【Windows Version情報】\r\n");
    csRet += GetRegDataText(dwType, dwSize, buf, _T("ProductName"));



    //// リリースIDを取得 //////////
    dwSize = DMAX_SIZE;
    ZeroMemory(&buf, DMAX_SIZE * 2);
    lRet = RegQueryValueEx(
        hKey,
        _T("ReleaseId"),
        0,
        &dwType,
        (LPBYTE)buf,
        &dwSize
    );
    //リリースID 値取得エラー
    if (lRet != ERROR_SUCCESS)
    {
        csRet = _T("RegQueryValueEx(ReleaseId)エラー");
        goto lbl_Error;
    }
    csRet += GetRegDataText(dwType, dwSize, buf, _T("ReleaseId"));



    //// ビルドバージョンを取得 //////////
    dwSize = DMAX_SIZE;
    ZeroMemory(&buf, DMAX_SIZE * 2);
    lRet = RegQueryValueEx(
        hKey,
        _T("CurrentBuildNumber"),
        0,
        &dwType,
        (LPBYTE)buf,
        &dwSize
    );
    //ビルドバージョン 値取得エラー
    if (lRet != ERROR_SUCCESS)
    {
        csRet = _T("RegQueryValueEx(CurrentBuildNumber)エラー");
        goto lbl_Error;
    }
    csRet += GetRegDataText(dwType, dwSize, buf, _T("CurrentBuildNumber"));



    //// ビルドバージョン(UBR)を取得 //////////
    dwSize = DMAX_SIZE;
    ZeroMemory(&buf, DMAX_SIZE * 2);
    lRet = RegQueryValueEx(
        hKey,
        _T("UBR"),
        0,
        &dwType,
        (LPBYTE)buf,
        &dwSize
    );
    //ビルドバージョン(UBR) 値取得エラー
    if (lRet != ERROR_SUCCESS)
    {
        csRet = _T("RegQueryValueEx(UBR)エラー");
        goto lbl_Error;
    }
    csRet += GetRegDataText(dwType, dwSize, buf, _T("UBR"));

lbl_Error:
    if (hKey != NULL)
    {
        //レジストリクローズ
        RegCloseKey(hKey);
    }
    return csRet;
}

/******************************************************
GetRegDataText
取得したタイプ（データ型）/サイズ/値より表示用文字列を生成



引数
 dwType  : タイプ（データ型）
 dwSize  : データサイズ
 buf     : レジストリの値
 csEntry : レジストリのエントリ名
戻り値
 表示用文字列
******************************************************/
CString GetRegDataText(DWORD dwType, DWORD dwSize, TCHAR* buf, CString csEntry)
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