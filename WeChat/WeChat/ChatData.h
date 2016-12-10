#pragma once

#include <assert.h>

#define MAX_TEXT_WIDTH	500
#define MAX_IMAGE_WIDTH	100

#define MARGIN_LEFT		100

#define MARGIN_TOP		4
#define MARGIN_BOTTOM	4

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
		rect.right = MARGIN_LEFT;
		rect.top = offsetY + MARGIN_TOP;
		rect.bottom = offsetY + m_height - MARGIN_BOTTOM;

		pDC->DrawText(m_id, rect, DT_LEFT | DT_TOP);

		rect.left = MARGIN_LEFT;
		rect.right = MAX_TEXT_WIDTH + MARGIN_LEFT;

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
		rect.right = MARGIN_LEFT;
		rect.top = offsetY + MARGIN_TOP;
		rect.bottom = offsetY + m_height - MARGIN_BOTTOM;

		pDC->DrawText(m_id, rect, DT_LEFT | DT_TOP);

		rect.left = MARGIN_LEFT;
		rect.right = m_width + MARGIN_LEFT;

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