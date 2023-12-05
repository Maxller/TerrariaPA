#pragma once
#include <SDL_events.h>
#include <vector>
#include <./input/controller.hpp>

enum ButtonStates {
    None,
    Pressed,
    Released
};

struct InputButton {
    int ActionId;
    int Code;
    ButtonStates State;
    InputButton() {}
    InputButton(int actionId, int code) : ActionId(actionId), Code(code), State(ButtonStates::None) {
    }
};

struct InputAxis {
    int ActionId;
    int NegativeCode;
    int PositiveCode;
    int Value;
    InputAxis() {}
    InputAxis(int actionId, int negativeCode, int positiveCode) : ActionId(actionId), NegativeCode(negativeCode),
                                                                  PositiveCode(positiveCode), Value(0) {
    }
};

class InputHandler {
public:
    void PreHandleEvent(){
        for (const auto &controller : _controllers){
            controller->ResetEvents();
        }
    }

    void HandleEvent(const SDL_Event *event){
        for (const auto &controller : _controllers){
            controller->HandleEvent(event);
        }
    }

    void Update(double elapsedSeconds){}

    void AddController(Controller *controller){
        _controllers.push_back(controller);
    }

private:
    std::vector<Controller *> _controllers;
};
