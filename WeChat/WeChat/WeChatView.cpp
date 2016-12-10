
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

static CString g_str_data = L"�ڸ����ľ����ڵ��øó�Ա������ʽ���ı���\
		ͨ�����Ʊ�ֵ��չ���ʵ���С��ʹ�ı��ڸ�������������롢�Ҷ���\
		����У�ʹ�ı��ϳɶ�������Ӧ������������ʽ���ı�����ʽ������\
		nFormatָ����\n�ó�Ա������Ӧ�豸��������ѡȡ�����塢�ı���ɫ\
         ������ɫ����ʾ����";

static CImage g_img_data;

// CWeChatView

IMPLEMENT_DYNCREATE(CWeChatView, CScrollView)

BEGIN_MESSAGE_MAP(CWeChatView, CScrollView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_SAVE, &CWeChatView::OnFileSave)
	ON_COMMAND(ID_FILE_OPEN, &CWeChatView::OnFileOpen)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_FILE_NEW, &CWeChatView::OnFileNew)
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

int paintCount = 0;

void CWeChatView::OnDraw(CDC* pDC)
{
	if (dataList.size() > 0) {

		DWORD start = GetTickCount();

		CRect rcView;
		GetClientRect(rcView);

		CDC memDC;
		memDC.CreateCompatibleDC(pDC);

		CBitmap bmp;
		bmp.CreateCompatibleBitmap(pDC, rcView.Width(), rcView.Height());

		memDC.SelectObject(&bmp);
		memDC.FillSolidRect(rcView, RGB(255, 255, 255));

		CPoint pt = GetScrollPosition();
		int offsetY = 0 - pt.y;

		for (auto iter = dataList.begin(); iter != dataList.end(); iter++) {
			offsetY += (*iter)->Show(&memDC, offsetY);
		}

		pDC->BitBlt(pt.x, pt.y, rcView.Width(), rcView.Height(), &memDC, 0, 0, SRCCOPY);

		CString str;
		str.Format(L"paintCount:%d time:%ld\n", paintCount++, GetTickCount() - start);
		OutputDebugString(str);
	}
}

void CWeChatView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	if (g_img_data.IsNull()) {
		g_img_data.Load(L"learn_xml.gif");
	}

	CSize sizeTotal;
	sizeTotal.cx = sizeTotal.cy = 0;
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


/**
 * ����1�������ݼ�����Ե�λ�������ʱ��
 */
void testCalcSize(CDC* pDC) {

	list<unique_ptr<ChatData>> dataList;

	int strCount = 0;
	int imgCount = 0;

	DWORD start = GetTickCount();

	for (int i = 0; i < 10000; i++) {
		ChatData* data = nullptr;

		if (rand() % 2 == 0) {
			strCount++;
			data = new TextChatData(g_str_data);
		} else {
			imgCount++;
			data = new ImageChatData(g_img_data);
		}

		dataList.push_back(unique_ptr<ChatData>(data));
	}

	CString str;
	str.Format(L"strCount:%d imgCount:%d initTime:%d\n", strCount, imgCount, GetTickCount() - start);
	OutputDebugString(str);

	start = GetTickCount();

	int offsetY = 0;
	for (auto iter = dataList.begin(); iter != dataList.end(); iter++) {
		offsetY += (*iter)->getHeight(pDC);
		offsetY += 8;
	}

	str.Format(L"(1) calcSizeTime:%d\n", GetTickCount() - start);
	OutputDebugString(str);

	start = GetTickCount();

	offsetY = 0;
	for (auto iter = dataList.begin(); iter != dataList.end(); iter++) {
		offsetY += (*iter)->getHeight(pDC);
		offsetY += 8;
	}

	str.Format(L"(2) calcSizeTime:%d\n", GetTickCount() - start);
	OutputDebugString(str);
}

int CWeChatView::loadMoreData(InsertPos pos) {

	CDC* pDC = GetDC();

	int newItemsHeight = 0;

	for (int i = 0; i < rand() % 15; i++) {
		ChatData* data = nullptr;

		if (rand() % 2 == 0) {
			data = new TextChatData(g_str_data);
		} else {
			data = new ImageChatData(g_img_data);
		}

		if (pos == InsertPos::Front) {
			dataList.push_front(unique_ptr<ChatData>(data));
		} else {
			dataList.push_back(unique_ptr<ChatData>(data));
		}

		newItemsHeight += data->getHeight(pDC);
	}

	return newItemsHeight;
}

void CWeChatView::OnFileSave()
{
	int newItemsHeight = loadMoreData(InsertPos::Back);

	CSize size = GetTotalSize();
	size.cy += newItemsHeight;

	SetScrollSizes(MM_TEXT, size);
}

void CWeChatView::OnFileOpen()
{
	int newItemsHeight = loadMoreData(InsertPos::Front);

	CSize size = GetTotalSize();
	size.cy += newItemsHeight;

	CPoint pt = GetScrollPosition();
	pt.y += newItemsHeight;

	paintCount = 0;

	SetScrollSizes(MM_TEXT, size);
	ScrollToPosition(pt);
	Invalidate();
}

BOOL CWeChatView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CWeChatView::OnFileNew()
{
	testCalcSize(GetDC());
}
