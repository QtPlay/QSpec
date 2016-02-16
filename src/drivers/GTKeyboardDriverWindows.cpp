/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2016 UniPro <ugene@unipro.ru>
 * http://ugene.unipro.ru
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#include <cctype>
#include "GTKeyboardDriver.h"
#include <QtGui/QClipboard>

#ifdef _WIN32
    #include <windows.h>
    #define VIRTUAL_TO_SCAN_CODE 0
#endif
#define GT_METHOD_NAME "keyPress"

namespace HI {

#ifdef _WIN32

#define GT_CLASS_NAME "GTKeyboardDriver Windows"
namespace{
INPUT getKeyEvent(int key, bool keyUp = false, bool extended = false) {
	INPUT event;
	event.type = INPUT_KEYBOARD;
	event.ki.wVk = key;
	event.ki.wScan = MapVirtualKey(key, VIRTUAL_TO_SCAN_CODE);
	event.ki.dwFlags = keyUp ? KEYEVENTF_KEYUP : 0;
	event.ki.time = 0;
	event.ki.dwExtraInfo = 0;
	if (extended){
		event.ki.dwFlags |= KEYEVENTF_EXTENDEDKEY;
	}

	return event;
}

void keyPressWindows(GUITestOpStatus &os, int key, int modifiers = 0, bool extended = false) {
	GT_CHECK(key != 0, " Error: key = 0 in GTKeyboardDriver::keyPress()");

	if (modifiers) {
		INPUT input = getKeyEvent(modifiers);
		SendInput(1, &input, sizeof(input));
	}

	INPUT input = getKeyEvent(key, false, extended);
	SendInput(1, &input, sizeof(input));
}
#undef GT_METHOD_NAME

#define GT_METHOD_NAME "keyRelease"
void keyReleaseWindows(GUITestOpStatus &os, int key, int modifiers = 0, bool extended = false)
{
	GT_CHECK(key != 0, " Error: key = 0 in GTKeyboardDriver::keyRelease()");

	if (modifiers) {
		INPUT input = getKeyEvent(modifiers, true);
		SendInput(1, &input, sizeof(input));
	}

	INPUT input = getKeyEvent(key, true, extended);
	SendInput(1, &input, sizeof(input));
}
#undef GT_METHOD_NAME
}

void GTKeyboardDriver::keyPress(GUITestOpStatus &os, char key, Qt::KeyboardModifiers modifiers)
{
    if (isalpha(key)) {
        key = toupper(key);
    }

	QList<Qt::Key> modKeys = modifiersToKeys(modifiers);
	foreach(Qt::Key mod, modKeys){
		keyPressWindows(os, mod);
	}

    switch (key) {
        case '-':
			keyPressWindows(os, VK_OEM_MINUS);
            break;
        case '_':
            keyPressWindows(os, VK_OEM_MINUS, GTKeyboardDriver::key[Qt::Key_Shift]);
            break;
        case '=':
            keyPressWindows(os, VK_OEM_PLUS);
            break;
        case '.':
			keyPressWindows(os, VK_DECIMAL);
            break;
        case ',':
			keyPressWindows(os, VK_OEM_COMMA);
            break;
        case ']':
			keyPressWindows(os, VK_OEM_6);
            break;
        case '\\':
			keyPressWindows(os, VK_OEM_5);
            break;
        case '[':
			keyPressWindows(os, VK_OEM_4);
            break;
        case '/':
			keyPressWindows(os, VK_DIVIDE);
            break;
        case '\n':
			keyPressWindows(os, GTKeyboardDriver::key[Qt::Key_Enter]);
            break;
        case ':':
			keyPressWindows(os, VK_OEM_1, GTKeyboardDriver::key[Qt::Key_Shift]);
            break;
        case ';':
			keyPressWindows(os, VK_OEM_1);
            break;
        case '<':
			keyPressWindows(os, VK_OEM_COMMA, GTKeyboardDriver::key[Qt::Key_Shift]);
            break;
        case '>':
			keyPressWindows(os, VK_OEM_PERIOD, GTKeyboardDriver::key[Qt::Key_Shift]);
            break;
        case '(':
			keyPressWindows(os, '9', GTKeyboardDriver::key[Qt::Key_Shift]);
            break;
        case ')':
			keyPressWindows(os, '0', GTKeyboardDriver::key[Qt::Key_Shift]);
            break;
        case '"':
			keyPressWindows(os, VK_OEM_7, GTKeyboardDriver::key[Qt::Key_Shift]);
		case '\'':
			keyPressWindows(os, VK_OEM_7);
            break;
        case '!':
			keyPressWindows(os, '1', GTKeyboardDriver::key[Qt::Key_Shift]);
            break;
        case '@':
			keyPressWindows(os, '2', GTKeyboardDriver::key[Qt::Key_Shift]);
            break;
        case '#':
			keyPressWindows(os, '3', GTKeyboardDriver::key[Qt::Key_Shift]);
            break;
        case '$':
			keyPressWindows(os, '4', GTKeyboardDriver::key[Qt::Key_Shift]);
            break;
        case '%':
			keyPressWindows(os, '5', GTKeyboardDriver::key[Qt::Key_Shift]);
            break;
        case '^':
			keyPressWindows(os, '6', GTKeyboardDriver::key[Qt::Key_Shift]);
            break;
        case '&':
			keyPressWindows(os, '7', GTKeyboardDriver::key[Qt::Key_Shift]);
            break;
        case '*':
			keyPressWindows(os, '8', GTKeyboardDriver::key[Qt::Key_Shift]);
            break;
        case '+':
			keyPressWindows(os, VK_OEM_PLUS, GTKeyboardDriver::key[Qt::Key_Shift]);
            break;
        case '?':
			keyPressWindows(os, VK_OEM_2, GTKeyboardDriver::key[Qt::Key_Shift]);
            break;
		case '{':
			keyPressWindows(os, VK_OEM_4, GTKeyboardDriver::key[Qt::Key_Shift]);
			break;
		case '}':
			keyPressWindows(os, VK_OEM_6, GTKeyboardDriver::key[Qt::Key_Shift]);
			break;
		case '|':
			keyPressWindows(os, VK_OEM_5, GTKeyboardDriver::key[Qt::Key_Shift]);
			break;
        default:
			keyPressWindows(os, (int)key);
            break;
    }
}

void GTKeyboardDriver::keyRelease(GUITestOpStatus &os, char key, Qt::KeyboardModifiers modifiers)
{
    if (isalpha(key)) {
        key = toupper(key);
    }

    switch (key) {
        case '_':
            keyReleaseWindows(os, VK_OEM_MINUS, GTKeyboardDriver::key[Qt::Key_Shift]);
            break;
        case '=':
            keyReleaseWindows(os, VK_OEM_PLUS);
            break;
        case '.':
			keyReleaseWindows(os, VK_DECIMAL);
            break;
        case ',':
            keyReleaseWindows(os, VK_OEM_COMMA);
            break;
        case ']':
			keyReleaseWindows(os, VK_OEM_6);
            break;
        case '\\':
			keyReleaseWindows(os, VK_OEM_5);
            break;
        case '[':
			keyReleaseWindows(os, VK_OEM_4);
            break;
        case '/':
			keyReleaseWindows(os, VK_DIVIDE);
            break;
        case '\n':
			keyReleaseWindows(os, GTKeyboardDriver::key[Qt::Key_Enter]);
            break;
        case ':':
			keyReleaseWindows(os, VK_OEM_1, GTKeyboardDriver::key[Qt::Key_Shift]);
            break;
        case ';':
			keyReleaseWindows(os, VK_OEM_1);
            break;
        case '<':
			keyReleaseWindows(os, VK_OEM_COMMA, GTKeyboardDriver::key[Qt::Key_Shift]);
            break;
        case '>':
			keyReleaseWindows(os, VK_OEM_PERIOD, GTKeyboardDriver::key[Qt::Key_Shift]);
            break;
        case '(':
			keyReleaseWindows(os, '9', GTKeyboardDriver::key[Qt::Key_Shift]);
            break;
        case ')':
			keyReleaseWindows(os, '0', GTKeyboardDriver::key[Qt::Key_Shift]);
            break;
        case '"':
			keyReleaseWindows(os, VK_OEM_7, GTKeyboardDriver::key[Qt::Key_Shift]);
            break;
		case '\'':
			keyReleaseWindows(os, VK_OEM_7);
			break;
        case '!':
			keyReleaseWindows(os, '1', GTKeyboardDriver::key[Qt::Key_Shift]);
            break;
        case '@':
			keyReleaseWindows(os, '2', GTKeyboardDriver::key[Qt::Key_Shift]);
            break;
        case '#':
			keyReleaseWindows(os, '3', GTKeyboardDriver::key[Qt::Key_Shift]);
            break;
        case '$':
			keyReleaseWindows(os, '4', GTKeyboardDriver::key[Qt::Key_Shift]);
            break;
        case '%':
			keyReleaseWindows(os, '5', GTKeyboardDriver::key[Qt::Key_Shift]);
            break;
        case '^':
			keyReleaseWindows(os, '6', GTKeyboardDriver::key[Qt::Key_Shift]);
            break;
        case '&':
			keyReleaseWindows(os, '7', GTKeyboardDriver::key[Qt::Key_Shift]);
            break;
        case '*':
			keyReleaseWindows(os, '8', GTKeyboardDriver::key[Qt::Key_Shift]);
            break;
        case '+':
			keyReleaseWindows(os, VK_OEM_PLUS, GTKeyboardDriver::key[Qt::Key_Shift]);
            break;
        case '?':
			keyReleaseWindows(os, VK_OEM_2, GTKeyboardDriver::key[Qt::Key_Shift]);
            break;
		case '{':
			keyReleaseWindows(os, VK_OEM_4, GTKeyboardDriver::key[Qt::Key_Shift]);
			break;
		case '}':
			keyReleaseWindows(os, VK_OEM_6, GTKeyboardDriver::key[Qt::Key_Shift]);
			break;
		case '|':
			keyReleaseWindows(os, VK_OEM_5, GTKeyboardDriver::key[Qt::Key_Shift]);
			break;
        default:
			keyReleaseWindows(os, (int)key);
            break;

		QList<Qt::Key> modKeys = modifiersToKeys(modifiers);
		foreach(Qt::Key mod, modKeys){
			keyReleaseWindows(os, mod);
		}
    }
}

void GTKeyboardDriver::keyPress(GUITestOpStatus &os, Qt::Key key, Qt::KeyboardModifiers modifiers){
	QList<Qt::Key> modKeys = modifiersToKeys(modifiers);
	foreach(Qt::Key mod, modKeys){
		keyPressWindows(os, GTKeyboardDriver::key[mod]);
	}
	keyPressWindows(os, GTKeyboardDriver::key[key]);
}

void GTKeyboardDriver::keyRelease(GUITestOpStatus &os, Qt::Key key, Qt::KeyboardModifiers modifiers){
	keyReleaseWindows(os, GTKeyboardDriver::key[key]);
	QList<Qt::Key> modKeys = modifiersToKeys(modifiers);
	foreach(Qt::Key mod, modKeys){
		keyReleaseWindows(os, GTKeyboardDriver::key[mod]);
	}
}

GTKeyboardDriver::keys::keys()
{
    //ADD_KEY("context_menu", VK_APPS);
    //ADD_KEY("back", VK_BACK);
    ADD_KEY(Qt::Key_Tab, VK_TAB);
    //ADD_KEY("clear", VK_CLEAR);
    ADD_KEY(Qt::Key_Enter, VK_RETURN);
    ADD_KEY(Qt::Key_Shift, VK_SHIFT);
    ADD_KEY(Qt::Key_Shift, VK_RSHIFT);
    //ADD_KEY("lshift", VK_LSHIFT);
	ADD_KEY(Qt::Key_Control, VK_LCONTROL);
    //ADD_KEY("rctrl", VK_RCONTROL);
    //ADD_KEY("lctrl", VK_LCONTROL);
    ADD_KEY(Qt::Key_Alt, VK_MENU);
    //ADD_KEY("pause", VK_PAUSE);
    ADD_KEY(Qt::Key_Escape, VK_ESCAPE);
    ADD_KEY(Qt::Key_Space, VK_SPACE);
    ADD_KEY(Qt::Key_Left, VK_LEFT);
    ADD_KEY(Qt::Key_Up, VK_UP);
    ADD_KEY(Qt::Key_Right, VK_RIGHT);
    ADD_KEY(Qt::Key_Down, VK_DOWN);
    ADD_KEY(Qt::Key_Insert, VK_INSERT);
    ADD_KEY(Qt::Key_Delete, VK_DELETE);
    ADD_KEY(Qt::Key_PageUp, VK_PRIOR);
    ADD_KEY(Qt::Key_PageDown, VK_NEXT);
    //ADD_KEY("help", VK_HELP);
    ADD_KEY(Qt::Key_F1, VK_F1);
	ADD_KEY(Qt::Key_F2, VK_F2);
	ADD_KEY(Qt::Key_F3, VK_F3);
	ADD_KEY(Qt::Key_F4, VK_F4);
    ADD_KEY(Qt::Key_F5, VK_F5);
	ADD_KEY(Qt::Key_F6, VK_F6);
	ADD_KEY(Qt::Key_F7, VK_F7);
	ADD_KEY(Qt::Key_F8, VK_F8);
	ADD_KEY(Qt::Key_F9, VK_F9);
	ADD_KEY(Qt::Key_F10, VK_F10);
	ADD_KEY(Qt::Key_F12, VK_F12);
    ADD_KEY(Qt::Key_Home, VK_HOME);
    ADD_KEY(Qt::Key_End, VK_END);

// feel free to add other keys
// macro VK_* defined in WinUser.h
}

#undef GT_CLASS_NAME

#endif

} //namespace
