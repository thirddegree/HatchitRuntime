/**
**    Hatchit Engine
**    Copyright(c) 2015-2017 Third-Degree
**
**    GNU Lesser General Public License
**    This file may be used under the terms of the GNU Lesser
**    General Public License version 3 as published by the Free
**    Software Foundation and appearing in the file LICENSE.LGPLv3 included
**    in the packaging of this file. Please review the following information
**    to ensure the GNU Lesser General Public License requirements
**    will be met: https://www.gnu.org/licenses/lgpl.html
**
**/

#pragma once

#include <ht_platform.h>
#include <map>

namespace Hatchit
{
	namespace Runtime
	{
		enum class Key
		{
			A, B, C, D, E, F, G, H, I,
			J, K, L, M, N, O, P, Q, R,
			S, T, U, V, W, X, Y, Z, N0,
			N1, N2, N3, N4, N5, N6, N7, N8,
			N9, F1, F2, F3, F4, F5, F6, F7, F8,
			F9, F10, F11, F12, Space, Ctrl, LShift,
			RShift, Left, Right, Up, Down, Backspace, Enter
		};

		class HT_API Keyboard
		{
			typedef std::map<Key, bool> KeyState;
		public:
			Keyboard();

			~Keyboard();

			bool KeyPressed(Key k);
			bool KeyReleased(Key k);
			bool SingleKeyPress(Key k);
			void Update();

			void RegisterKey(Key k, bool state);
		private:
			KeyState m_current;
			KeyState m_previous;
		};

		
	}
}