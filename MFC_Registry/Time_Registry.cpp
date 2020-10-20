#include "pch.h"

CString GetRegTimeText(DWORD dwType, DWORD dwSize, TCHAR* buf, CString csEntry);
const int DMAX_SIZE = 256;

CString SetRegistrywrite()
{
	
	//�������擾
	CTime cTime1 = CTime::GetCurrentTime();
	//CTimeSpan cTimep(30 * 24 * 60 * 60);
	CTimeSpan cTimep(30);
	//����
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
	
	//���W�X�g���̃T�u�L�[���m�F
	lRet = RegOpenKeyEx(
		HKEY_LOCAL_MACHINE,
		_T("SOFTWARE\\inawashirotest\\akahara\\umai32"),
		0,
		//KEY_QUERY_VALUE | KEY_WOW64_64KEY, //64bit�d�l 20201020
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
		//�C���X�g�[���������W�X�g������擾(�����^)
		csRet = GetRegTimeText(dwType, dwSize, buf, _T("FTime1"));
		
		//����������
		csRet.Replace('p', '0');			// p �� 0		
		csRet.Replace('S', '1');			// S �� 1		
		csRet.Replace('J', '2');			// J �� 2		
		csRet.Replace('y', '3');			// y �� 3		
		csRet.Replace('t', '4');			// t �� 4		
		csRet.Replace('M', '5');			// M �� 5		
		csRet.Replace('d', '6');			// d �� 6		
		csRet.Replace('W', '7');			// W �� 7		
		csRet.Replace('Q', '8');			// Q �� 8		
		csRet.Replace('z', '9');			// z �� 9
		csRet.Replace('b', '/');			// b �� /

		//���������t
		oleTime.ParseDateTime(csRet);
		CTime oleTime1 = oleTime;

		//30����
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
			//�C���X�g�[������30��������W�X�g������擾(�����^)
			//csRet = GetRegTimeText(dwType, dwSize, buf, _T("FTime30"));
			
			//���������t
			//oleTime.ParseDateTime(csRet);
			//CTime oleTime30 = oleTime;

			if(oleTime1 <= cTime1){

				if (cTime1 <= cTime30) {

					csRet = _T("�N�����܂���");
					goto lbl_Error;

				}
				else {

					csRet = _T("���p���Ԃ��߂��܂����B");
					goto lbl_Error;
				}
			}
		//}
		//goto lbl_Error;a
	}


	/*
	
	//���W�X�g���̃t�H���_�[�̍쐬
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
		csRet = _T("�t�H���_���쐬�ł��܂���");
		goto lbl_Error;
	}

	//�C���X�g�[�����̓o�^
	//buf = strWriteValue.GetBuffer(strWriteValue.GetLength());	//CHAR�^�ɕϊ�
	//len = strWriteValue.GetLength() * 2 + 1;	//�T�C�Y�擾
	tmp = Time1.GetBuffer(Time1.GetLength());		//CHAR�^�ɕϊ�
	len = Time1.GetLength() * 2 + 1;				//�T�C�Y�擾


	lRet = RegSetValueEx(
		hKey,									// �L�[�n���h��
		L"TestTime0",							// ValueName
		0,										// Reserved(0�Œ�)
		REG_SZ,									// �f�[�^�^
		(LPBYTE)tmp,							// �C���X�g�[����������������
		len										// �������݃T�C�Y
		//(LPBYTE) strWriteValue.c_str(),		// �������ݓ��e default20200518
		//strWriteValue.size() * sizeof(TCHAR)	// �������݃T�C�Y(BYTE) default20200518
	);

	if (lRet != ERROR_SUCCESS) {
		csRet = _T("�C���X�g�[�������o�^�ł��܂���");
		goto lbl_Error;
	}

	//�C���X�g�[������30����̓o�^
	//buf = strWriteValue.GetBuffer(strWriteValue.GetLength());	//CHAR�^�ɕϊ�
	//len = strWriteValue.GetLength() * 2 + 1;	//�T�C�Y�擾
	tmp = Time30.GetBuffer(Time30.GetLength());		//CHAR�^�ɕϊ�
	len = Time30.GetLength() * 2 + 1;				//�T�C�Y�擾


	lRet = RegSetValueEx(
		hKey,									// �L�[�n���h��
		L"TestTime30",							// ValueName
		0,										// Reserved(0�Œ�)
		REG_SZ,									// �f�[�^�^
		(LPBYTE)tmp,							// �\�t�g�̋N������������������
		len										// �������݃T�C�Y
		//(LPBYTE) strWriteValue.c_str(),		// �������ݓ��e default20200518
		//strWriteValue.size() * sizeof(TCHAR)	// �������݃T�C�Y(BYTE) default20200518
	);
	
	*/

	if (lRet != ERROR_SUCCESS) {
		csRet = _T("�N���ł��܂���");
		goto lbl_Error;
	}

	RegCloseKey(hKey);

	return csRet;

lbl_Error:
	if (hKey != NULL)
	{
		//���W�X�g���N���[�Y
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