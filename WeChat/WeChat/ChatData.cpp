#include "stdafx.h"
#include "ChatData.h"

int newId() {
	static int id = 0;
	return id++;
}