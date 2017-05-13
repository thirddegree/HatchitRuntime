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
#include <ht_application.h>

namespace Hatchit
{
	namespace Runtime
	{
		namespace WinRT
		{
			ref class Application sealed : Windows::ApplicationModel::Core::IFrameworkView
			{
			public:
				Application();

				// IFrameworkView methods.
				virtual void Initialize(Windows::ApplicationModel::Core::CoreApplicationView^ applicationView);
				virtual void SetWindow(Windows::UI::Core::CoreWindow^ window);
				virtual void Load(Platform::String^ entryPoint);
				virtual void Run();
				virtual void Uninitialize();

			protected:
				// Application lifecycle event handlers.
				void OnActivated(Windows::ApplicationModel::Core::CoreApplicationView^ applicationView, Windows::ApplicationModel::Activation::IActivatedEventArgs^ args);
				void OnSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ args);
				void OnResuming(Platform::Object^ sender, Platform::Object^ args);

				// Window event handlers.
				void OnWindowSizeChanged(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::WindowSizeChangedEventArgs^ args);
				void OnVisibilityChanged(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::VisibilityChangedEventArgs^ args);
				void OnWindowClosed(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::CoreWindowEventArgs^ args);
				void OnKeyDown(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::KeyEventArgs^ args);
				void OnKeyUp(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::KeyEventArgs^ args);

			private:
				std::unique_ptr<Runtime::Application> m_internal;
				bool								  m_closed;
				bool							      m_hidden;
			};

            ref class ApplicationSource sealed : Windows::ApplicationModel::Core::IFrameworkViewSource
            {
            public:
                virtual Windows::ApplicationModel::Core::IFrameworkView^ CreateView();
            };

            int HT_API InitWinRTApplication();
		}
	}
}