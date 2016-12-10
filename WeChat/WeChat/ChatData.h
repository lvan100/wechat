#pragma once

#include <assert.h>

class ChatBubble {
public:
	void Draw(CDC* pDC, CRect rect) {

		if (m_bubble.IsNull()) {
			m_bubble.Load(L"bubble.png");
		}

		if (m_brush_left.GetSafeHandle() == NULL) {
			CImage img;
			img.Create(14, 7, 32);
			m_bubble.BitBlt(img.GetDC(), 0, 0, 14, 7, 0, 28, SRCCOPY);
			img.ReleaseDC();
			m_brush_left.CreatePatternBrush(CBitmap::FromHandle(img.Detach()));
		}

		if (m_brush_top.GetSafeHandle() == NULL) {
			CImage img;
			img.Create(14, 28, 32);
			m_bubble.BitBlt(img.GetDC(), 0, 0, 14, 28, 14, 0, SRCCOPY);
			img.ReleaseDC();
			m_brush_top.CreatePatternBrush(CBitmap::FromHandle(img.Detach()));
		}

		if (m_brush_right.GetSafeHandle() == NULL) {
			CImage img;
			img.Create(7, 7, 32);
			m_bubble.BitBlt(img.GetDC(), 0, 0, 7, 7, 30, 28, SRCCOPY);
			img.ReleaseDC();
			m_brush_right.CreatePatternBrush(CBitmap::FromHandle(img.Detach()));
		}

		if (m_brush_bottom.GetSafeHandle() == NULL) {
			CImage img;
			img.Create(14, 7, 32);
			m_bubble.BitBlt(img.GetDC(), 0, 0, 14, 7, 14, 35, SRCCOPY);
			img.ReleaseDC();
			m_brush_bottom.CreatePatternBrush(CBitmap::FromHandle(img.Detach()));
		}

		m_bubble.BitBlt(pDC->GetSafeHdc(), rect.left, rect.top, 14, 28, 0, 0, SRCCOPY);
		m_bubble.BitBlt(pDC->GetSafeHdc(), rect.left, rect.bottom - 7, 14, 7, 0, 35, SRCCOPY);

		m_bubble.BitBlt(pDC->GetSafeHdc(), rect.right - 7, rect.top, 7, 28, 30, 0, SRCCOPY);
		m_bubble.BitBlt(pDC->GetSafeHdc(), rect.right - 7, rect.bottom - 7, 7, 7, 30, 35, SRCCOPY);

		CPoint oldPoint = pDC->GetBrushOrg();

		pDC->SetBrushOrg(rect.left, rect.top + 28);
		pDC->FillRect(CRect(rect.left, rect.top + 28, rect.left + 14, rect.bottom - 7), &m_brush_left);

		pDC->SetBrushOrg(rect.right - 7, rect.top + 28);
		pDC->FillRect(CRect(rect.right - 7, rect.top + 28, rect.right, rect.bottom - 7), &m_brush_right);

		pDC->SetBrushOrg(rect.left + 14, rect.top);
		pDC->FillRect(CRect(rect.left + 14, rect.top, rect.right - 7, rect.top + 28), &m_brush_top);

		pDC->SetBrushOrg(rect.left + 14, rect.bottom - 7);
		pDC->FillRect(CRect(rect.left + 14, rect.bottom - 7, rect.right - 7, rect.bottom), &m_brush_bottom);

		pDC->SetBrushOrg(oldPoint);
	}

protected:
	CImage m_bubble;

	CBrush m_brush_left;
	CBrush m_brush_right;

	CBrush m_brush_top;
	CBrush m_brush_bottom;
};

extern ChatBubble theChatBubble;

#define MAX_TEXT_WIDTH	500
#define MAX_IMAGE_WIDTH	100

#define HEAD_WIDTH		100

#define MARGIN_LEFT		12
#define MARGIN_RIGHT	6

#define MARGIN_TOP		12
#define MARGIN_BOTTOM	12

extern int newId();

class ChatData {

public:
	ChatData() : haveSize(false) {
		m_id.Format(L"%d", newId());
	}

	virtual ~ChatData() {}

public:
	virtual int Show(CDC* pDC, int offsetY) = 0;
	virtual int getHeight(CDC* pDC) = 0;

	int getHeight() { return m_height; }

protected:
	bool haveSize;
	int m_height;

	CString m_id;
};

class TextChatData : public ChatData
{
public:
	TextChatData(CString str) : text(str) {
	}

	virtual int Show(CDC* pDC, int offsetY) {
		assert(haveSize);

		CRect rect;

		rect.left = 0;
		rect.right = HEAD_WIDTH;
		rect.top = offsetY + MARGIN_TOP / 2;
		rect.bottom = offsetY + m_height - MARGIN_BOTTOM / 2;

		pDC->DrawText(m_id, rect, DT_LEFT | DT_TOP);

		rect.left = HEAD_WIDTH;
		rect.right = MAX_TEXT_WIDTH + HEAD_WIDTH + MARGIN_LEFT + MARGIN_RIGHT;

		theChatBubble.Draw(pDC, rect);

		rect.left = HEAD_WIDTH + MARGIN_LEFT;
		rect.right = MAX_TEXT_WIDTH + HEAD_WIDTH + MARGIN_LEFT;

		rect.top = offsetY + MARGIN_TOP;
		rect.bottom = offsetY + m_height - MARGIN_BOTTOM;

		pDC->DrawText(text, rect, DT_LEFT | DT_TOP | DT_WORDBREAK);

		return m_height;
	}

	virtual int getHeight(CDC* pDC) {
		if (haveSize) {
			return m_height;
		}

		haveSize = true;

		CRect rect(0, 0, MAX_TEXT_WIDTH, MAXINT);
		m_height = pDC->DrawText(text, rect, DT_LEFT | DT_TOP | DT_CALCRECT | DT_WORDBREAK);

		m_height += MARGIN_TOP + MARGIN_BOTTOM;
		return m_height;
	}

protected:
	CString text;
};

class ImageChatData : public ChatData
{
public:
	ImageChatData(CImage& img) : image(img) {
	}

	virtual int Show(CDC* pDC, int offsetY) {
		assert(haveSize);

		CRect rect;

		rect.left = 0;
		rect.right = HEAD_WIDTH;
		rect.top = offsetY + MARGIN_TOP / 2;
		rect.bottom = offsetY + m_height - MARGIN_BOTTOM / 2;

		pDC->DrawText(m_id, rect, DT_LEFT | DT_TOP);

		rect.left = HEAD_WIDTH;
		rect.right = m_width + HEAD_WIDTH + MARGIN_LEFT + MARGIN_RIGHT;

		theChatBubble.Draw(pDC, rect);

		rect.left = HEAD_WIDTH + MARGIN_LEFT;
		rect.right = m_width + HEAD_WIDTH + MARGIN_LEFT;

		rect.top = offsetY + MARGIN_TOP;
		rect.bottom = offsetY + m_height - MARGIN_BOTTOM;

		image.Draw(pDC->GetSafeHdc(), rect);

		return m_height;
	}

	virtual int getHeight(CDC* pDC) {
		if (haveSize) {
			return m_height;
		}

		haveSize = true;

		m_width = min(image.GetWidth(), MAX_IMAGE_WIDTH);
		m_height = m_width * image.GetHeight() / image.GetWidth();

		m_height += MARGIN_TOP + MARGIN_BOTTOM;
		return m_height;
	}

protected:
	CImage image;
	int m_width;
};