
// EditCtrlView.cpp: CEditCtrlView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include <vector>

// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "EditCtrl.h"
#endif

#include "EditCtrlDoc.h"
#include "EditCtrlView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEditCtrlView

IMPLEMENT_DYNCREATE(CEditCtrlView, CFormView)

BEGIN_MESSAGE_MAP(CEditCtrlView, CFormView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
	//ON_EN_CHANGE(IDC_EDIT1, &CEditCtrlView::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_MYEDIT, &CEditCtrlView::OnEnChangeMyedit)
	ON_EN_MAXTEXT(IDC_MYEDIT, &CEditCtrlView::OnEnMaxtextMyedit)
	ON_STN_CLICKED(IDC_MYSTATIC, &CEditCtrlView::OnStnClickedMystatic)
END_MESSAGE_MAP()

// CEditCtrlView 생성/소멸

CEditCtrlView::CEditCtrlView() noexcept
	: CFormView(IDD_EDITCTRL_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CEditCtrlView::~CEditCtrlView()
{
}

void CEditCtrlView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MYEDIT, m_edit);
	DDX_Control(pDX, IDC_MYSTATIC, m_static);
}

BOOL CEditCtrlView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CEditCtrlView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	m_edit.SetLimitText(100000); // 텍스트 길이 제한을 적절하게 설정

	// Modify the style of the Edit Control to Multi-line
	m_edit.ModifyStyle(0, ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | WS_VSCROLL | WS_HSCROLL);

	// 파일 열기
	CFile file;
	CString strFilePath = _T("./EditCtrl.vcxproj"); // 프로젝트 폴더에 있는 "EditCtrl.vcxproj" 파일 경로
	if (!file.Open(strFilePath, CFile::modeRead))
	{
		AfxMessageBox(_T("파일 열기 실패!"));
		return;
	}

	// ANSI 문자열을 담기 위한 버퍼
	char buffer[1025];

	// 유니코드 문자열을 담기 위한 버퍼
	WCHAR unicodeBuffer[1025];

	// 파일의 모든 내용을 읽어서 CString에 저장
	CString strText;
	UINT nBytesRead = 0;
	do
	{
		// 파일에서 다음 줄 읽기
		nBytesRead = file.Read(buffer, sizeof(buffer) - 1);
		buffer[nBytesRead] = 0; // null-terminated string으로 만들기

		// ANSI에서 유니코드로 변환
		MultiByteToWideChar(CP_ACP, 0, buffer, -1, unicodeBuffer, sizeof(unicodeBuffer) / sizeof(WCHAR));

		// 텍스트에 추가
		strText += unicodeBuffer;

	} while (nBytesRead > 0);

	// 파일 닫기
	file.Close();

	// 에디트 컨트롤에 텍스트 설정
	m_edit.SetWindowText(strText);
}




// CEditCtrlView 인쇄

BOOL CEditCtrlView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CEditCtrlView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CEditCtrlView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CEditCtrlView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: 여기에 사용자 지정 인쇄 코드를 추가합니다.
}


// CEditCtrlView 진단

#ifdef _DEBUG
void CEditCtrlView::AssertValid() const
{
	CFormView::AssertValid();
}

void CEditCtrlView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CEditCtrlDoc* CEditCtrlView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEditCtrlDoc)));
	return (CEditCtrlDoc*)m_pDocument;
}
#endif //_DEBUG


// CEditCtrlView 메시지 처리기


void CEditCtrlView::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CEditCtrlView::OnEnChangeMyedit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	m_edit.GetWindowText(str);
	m_static.SetWindowText(str);
	
}


void CEditCtrlView::OnEnMaxtextMyedit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	MessageBox(_T("최대 길이 도달!"), _T("오류"), MB_ICONERROR);
}


void CEditCtrlView::OnStnClickedMystatic()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
