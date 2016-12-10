#include "stdafx.h"
#include "ChatData.h"

ChatBubble theChatBubble;

int newId() {
	static int id = 0;
	return id++;
}