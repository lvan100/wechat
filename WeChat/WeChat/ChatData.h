#pragma once

#include <assert.h>

/**
 * ��������
 */
class ChatBubble {

public:
	const int horizon_left = 14;
	const int horizon_center = 16;
	const int horizon_right = 7;

	const int vertical_top = 28;
	const int vertical_center = 7;
	const int vertical_bottom = 7;

	// �Ź�����ͼԭ��ʾ��ͼ:
	//
	//                        horizon_left   |   horizon_center   |    horizon_right
	//                    |������������������|��������������������|��������������������|
	//                    |                  |                    |                    |
	//  vertical_top      |        1         |          2         |          3         |
	//                    |                  |                    |                    |
	//                 ����������������������|��������������������|������������������������
	//                    |                  |                    |                    |
	//   vertical_center  |        4         |          5         |          6         |
	//                    |                  |                    |                    |
	//                 ����������������������|��������������������|������������������������
	//                    |                  |                    |                    |
	//   vertical_bottom  |        7         |          8         |          9         |
	//                    |                  |                    |                    |
	//                    |������������������|��������������������|��������������������|
	//                                       |                    |

public:
	void LoadImage(CString imgPath) {
		if (m_bubble.IsNull()) {
			m_bubble.Load(imgPath);
		}
	}

