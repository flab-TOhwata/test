#include "pch.h"

CString GetRegFStrialText(DWORD dwType, DWORD dwSize, TCHAR* buf, CString csEntry);
const int DMAX_SIZE = 256;

/******************************************************
GetWindows10Version
���W�X�g������RegQueryValueEx���g�p���ăo�[�W���������擾����



�߂�l
 �o�[�W�������i�^�C�v/�T�C�Y/�l�j
******************************************************/

CString GetFStrialInformation()
{
	HKEY hKey = nullptr; //���W�X�g���L�[�̃n���h��
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
	//���W�X�g���I�[�v���G���[
	if (lRet != ERROR_SUCCESS)
	{
		csRet = _T("RegOpenKeyEx�G���[");
		goto lbl_Error;
	}
	//RegQueryValueEx�ɂ��Ă�DeveloperNetwork�Q��
	//// fish�̒l���擾 //////////
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
	//fish �l�擾�G���[
	if (lRet != ERROR_SUCCESS)
	{
		csRet = _T("fish�G���[");
		goto lbl_Error;
	}
	csRet = _T("�yF-Search trial�̏��z\r\n");
	csRet += GetRegFStrialText(dwType, dwSize, buf, _T("fish"));

lbl_Error:
	if (hKey != NULL)
	{
		//���W�X�g���N���[�Y
		RegCloseKey(hKey);
	}
	return csRet;
}

CString GetRegFStrialText(DWORD dwType, DWORD dwSize, TCHAR* buf, CString csEntry)
{
	CString csRet = _T("\r\n=== ") + csEntry + _T(" ==========\r\n");
	CString cwk;
	int iwk;

	//�ǂ݂������^�C�v�ɉ����ăT�C�Y�ƒl��ݒ�
	//�����ł͕K�v�ȃ^�C�v�̂ݐݒ肷�邪�^�C�v�̏ڍׂ�DeveloperNetwork�Q��
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