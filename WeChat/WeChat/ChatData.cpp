#include "stdafx.h"
#include "ChatData.h"

ChatBubble theChatBubble;
ChatBubble theChatHoverBubble;

int newId() {
	static int id = 0;
	return id++;
}