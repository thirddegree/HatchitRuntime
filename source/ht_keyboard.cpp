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

#include <ht_keyboard.h>

namespace Hatchit
{
	namespace Runtime
	{
		Keyboard::Keyboard()
		{
			
		}

		Keyboard::~Keyboard()
		{
			
		}

		bool Keyboard::KeyPressed(Key k)
		{
			return false;
		}

		bool Keyboard::KeyReleased(Key k)
		{
			return false;
		}

		bool Keyboard::SingleKeyPress(Key k)
		{
			return false;
		}

		void Keyboard::Update()
		{
			m_previous = m_current;
			m_current.clear();
		}

		void Keyboard::RegisterKey(Key k, bool state)
		{
			m_current[k] = state;
		}
	}
}