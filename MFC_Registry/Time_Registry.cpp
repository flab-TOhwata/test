#include "pch.h"

CString GetRegTimeText(DWORD dwType, DWORD dwSize, TCHAR* buf, CString csEntry);
const int DMAX_SIZE = 256;

CString SetRegistrywrite()
{
	
	//日時を取得
	CTime cTime1 = CTime::GetCurrentTime();
	//CTimeSpan cTimep(30 * 24 * 60 * 60);
	CTimeSpan cTimep(30);
	//現在
	CString Time1 = cTime1.Format("%Y/%m/%d");
	COleDateTime oleTime;
	oleTime.ParseDateTime(Time1);
	cTime1 = oleTime;
	//CString time = cTime.Format("%Y/%m/%d %H:%M:%S");	

	HKEY hKey;
	LONG lRet;
	DWORD dwDisposition;
	CString csRet = _T("");
	_TCHAR* tmp;
	TCHAR buf[DMAX_SIZE];
	INT     len;

	DWORD dwSize, dwType, dwVal = 0;
	
	//レジストリのサブキーを確認
	lRet = RegOpenKeyEx(
		HKEY_LOCAL_MACHINE,
		_T("SOFTWARE\\inawashirotest\\akahara\\umai32"),
		0,
		//KEY_QUERY_VALUE | KEY_WOW64_64KEY, //64bit仕様 20201020
		KEY_QUERY_VALUE,
		&hKey
	);

	dwSize = DMAX_SIZE;
	ZeroMemory(&buf, DMAX_SIZE * 2);
	lRet = RegQueryValueEx(
		hKey,
		_T("FTime1"),
		0,
		&dwType,
		(LPBYTE)buf,
		&dwSize
	);
		
	if (lRet == ERROR_SUCCESS)
	{
		//インストール日をレジストリから取得(文字型)
		csRet = GetRegTimeText(dwType, dwSize, buf, _T("FTime1"));
		
		//文字→数字
		csRet.Replace('p', '0');			// p → 0		
		csRet.Replace('S', '1');			// S → 1		
		csRet.Replace('J', '2');			// J → 2		
		csRet.Replace('y', '3');			// y → 3		
		csRet.Replace('t', '4');			// t → 4		
		csRet.Replace('M', '5');			// M → 5		
		csRet.Replace('d', '6');			// d → 6		
		csRet.Replace('W', '7');			// W → 7		
		csRet.Replace('Q', '8');			// Q → 8		
		csRet.Replace('z', '9');			// z → 9
		csRet.Replace('b', '/');			// b → /

		//文字→日付
		oleTime.ParseDateTime(csRet);
		CTime oleTime1 = oleTime;

		//30日後
		CTime cTime30 = oleTime1 + cTimep;
		CString oleTime30 = cTime30.Format("%Y/%m/%d");
		
		/*
		
		dwSize = DMAX_SIZE;
		ZeroMemory(&buf, DMAX_SIZE * 2);
		lRet = RegQueryValueEx(
			hKey,
			_T("FTime30"),
			0,
			&dwType,
			(LPBYTE)buf,
			&dwSize
		);

		if (lRet == ERROR_SUCCESS)
		{
		*/
			//インストールから30日後をレジストリから取得(文字型)
			//csRet = GetRegTimeText(dwType, dwSize, buf, _T("FTime30"));
			
			//文字→日付
			//oleTime.ParseDateTime(csRet);
			//CTime oleTime30 = oleTime;

			if(oleTime1 <= cTime1){

				if (cTime1 <= cTime30) {

					csRet = _T("起動しました");
					goto lbl_Error;

				}
				else {

					csRet = _T("試用期間が過ぎました。");
					goto lbl_Error;
				}
			}
		//}
		//goto lbl_Error;a
	}


	/*
	
	//レジストリのフォルダーの作成
	lRet = RegCreateKeyEx(
		HKEY_LOCAL_MACHINE,
		//HKEY_CURRENT_USER,	//default20200518
		TEXT("SOFTWARE\\inawashiro\\akahara\\umai32"),
		//TEXT("test"),			//default20200518
		0,
		NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_CREATE_SUB_KEY | KEY_SET_VALUE | KEY_WOW64_64KEY,
		NULL,
		&hKey,
		&dwDisposition
	);

	if (lRet != ERROR_SUCCESS) {
		csRet = _T("フォルダが作成できません");
		goto lbl_Error;
	}

	//インストール日の登録
	//buf = strWriteValue.GetBuffer(strWriteValue.GetLength());	//CHAR型に変換
	//len = strWriteValue.GetLength() * 2 + 1;	//サイズ取得
	tmp = Time1.GetBuffer(Time1.GetLength());		//CHAR型に変換
	len = Time1.GetLength() * 2 + 1;				//サイズ取得


	lRet = RegSetValueEx(
		hKey,									// キーハンドル
		L"TestTime0",							// ValueName
		0,										// Reserved(0固定)
		REG_SZ,									// データ型
		(LPBYTE)tmp,							// インストール日時を書き込む
		len										// 書き込みサイズ
		//(LPBYTE) strWriteValue.c_str(),		// 書き込み内容 default20200518
		//strWriteValue.size() * sizeof(TCHAR)	// 書き込みサイズ(BYTE) default20200518
	);

	if (lRet != ERROR_SUCCESS) {
		csRet = _T("インストール日が登録できません");
		goto lbl_Error;
	}

	//インストールから30日後の登録
	//buf = strWriteValue.GetBuffer(strWriteValue.GetLength());	//CHAR型に変換
	//len = strWriteValue.GetLength() * 2 + 1;	//サイズ取得
	tmp = Time30.GetBuffer(Time30.GetLength());		//CHAR型に変換
	len = Time30.GetLength() * 2 + 1;				//サイズ取得


	lRet = RegSetValueEx(
		hKey,									// キーハンドル
		L"TestTime30",							// ValueName
		0,										// Reserved(0固定)
		REG_SZ,									// データ型
		(LPBYTE)tmp,							// ソフトの起動期限日を書き込む
		len										// 書き込みサイズ
		//(LPBYTE) strWriteValue.c_str(),		// 書き込み内容 default20200518
		//strWriteValue.size() * sizeof(TCHAR)	// 書き込みサイズ(BYTE) default20200518
	);
	
	*/

	if (lRet != ERROR_SUCCESS) {
		csRet = _T("起動できません");
		goto lbl_Error;
	}

	RegCloseKey(hKey);

	return csRet;

lbl_Error:
	if (hKey != NULL)
	{
		//レジストリクローズ
		RegCloseKey(hKey);
	}
	return csRet;
}

CString GetRegTimeText(DWORD dwType, DWORD dwSize, TCHAR* buf, CString csEntry)
{
	CString csRet;

	csRet.Format(_T("%s"), buf);
	
	return csRet;
}