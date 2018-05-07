
// ReadSHDFileDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ReadSHDFile.h"
#include "ReadSHDFileDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//========================SHD�ļ��ṹ=============================
//Windows98
typedef struct _SHADOW_FILE_HEADER_WIN98 {
  DWORD dwSignature;        //SHD_SIGNATURE_WIN98
  WORD wStatus;
  WORD wUnknown1;
  DWORD dwJobID;
  DWORD dwPriority;
  DWORD offUserName;        //Offset of WideChar+0
  DWORD offNotifyName;      //Offset of WideChar+0
  DWORD offDocumentName;    //Offset of WideChar+0
  DWORD offPort;            //Offset of WideChar+0
  DWORD offPrinterName;     //Offset of WideChar+0
  DWORD offDriverName;      //Offset of WideChar+0
  DWORD offDevMode;         //Offset of DEVMODE
        //Note that the dmCopies in this structure will hold
        //the wrong value when the Microsoft Word multiple
        //copies bug occurs.
        //In this case use the dmCopies from the SPL file
  DWORD offPrintProcessor;  //Offset of WideChar+0
  DWORD offDataFormat;      //Offset of WideChar+0
  DWORD dwUnknown2;
  SYSTEMTIME stSubmitTime;
  DWORD dwStartTime;
  DWORD dwUntilTime;
  DWORD dwSizeSPL;          //Size of SPL File
  DWORD dwPageCount;
  DWORD dwSizeSecurityInfo; //Size of SecurityInfo
  DWORD offSecurityInfo;    //Offset of SECURITY_DESCRIPTOR
  DWORD dwUnknown3;
} SHADOW_FILE_HEADER_WIN98, *PSHADOW_FILE_HEADER_WIN98;
//WindowsNT
typedef struct _SHADOW_FILE_HEADER_WINNT {
  DWORD dwSignature;        //SHD_SIGNATURE_WINNT
  WORD wStatus;
  WORD wUnknown1;
  DWORD dwJobID;
  DWORD dwPriority;
  DWORD offUserName;        //Offset of WideChar+0
  DWORD offNotifyName;      //Offset of WideChar+0
  DWORD offDocumentName;    //Offset of WideChar+0
  DWORD offPort;            //Offset of WideChar+0
  DWORD offPrinterName;     //Offset of WideChar+0
  DWORD offDriverName;      //Offset of WideChar+0
  DWORD offDevMode;         //Offset of DEVMODE
        //Note that the dmCopies in this structure will hold
        //the wrong value when the Microsoft Word multiple
        //copies bug occurs.
        //In this case use the dmCopies from the SPL file
  DWORD offPrintProcessor;  //Offset of WideChar+0
  DWORD offDataFormat;      //Offset of WideChar+0
  DWORD dwUnknown2;
  SYSTEMTIME stSubmitTime;
  DWORD dwStartTime;
  DWORD dwUntilTime;
  DWORD dwSizeSPL;          //Size of SPL File
  DWORD dwPageCount;
  DWORD dwSizeSecurityInfo; //Size of SecurityInfo
  DWORD offSecurityInfo;    //Offset of SECURITY_DESCRIPTOR
  DWORD dwUnknown3;
  DWORD dwUnknown4;
  DWORD dwUnknown5;
} SHADOW_FILE_HEADER_WINNT, *PSHADOW_FILE_HEADER_WINNT;

//Windows2000/XP
typedef struct _SHADOW_FILE_HEADER_WIN2000 {
  DWORD dwSignature;        //SHD_SIGNATURE_WIN2000
  DWORD dwHeaderSize;
  WORD wStatus;
  WORD wUnknown1;
  DWORD dwJobID;
  DWORD dwPriority;
  DWORD offUserName;        //Offset of WideChar+0
  DWORD offNotifyName;      //Offset of WideChar+0
  DWORD offDocumentName;    //Offset of WideChar+0
  DWORD offPort;            //Offset of WideChar+0
  DWORD offPrinterName;     //Offset of WideChar+0
  DWORD offDriverName;      //Offset of WideChar+0
  DWORD offDevMode;         //Offset of DEVMODE
        //Note that the dmCopies in this structure will hold
        //the wrong value when the Microsoft Word multiple
        //copies bug occurs.
        //In this case use the dmCopies from the SPL file
  DWORD offPrintProcessor;  //Offset of WideChar+0
  DWORD offDataFormat;      //Offset of WideChar+0
  DWORD dwUnknown2;
  SYSTEMTIME stSubmitTime;
  DWORD dwStartTime;
  DWORD dwUntilTime;
  DWORD dwSizeSPL;          //Size of SPL File
  DWORD dwPageCount;
  DWORD dwSizeSecurityInfo; //Size of SecurityInfo
  DWORD offSecurityInfo;    //Offset of SECURITY_DESCRIPTOR
  DWORD dwUnknown3;
  DWORD dwUnknown4;
  DWORD dwUnknown5;
  DWORD offComputername;    //Offset of WideChar+0
  DWORD dwSPLSize2;
} SHADOW_FILE_HEADER_WIN2000, *PSHADOW_FILE_HEADER_WIN2000;




// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CReadSHDFileDlg �Ի���




CReadSHDFileDlg::CReadSHDFileDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CReadSHDFileDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReadSHDFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CReadSHDFileDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CReadSHDFileDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CReadSHDFileDlg ��Ϣ�������

BOOL CReadSHDFileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CReadSHDFileDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CReadSHDFileDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CReadSHDFileDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CReadSHDFileDlg::OnBnClickedOk()
{
	TCHAR pszSHDFilePath[1024] = {0x00};
	TCHAR szPageNum[1024] = {0x00};
	_SHADOW_FILE_HEADER_WIN2000 sfhw2000;
	
	int n = 12;
	sprintf_s(pszSHDFilePath, 1024, "D:\\360data\\��Ҫ����\\����\\000%d.SHD", n);
	
	if(NULL == pszSHDFilePath)
	{
		return ;
	}

	FILE* pf = NULL;
	pf = fopen(pszSHDFilePath, "rb");

	if(NULL == pf)
	{
		::MessageBox(NULL, TEXT("Open SHD File Error!"), TEXT("Error!"), MB_OK | MB_ICONWARNING);
		return ;
	}

	int size = fread(&sfhw2000, sizeof(_SHADOW_FILE_HEADER_WIN2000), 1, pf);
	if(size != 1)
	{
		::MessageBox(NULL, TEXT("Read SHD File Error!"), TEXT("Error!"), MB_OK | MB_ICONWARNING);
		return ;
	}

	sprintf_s(szPageNum, 1024, "%d", sfhw2000.dwPageCount);
	MessageBox(szPageNum, szPageNum, MB_OK);

	//CDialogEx::OnOK();
}
