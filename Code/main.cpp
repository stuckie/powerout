#include "externs.h"
#include <windowsx.h>

/** The Windows Message Processor */
    LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        /** As Windows tends to fire a lot of messages at us, we need some way of dealing with them.
        *   This function does that, and the following switch block allows us to deal with the ones we want,
        *   and ignore the rest of the junk Windows likes to send us ;)                                   */

        switch (message)
        {
            case WM_CREATE:	                                //!< When the window is created, do this:
                loadBackground();
                break;

            case WM_SIZE:	                                //!< When the window is resized, do this:

                break;

            case WM_KEYDOWN:                                //!< When a key is pressed:
                keys[wParam]=true;                          //!< mark it true in the key array
                break;

            case WM_KEYUP:	                                //!< And ofcourse, when it's released:
                keys[wParam]=false;                         //!< mark it false.
                break;

            case WM_MOUSEMOVE:                              //!< When the mouse is moved:
                MousePos.x = GET_X_LPARAM (lParam);               //!< update the X co-ord
                MousePos.y = GET_Y_LPARAM (lParam);               //!< update the Y co-ord
                break;

			case WM_LBUTTONDOWN:
				MousePos.left = true;
				MousePos.x = GET_X_LPARAM(lParam); 
				MousePos.y = GET_Y_LPARAM(lParam); 
				break;

			case WM_LBUTTONUP:
				MousePos.left = false;
				MousePos.x = GET_X_LPARAM(lParam); 
				MousePos.y = GET_Y_LPARAM(lParam); 
				break;
		
			case WM_RBUTTONDOWN:
				MousePos.right = true;
				MousePos.x = GET_X_LPARAM(lParam); 
				MousePos.y = GET_Y_LPARAM(lParam); 
				break;
			
			case WM_RBUTTONUP:
				MousePos.right = false;
				MousePos.x = GET_X_LPARAM(lParam); 
				MousePos.y = GET_Y_LPARAM(lParam); 
				break;

            case WM_PAINT:	                                //!< When we get a PAINT call:
                break;

            case WM_DESTROY:                                //!< When the Window dies:
                PostQuitMessage(0);                         //!< Quit gracefully
                break;
        }

        return DefWindowProc (  hwnd,                       //!< Else, windows should know what to do with it
                                message,
                                wParam,
                                lParam);
    }

/** The ACTUAL Windows Entry Point */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int nCmdShow)
{
	MSG	msg;		                                    //!< Pointer to the messages Windows likes to throw at us.

	RegisterMyWindow(hInstance);	                    //!< Register the window to THIS instance.

	if (!InitialiseMyWindow(hInstance, nCmdShow))	    //!< If there's been a bug creating the window..
		return FALSE;					                //!< PANIC!!!

	setBuffers();

	while (TRUE)					                    //!< And carry on :)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))       //!< has Windows got a message for us?
		{
			if (msg.message == WM_QUIT)		            //!< if it's quit,
				break;			                        //!< just die..

			TranslateMessage(&msg);	                //!< Else, figure out what Windows wants
			DispatchMessage(&msg);		                //!< And fire it to our WNDPROC above to deal with.
		}
		else {
			BitBlt(backHDC, screenRect.left, screenRect.top, screenRect.right, screenRect.bottom, backgroundHDC, 0, 0, SRCCOPY);

			// 0 : init | 1 : intro | 2 : game | 3 : level win | 4 : level fail | 5 : credits
			switch (game_status) {
				case 0: {
					init_game();
					ballSetup();
					music_playing=0;
				}
				break;
				case 1: {
					game_intro();
					if (true == keys[VK_F2]) {
						gameSetup();
						music_playing = 0;
						game_status = 2;
					}
					else if (true == keys[VK_F3]) {
						music_playing = 0;
						game_status = 5;
					}
					else if (true == keys[VK_ESCAPE])
						PostMessage(ghwnd, WM_QUIT, 0, 0);

					if (true == paused)
						show_help();
				}
				break;
				case 2: {
					if (false == paused)
						game();

					if (true == paused)
						show_help();
				}
				break;
				case 3: {
					levelWin();
				}
				break;
				case 4: {
					levelFail();
				}
				break;
				case 5: {
					show_credits();

					if ((true == keys[VK_F4])
					|| (true == keys[VK_ESCAPE])
					|| (true == keys[VK_SPACE])) {
						music_playing = 0;
						game_status = 1;
					}
				}
			}

			if (true == keys[VK_F1])
				paused = true;

			if (true == paused && true == keys[VK_SPACE])
				paused = false;

			playMusic();
		}

		BitBlt(frontHDC, screenRect.left, screenRect.top, screenRect.right, screenRect.bottom, backHDC, 0, 0, SRCCOPY);
	}

	killGFX();

	return msg.wParam;	                                    //!< And tell windows the reason we died.. be it proper quit or an oops!
}
