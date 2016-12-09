
// WeChatView.cpp : CWeChatView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "WeChat.h"
#endif

#include "WeChatDoc.h"
#include "WeChatView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWeChatView

IMPLEMENT_DYNCREATE(CWeChatView, CScrollView)

BEGIN_MESSAGE_MAP(CWeChatView, CScrollView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CWeChatView ����/����

CWeChatView::CWeChatView()
{
	// TODO: �ڴ˴���ӹ������

}

CWeChatView::~CWeChatView()
{
}

BOOL CWeChatView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CScrollView::PreCreateWindow(cs);
}

// CWeChatView ����

void CWeChatView::OnDraw(CDC* /*pDC*/)
{
	CWeChatDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}

void CWeChatView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: �������ͼ�ĺϼƴ�С
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CWeChatView ��ӡ

BOOL CWeChatView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CWeChatView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CWeChatView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CWeChatView ���

#ifdef _DEBUG
void CWeChatView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CWeChatView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CWeChatDoc* CWeChatView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWeChatDoc)));
	return (CWeChatDoc*)m_pDocument;
}
#endif //_DEBUG


// CWeChatView ��Ϣ�������
