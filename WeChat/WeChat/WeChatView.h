
// WeChatView.h : CWeChatView ��Ľӿ�
//

#pragma once

#include "ChatData.h"

#include <list>
#include <memory>
using namespace std;

enum InsertPos {
	Front,
	Back,
};

class CWeChatView : public CScrollView
{
protected: // �������л�����
	CWeChatView();
	DECLARE_DYNCREATE(CWeChatView)

// ����
public:
	CWeChatDoc* GetDocument() const;

	CFont m_text_font;

// ����
public:
	int loadMoreData(InsertPos pos);

	ChatData* HitTest(CPoint point);

private:
	/**
	 * ��һ����갴�µ�������Ϣ
	 */
	ChatData* m_last_press_chat = nullptr;

	/**
	 * ��һ�λ��е�������Ϣ
	 */
	ChatData* m_last_hover_chat = nullptr;

	/**
	 * ������Ϣ�б�
	 */
	list<unique_ptr<ChatData>> dataList;

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	virtual BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE);
	virtual BOOL OnScrollBy(CSize sizeScroll, BOOL bDoScroll = TRUE);

// ʵ��
public:
	virtual ~CWeChatView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	afx_msg void OnFileSave();
	afx_msg void OnFileOpen();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileNew();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	afx_msg LRESULT OnLoadMoreData(WPARAM wParam, LPARAM lParam);
};

#ifndef _DEBUG  // WeChatView.cpp �еĵ��԰汾
inline CWeChatDoc* CWeChatView::GetDocument() const
   { return reinterpret_cast<CWeChatDoc*>(m_pDocument); }
#endif

