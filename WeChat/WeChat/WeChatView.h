
// WeChatView.h : CWeChatView ��Ľӿ�
//

#pragma once


class CWeChatView : public CScrollView
{
protected: // �������л�����
	CWeChatView();
	DECLARE_DYNCREATE(CWeChatView)

// ����
public:
	CWeChatDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CWeChatView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // WeChatView.cpp �еĵ��԰汾
inline CWeChatDoc* CWeChatView::GetDocument() const
   { return reinterpret_cast<CWeChatDoc*>(m_pDocument); }
#endif

