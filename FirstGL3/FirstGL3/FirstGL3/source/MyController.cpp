#include "MyController.hpp"
#include "MyView.hpp"
#include <tygra/Window.hpp>
#include <iostream>

MyController::MyController()
{
    /*
     * Tutorial: Create an instance of MyView (our class to draw with OpenGL).
     */

	view_ = new MyView();
}

MyController::
~MyController()
{
    delete view_;
}

void MyController::windowControlWillStart(tygra::Window * window)
{
    /*
     * Tutorial: Assign our view object to be used by the window and perform
     *           other initialisation work now that the window exists.
     */

    window->setView(view_);
    window->setTitle("3D Graphics Programming :: FirstGL3");
}

void MyController::windowControlDidStop(tygra::Window * window)
{
    window->setView(nullptr);
}

void MyController::windowControlMouseMoved(tygra::Window * window,
                                           int x,
                                           int y)
{
}

void MyController::windowControlMouseButtonChanged(tygra::Window * window,
                                                   int button_index,
                                                   bool down)
{
}


void MyController::windowControlMouseWheelMoved(tygra::Window * window,
                                                int position)
{
}

void MyController::windowControlKeyboardChanged(tygra::Window * window,
                                                int key_index,
                                                bool down)
{
    /*
     * Tutorial: We can use this method to respond to keyboard presses.
     */

    if (down == false) {
        return;
    }

    switch (key_index) {
    case tygra::kWindowKeyF5:
        std::cout << "Reloading shaders not usually implemented" << std::endl;
        break;
    }
}

void MyController::windowControlGamepadAxisMoved(tygra::Window * window,
                                                 int gamepad_index,
                                                 int axis_index,
                                                 float pos)
{
}

void MyController::windowControlGamepadButtonChanged(tygra::Window * window,
                                                     int gamepad_index,
                                                     int button_index,
                                                     bool down)
{
}
