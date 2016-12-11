#pragma once

#include <assert.h>

class ChatBubble {

public:
	const int horizon_left = 14;
	const int horizon_center = 16;
	const int horizon_right = 7;

	const int vertical_top = 28;
	const int vertical_center = 7;
	const int vertical_bottom = 7;

public:
	void Draw(CDC* pDC, CRect rect) {

		if (m_bubble.IsNull()) {
			m_bubble.Load(L"bubble.png");
		}

		// 九宫格切图原理示意图:
		//
		//                        horizon_left   |   horizon_center   |    horizon_right
		//                    |—————————|——————————|——————————|
		//                    |                  |                    |                    |
		//  vertical_top      |        1         |          2         |          3         |
		//                    |                  |                    |                    |
		//                 ———————————|——————————|————————————
		//                    |                  |                    |                    |
		//   vertical_center  |        4         |          5         |          6         |
		//                    |                  |                    |                    |
		//                 ———————————|——————————|————————————
		//                    |                  |                    |                    |
		//   vertical_bottom  |        7         |          8         |          9         |
		//                    |                  |                    |                    |
		//                    |—————————|——————————|——————————|
		//                                       |                    |

		if (m_brush_left.GetSafeHandle() == NULL) { // 制作 4 的画刷
			CImage img;
			img.Create(horizon_left, vertical_center, 32);
			m_bubble.BitBlt(img.GetDC(), 0, 0, img.GetWidth(), img.GetHeight(), 0, vertical_top, SRCCOPY);
			img.ReleaseDC();
			m_brush_left.CreatePatternBrush(CBitmap::FromHandle(img.Detach()));
		}

		if (m_brush_top.GetSafeHandle() == NULL) { // 制作 2 的画刷
			CImage img;
			img.Create(horizon_center, vertical_top, 32);
			m_bubble.BitBlt(img.GetDC(), 0, 0, img.GetWidth(), img.GetHeight(), horizon_left, 0, SRCCOPY);
			img.ReleaseDC();
			m_brush_top.CreatePatternBrush(CBitmap::FromHandle(img.Detach()));
		}

		if (m_brush_right.GetSafeHandle() == NULL) { // 制作 6 的画刷
			CImage img;
			img.Create(horizon_right, vertical_center, 32);
			m_bubble.BitBlt(img.GetDC(), 0, 0, img.GetWidth(), img.GetHeight(), horizon_left + horizon_center, vertical_top, SRCCOPY);
			img.ReleaseDC();
			m_brush_right.CreatePatternBrush(CBitmap::FromHandle(img.Detach()));
		}

		if (m_brush_bottom.GetSafeHandle() == NULL) { // 制作 8 的画刷
			CImage img;
			img.Create(horizon_center, vertical_bottom, 32);
			m_bubble.BitBlt(img.GetDC(), 0, 0, img.GetWidth(), img.GetHeight(), horizon_left, vertical_top + vertical_center, SRCCOPY);
			img.ReleaseDC();
			m_brush_bottom.CreatePatternBrush(CBitmap::FromHandle(img.Detach()));
		}

		if (m_brush_center.GetSafeHandle() == NULL) { // 制作 5 的画刷
			CImage img;
			img.Create(horizon_center, vertical_center, 32);
			m_bubble.BitBlt(img.GetDC(), 0, 0, img.GetWidth(), img.GetHeight(), horizon_left, vertical_top, SRCCOPY);
			img.ReleaseDC();
			m_brush_center.CreatePatternBrush(CBitmap::FromHandle(img.Detach()));
		}

		// 绘制 1 区图像
		m_bubble.BitBlt(pDC->GetSafeHdc(), rect.left, rect.top, horizon_left, vertical_top, 0, 0, SRCCOPY);
		// 绘制 7 区图像
		m_bubble.BitBlt(pDC->GetSafeHdc(), rect.left, rect.bottom - vertical_bottom, horizon_left, vertical_bottom, 0, vertical_top + vertical_center, SRCCOPY);

		// 绘制 3 区图像
		m_bubble.BitBlt(pDC->GetSafeHdc(), rect.right - horizon_right, rect.top, horizon_right, vertical_top, horizon_left + horizon_center, 0, SRCCOPY);
		// 绘制 9 区图像
		m_bubble.BitBlt(pDC->GetSafeHdc(), rect.right - horizon_right, rect.bottom - vertical_bottom, horizon_right, vertical_bottom, horizon_left + horizon_center, vertical_top + vertical_center, SRCCOPY);

		CPoint oldPoint = pDC->GetBrushOrg();

		// 绘制 4 区图像
		pDC->SetBrushOrg(rect.left, rect.top + vertical_top);
		pDC->FillRect(CRect(rect.left, rect.top + vertical_top, rect.left + horizon_left, rect.bottom - vertical_bottom), &m_brush_left);

		// 绘制 6 区图像
		pDC->SetBrushOrg(rect.right - horizon_right, rect.top + vertical_top);
		pDC->FillRect(CRect(rect.right - horizon_right, rect.top + vertical_top, rect.right, rect.bottom - vertical_bottom), &m_brush_right);

		// 绘制 2 区图像
		pDC->SetBrushOrg(rect.left + horizon_left, rect.top);
		pDC->FillRect(CRect(rect.left + horizon_left, rect.top, rect.right - horizon_right, rect.top + vertical_top), &m_brush_top);

		// 绘制 8 区图像
		pDC->SetBrushOrg(rect.left + horizon_left, rect.bottom - vertical_bottom);
		pDC->FillRect(CRect(rect.left + horizon_left, rect.bottom - vertical_bottom, rect.right - horizon_right, rect.bottom), &m_brush_bottom);

		// 绘制 5 区图像
		pDC->SetBrushOrg(rect.left + horizon_left, rect.top + vertical_top);
		pDC->FillRect(CRect(rect.left + horizon_left, rect.top + vertical_top, rect.right - horizon_right, rect.bottom - vertical_bottom), &m_brush_center);

		pDC->SetBrushOrg(oldPoint);
	}

protected:
	CImage m_bubble;

	CBrush m_brush_left;
	CBrush m_brush_right;

	CBrush m_brush_top;
	CBrush m_brush_bottom;

	CBrush m_brush_center;
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

		pDC->SetBkMode(TRANSPARENT);
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