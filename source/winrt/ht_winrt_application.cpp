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

#include <ht_winrt_application.h>
#include <ht_application.h>
#include <ht_keyboard.h>
#include <ht_debug.h>
#include <ht_string.h>

#include <ppltasks.h>

using namespace Hatchit;
using namespace Hatchit::Core;

using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::UI::Core;
using namespace Windows::Foundation;
using namespace Windows::System;

namespace
{
	Hatchit::Runtime::Key ConvertToKey(VirtualKey key)
	{
		using namespace Hatchit::Runtime;

		switch(key)
		{
		case VirtualKey::A:
			return Key::A;
		case VirtualKey::B:
			return Key::B;
		case VirtualKey::C:
			return Key::C;
		case VirtualKey::D:
			return Key::D;
		case VirtualKey::E:
			return Key::E;
		case VirtualKey::F:
			return Key::F;
		case VirtualKey::G:
			return Key::G;
		case VirtualKey::H:
			return Key::H;
		case VirtualKey::I:
			return Key::I;
		case VirtualKey::J:
			return Key::J;
		case VirtualKey::K:
			return Key::K;
		case VirtualKey::L:
			return Key::L;
		case VirtualKey::M:
			return Key::M;
		case VirtualKey::N:
			return Key::N;
		case VirtualKey::O:
			return Key::O;
		case VirtualKey::P:
			return Key::P;
		case VirtualKey::Q:
			return Key::Q;
		case VirtualKey::R:
			return Key::R;
		case VirtualKey::S:
			return Key::S;
		case VirtualKey::T:
			return Key::T;
		case VirtualKey::U:
			return Key::U;
		case VirtualKey::V:
			return Key::V;

		default:
			return Key::Z;
		}
	}
}

namespace Hatchit
{
	namespace Runtime
	{
		namespace WinRT
		{
            int InitWinRTApplication()
            {
                auto app = ref new ApplicationSource();
                CoreApplication::Run(app);

                return 0;
            }

            IFrameworkView^ ApplicationSource::CreateView()
            {
                return ref new Application();
            }

			Application::Application()
                : m_closed(false), m_hidden(false)
			{
				
			}

			void Application::Initialize(CoreApplicationView^ view)
			{
				// Register event handlers for app lifecycle. This example includes Activated, so that we
				// can make the CoreWindow active and start rendering on the window.
				view->Activated +=
					ref new TypedEventHandler<CoreApplicationView^, IActivatedEventArgs^>(this, &Application::OnActivated);

				CoreApplication::Suspending +=
					ref new EventHandler<SuspendingEventArgs^>(this, &Application::OnSuspending);

				CoreApplication::Resuming +=
					ref new EventHandler<Platform::Object^>(this, &Application::OnResuming);
			}

			void Application::SetWindow(CoreWindow^ window)
			{
				window->SizeChanged +=
					ref new TypedEventHandler<CoreWindow^, WindowSizeChangedEventArgs^>(this, &Application::OnWindowSizeChanged);

				window->VisibilityChanged +=
					ref new TypedEventHandler<CoreWindow^, VisibilityChangedEventArgs^>(this, &Application::OnVisibilityChanged);

				window->Closed +=
					ref new TypedEventHandler<CoreWindow^, CoreWindowEventArgs^>(this, &Application::OnWindowClosed);

				window->KeyDown +=
					ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &Application::OnKeyDown);

				window->KeyUp +=
					ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &Application::OnKeyUp);
			}

			void Application::Load(Platform::String^ entryPoint)
			{
				if (!m_internal)
					m_internal = std::make_unique<Runtime::Application>();
			}

			void Application::Run()
			{
				while(!m_closed)
				{
					if(!m_hidden)
					{
						CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);

						m_internal->Update();

						m_internal->Render();
					}
					else
					{
						CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessOneAndAllPending);
					}
				}
			}

			void Application::Uninitialize()
			{
				
			}


			//////////////////////////////////////////////////
			// Event Handlers
			//////////////////////////////////////////////////
		
		
			void Application::OnActivated(CoreApplicationView^ view, IActivatedEventArgs^ args)
			{
				// Activate window to enable ::Run()
				CoreWindow::GetForCurrentThread()->Activate();
			}

			void Application::OnSuspending(Platform::Object^ sender, SuspendingEventArgs^ args)
			{
				// Acquire deferral to perform application suspending operations.
				// (i.e) running any save state game operations
				// NOTE:
				// Deferal is not indefinite, only around 5 seconds or so until the app
				// will force close.

				SuspendingDeferral^ deferral = args->SuspendingOperation->GetDeferral();

				Concurrency::create_task([this, deferral]()
				{
					m_internal->Suspend();
					deferral->Complete();
				});
			}

			void Application::OnResuming(Platform::Object^ sender, Platform::Object^ resuming)
			{
				m_internal->Resume();
			}

			void Application::OnWindowClosed(CoreWindow^ window, CoreWindowEventArgs^ args)
			{
				m_closed = true;
			}

			void Application::OnWindowSizeChanged(CoreWindow^ sender, WindowSizeChangedEventArgs^ args)
			{
				
			}

			void Application::OnVisibilityChanged(CoreWindow^ sender, VisibilityChangedEventArgs^ args)
			{
				m_hidden = !args->Visible;
			}

			void Application::OnKeyDown(CoreWindow^ sender, KeyEventArgs^ args)
			{
                HT_DEBUG_PRINTF("Key Pressed: %s\n", wstring_to_string(args->VirtualKey.ToString()->Data()));
			}

			void Application::OnKeyUp(CoreWindow^ sender, KeyEventArgs^ args)
			{
                HT_DEBUG_PRINTF("Key Released: %s\n", wstring_to_string(args->VirtualKey.ToString()->Data()));
			}

		}
	}
}