	void Draw(CDC* pDC, CRect rect) {

		if (m_brush_left.GetSafeHandle() == NULL) { // ���� 4 �Ļ�ˢ
			CImage img;
			img.Create(horizon_left, vertical_center, 32);
			m_bubble.BitBlt(img.GetDC(), 0, 0, img.GetWidth(), img.GetHeight(), 0, vertical_top, SRCCOPY);
			img.ReleaseDC();
			m_brush_left.CreatePatternBrush(CBitmap::FromHandle(img.Detach()));
		}

		if (m_brush_top.GetSafeHandle() == NULL) { // ���� 2 �Ļ�ˢ
			CImage img;
			img.Create(horizon_center, vertical_top, 32);
			m_bubble.BitBlt(img.GetDC(), 0, 0, img.GetWidth(), img.GetHeight(), horizon_left, 0, SRCCOPY);
			img.ReleaseDC();
			m_brush_top.CreatePatternBrush(CBitmap::FromHandle(img.Detach()));
		}

		if (m_brush_right.GetSafeHandle() == NULL) { // ���� 6 �Ļ�ˢ
			CImage img;
			img.Create(horizon_right, vertical_center, 32);
			m_bubble.BitBlt(img.GetDC(), 0, 0, img.GetWidth(), img.GetHeight(), horizon_left + horizon_center, vertical_top, SRCCOPY);
			img.ReleaseDC();
			m_brush_right.CreatePatternBrush(CBitmap::FromHandle(img.Detach()));
		}

		if (m_brush_bottom.GetSafeHandle() == NULL) { // ���� 8 �Ļ�ˢ
			CImage img;
			img.Create(horizon_center, vertical_bottom, 32);
			m_bubble.BitBlt(img.GetDC(), 0, 0, img.GetWidth(), img.GetHeight(), horizon_left, vertical_top + vertical_center, SRCCOPY);
			img.ReleaseDC();
			m_brush_bottom.CreatePatternBrush(CBitmap::FromHandle(img.Detach()));
		}

		if (m_brush_center.GetSafeHandle() == NULL) { // ���� 5 �Ļ�ˢ
			CImage img;
			img.Create(horizon_center, vertical_center, 32);
			m_bubble.BitBlt(img.GetDC(), 0, 0, img.GetWidth(), img.GetHeight(), horizon_left, vertical_top, SRCCOPY);
			img.ReleaseDC();
			m_brush_center.CreatePatternBrush(CBitmap::FromHandle(img.Detach()));
		}

		// ���� 1 ��ͼ��
		m_bubble.BitBlt(pDC->GetSafeHdc(), rect.left, rect.top, horizon_left, vertical_top, 0, 0, SRCCOPY);
		// ���� 7 ��ͼ��
		m_bubble.BitBlt(pDC->GetSafeHdc(), rect.left, rect.bottom - vertical_bottom, horizon_left, vertical_bottom, 0, vertical_top + vertical_center, SRCCOPY);

		// ���� 3 ��ͼ��
		m_bubble.BitBlt(pDC->GetSafeHdc(), rect.right - horizon_right, rect.top, horizon_right, vertical_top, horizon_left + horizon_center, 0, SRCCOPY);
		// ���� 9 ��ͼ��
		m_bubble.BitBlt(pDC->GetSafeHdc(), rect.right - horizon_right, rect.bottom - vertical_bottom, horizon_right, vertical_bottom, horizon_left + horizon_center, vertical_top + vertical_center, SRCCOPY);

		CPoint oldPoint = pDC->GetBrushOrg();

		// ���� 4 ��ͼ��
		pDC->SetBrushOrg(rect.left, rect.top + vertical_top);
		pDC->FillRect(CRect(rect.left, rect.top + vertical_top, rect.left + horizon_left, rect.bottom - vertical_bottom), &m_brush_left);

		// ���� 6 ��ͼ��
		pDC->SetBrushOrg(rect.right - horizon_right, rect.top + vertical_top);
		pDC->FillRect(CRect(rect.right - horizon_right, rect.top + vertical_top, rect.right, rect.bottom - vertical_bottom), &m_brush_right);

		// ���� 2 ��ͼ��
		pDC->SetBrushOrg(rect.left + horizon_left, rect.top);
		pDC->FillRect(CRect(rect.left + horizon_left, rect.top, rect.right - horizon_right, rect.top + vertical_top), &m_brush_top);

		// ���� 8 ��ͼ��
		pDC->SetBrushOrg(rect.left + horizon_left, rect.bottom - vertical_bottom);
		pDC->FillRect(CRect(rect.left + horizon_left, rect.bottom - vertical_bottom, rect.right - horizon_right, rect.bottom), &m_brush_bottom);

		// ���� 5 ��ͼ��
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
extern ChatBubble theChatHoverBubble;


#define MAX_CHAT_WIDTH	500

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
	/**
	 * ������������
	 */
	int Draw(CDC* pDC, int offsetY, CPoint ptHover) {
		assert(haveSize);

		CRect rect;

		rect.left = 0;
		rect.right = HEAD_WIDTH;
		rect.top = offsetY + MARGIN_TOP / 2;
		rect.bottom = offsetY + m_size.cy - MARGIN_BOTTOM / 2;

		pDC->DrawText(m_id, rect, DT_LEFT | DT_TOP);

		rect.left = HEAD_WIDTH;
		rect.right = m_size.cx + HEAD_WIDTH + MARGIN_LEFT + MARGIN_RIGHT;

		if (rect.PtInRect(ptHover)) {
			theChatHoverBubble.Draw(pDC, rect);
		} else {
			theChatBubble.Draw(pDC, rect);
		}

		rect.left = HEAD_WIDTH + MARGIN_LEFT;
		rect.right = m_size.cx + HEAD_WIDTH + MARGIN_LEFT;

		rect.top = offsetY + MARGIN_TOP;
		rect.bottom = offsetY + m_size.cy - MARGIN_BOTTOM;

		DrawChatData(pDC, rect);

		return m_size.cy;
	}

	/**
	 * ������ʾ����Ĵ�С
	 */
	int CalcSize(CDC* pDC) {
		if (haveSize) {
			return m_size.cy;
		}

		haveSize = true;

		m_size = CalcChatDataSize(pDC);
		m_size.cy += MARGIN_TOP + MARGIN_BOTTOM;

		return m_size.cy;
	}

	/**
	 * ��ȡ��ʾ����ĸ߶�
	 */
	int GetHeight() {
		assert(haveSize);
		return m_size.cy;
	}

protected:
	/**
	 * ������������
	 */
	virtual void DrawChatData(CDC* pDC, CRect rect) = 0;

	/**
	 * �����������ݵ���ʾ����
	 */
	virtual CSize CalcChatDataSize(CDC* pDC) = 0;

protected:
	/**
	 * �Ƿ�������ʾ����
	 */
	bool haveSize;

	/**
	 * ��ʾ����Ĵ�С
	 */
	CSize m_size;

	/**
	 * ��Ϣ��ID
	 */
	CString m_id;
};

/**
 * ����������Ϣ
 */
class TextChatData : public ChatData
{
public:
	TextChatData(CString str) : text(str) {
	}

protected:
	virtual void DrawChatData(CDC* pDC, CRect rect) override {
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(text, rect, DT_LEFT | DT_TOP | DT_WORDBREAK);
	}

	virtual CSize CalcChatDataSize(CDC* pDC) override {
		CRect rect(0, 0, MAX_CHAT_WIDTH, MAXINT);
		pDC->DrawText(text, rect, DT_LEFT | DT_TOP | DT_CALCRECT | DT_WORDBREAK);
		return rect.Size();
	}

protected:
	CString text;
};

/**
 * ͼƬ������Ϣ
 */
class ImageChatData : public ChatData
{
public:
	ImageChatData(CImage& img) : image(img) {
	}

	virtual void DrawChatData(CDC* pDC, CRect rect) override {
		rect.right = m_img_size.cx + HEAD_WIDTH + MARGIN_LEFT;
		image.Draw(pDC->GetSafeHdc(), rect);
	}

	virtual CSize CalcChatDataSize(CDC* pDC) override {
		m_img_size.cx = min(image.GetWidth(), MAX_CHAT_WIDTH);
		m_img_size.cy = m_img_size.cx * image.GetHeight() / image.GetWidth();
		return m_img_size;
	}

protected:
	CImage image;

	/**
	 * ͼ�����ʾ��С
	 */
	CSize m_img_size;
};