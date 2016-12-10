#pragma once

#include <assert.h>

#define MAX_TEXT_WIDTH	300
#define MAX_IMAGE_WIDTH	100

extern int newId();

class ChatData {

public:
	ChatData() : haveSize(false) {
		m_id.Format(L"%d", newId());
	}

public:
	virtual int Show(CDC* pDC, int offsetY) = 0;
	virtual int getHeight(CDC* pDC) = 0;

protected:
	bool haveSize;
	int m_height;

	CString m_id;
};

class TextChatData : public ChatData
{
public:
	TextChatData(CString& str) : text(str) {
	}

	virtual int Show(CDC* pDC, int offsetY) {
		assert(haveSize);

		if (offsetY + m_height <= 0) {
			return m_height;
		}

		pDC->DrawText(m_id, CRect(0, offsetY, 100, offsetY + m_height), DT_LEFT | DT_TOP);
		pDC->DrawText(text, CRect(100, offsetY, MAX_TEXT_WIDTH + 100, offsetY + m_height), DT_LEFT | DT_TOP | DT_WORDBREAK);
		return m_height;
	}

	virtual int getHeight(CDC* pDC) {
		if (haveSize) {
			return m_height;
		}

		haveSize = true;
		return m_height = pDC->DrawText(text, CRect(0, 0, MAX_TEXT_WIDTH, MAXINT), DT_LEFT | DT_TOP | DT_CALCRECT | DT_WORDBREAK);
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

		if (offsetY + m_height <= 0) {
			return m_height;
		}

		pDC->DrawText(m_id, CRect(0, offsetY, 100, offsetY + m_height), DT_LEFT | DT_TOP);
		image.Draw(pDC->GetSafeHdc(), CRect(100, offsetY, m_width + 100, offsetY + m_height));
		return m_height;
	}

	virtual int getHeight(CDC* pDC) {
		if (haveSize) {
			return m_height;
		}

		haveSize = true;
		m_width = min(image.GetWidth(), MAX_IMAGE_WIDTH);
		return m_height = m_width * image.GetHeight() / image.GetWidth();
	}

protected:
	CImage image;
	int m_width;
};