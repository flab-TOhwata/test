#include "pch.h"

CString GetRegDataText(DWORD dwType, DWORD dwSize, TCHAR* buf, CString csEntry);
const int DMAX_SIZE = 256;

/******************************************************
GetWindows10Version
���W�X�g������RegQueryValueEx���g�p���ăo�[�W���������擾����



�߂�l
 �o�[�W�������i�^�C�v/�T�C�Y/�l�j
******************************************************/
CString GetWindows10Version()
{
    HKEY hKey = nullptr; //���W�X�g���L�[�̃n���h��
    LONG lRet;
    CString csRet = _T("");
    TCHAR buf[DMAX_SIZE];
    DWORD dwSize, dwType, dwVal = 0;

    //���W�X�g���I�[�v��
    lRet = RegOpenKeyEx(
        HKEY_LOCAL_MACHINE,
        _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion"),
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
    //// �v���_�N�g(OS)���擾 //////////
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
    //�v���_�N�g �l�擾�G���[
    if (lRet != ERROR_SUCCESS)
    {
        csRet = _T("RegQueryValueEx(ProductName)�G���[");
        goto lbl_Error;
    }
    csRet = _T("�yWindows Version���z\r\n");
    csRet += GetRegDataText(dwType, dwSize, buf, _T("ProductName"));



    //// �����[�XID���擾 //////////
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
    //�����[�XID �l�擾�G���[
    if (lRet != ERROR_SUCCESS)
    {
        csRet = _T("RegQueryValueEx(ReleaseId)�G���[");
        goto lbl_Error;
    }
    csRet += GetRegDataText(dwType, dwSize, buf, _T("ReleaseId"));



    //// �r���h�o�[�W�������擾 //////////
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
    //�r���h�o�[�W���� �l�擾�G���[
    if (lRet != ERROR_SUCCESS)
    {
        csRet = _T("RegQueryValueEx(CurrentBuildNumber)�G���[");
        goto lbl_Error;
    }
    csRet += GetRegDataText(dwType, dwSize, buf, _T("CurrentBuildNumber"));



    //// �r���h�o�[�W����(UBR)���擾 //////////
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
    //�r���h�o�[�W����(UBR) �l�擾�G���[
    if (lRet != ERROR_SUCCESS)
    {
        csRet = _T("RegQueryValueEx(UBR)�G���[");
        goto lbl_Error;
    }
    csRet += GetRegDataText(dwType, dwSize, buf, _T("UBR"));

lbl_Error:
    if (hKey != NULL)
    {
        //���W�X�g���N���[�Y
        RegCloseKey(hKey);
    }
    return csRet;
}

/******************************************************
GetRegDataText
�擾�����^�C�v�i�f�[�^�^�j/�T�C�Y/�l���\���p������𐶐�



����
 dwType  : �^�C�v�i�f�[�^�^�j
 dwSize  : �f�[�^�T�C�Y
 buf     : ���W�X�g���̒l
 csEntry : ���W�X�g���̃G���g����
�߂�l
 �\���p������
******************************************************/
CString GetRegDataText(DWORD dwType, DWORD dwSize, TCHAR* buf, CString csEntry)
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