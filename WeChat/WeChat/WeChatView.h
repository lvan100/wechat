
// WeChatView.h : CWeChatView 类的接口
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
protected: // 仅从序列化创建
	CWeChatView();
	DECLARE_DYNCREATE(CWeChatView)

// 特性
public:
	CWeChatDoc* GetDocument() const;

	CFont m_text_font;

// 操作
public:
	int loadMoreData(InsertPos pos);

private:
	list<unique_ptr<ChatData>> dataList;

	void ReDraw();

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
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

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileNew();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

#ifndef _DEBUG  // WeChatView.cpp 中的调试版本
inline CWeChatDoc* CWeChatView::GetDocument() const
   { return reinterpret_cast<CWeChatDoc*>(m_pDocument); }
#endif

