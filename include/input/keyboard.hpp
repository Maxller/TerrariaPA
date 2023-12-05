#pragma once
#include <./input/controller.hpp>
#include <./input/imputHandler.hpp>

#include <unordered_map>


class Keyboard : public Controller {
private:
    std::unordered_map<int, InputButton> buttonsMap;
    std::unordered_map<SDL_Keycode, int> keyToActionMap;
    std::unordered_map<int, InputAxis> axisMap;
    std::unordered_map<SDL_Keycode, int> keyToAxisActionMap;

    void HandleButton(const SDL_Event *event) {
    auto code = event->key.keysym.sym;
    auto action = keyToActionMap.find(code);
    if (action == keyToActionMap.cend()) {
        return;
    }

    if (event->key.state == SDL_PRESSED) {
        buttonsMap[action->second].State = Pressed;
        return;
    }
    buttonsMap[action->second].State = Released;
}

void HandleAxis(const SDL_Event *event) {

}

public:
    void AddButtonMap(InputButton &inputButton){
        buttonsMap[inputButton.ActionId] = inputButton;
        keyToActionMap[inputButton.Code] = inputButton.ActionId;
    }
    void AddAxisMap(InputAxis &inputAxis){
        axisMap[inputAxis.ActionId] = inputAxis;
        keyToAxisActionMap[inputAxis.PositiveCode] = inputAxis.ActionId;
        keyToAxisActionMap[inputAxis.NegativeCode] = inputAxis.ActionId;
    }

    void HandleEvent(const SDL_Event *event) override{
        if (event->type != SDL_KEYDOWN && event->type != SDL_KEYUP) {
            return;
        }
        HandleButton(event);
        HandleAxis(event);
    }
    bool GetButtonDown(int actionId) const override{
        auto inputButton = buttonsMap.find(actionId);
        if (inputButton == buttonsMap.cend()) {
            return false;
        }
        return inputButton->second.State == ButtonStates::Pressed;
    }
    bool GetButtonUp(int actionId) const override{
        auto inputButton = buttonsMap.find(actionId);
        if (inputButton == buttonsMap.cend()) {
            return false;
        }

        return inputButton->second.State == ButtonStates::Released;
    }
    bool GetButton(int actionId) const override{
        auto inputButton = buttonsMap.find(actionId);
        if (inputButton == buttonsMap.cend()) {
            return false;
        }

        return inputButton->second.State == ButtonStates::Released;
    }   
    double GetAxis(const int actionId) const override{
        auto inputAxis = axisMap.find(actionId);
        if (inputAxis == axisMap.cend()) {
            return 0;
        }

        return inputAxis->second.Value;
    }

    void ResetEvents() override{
        for (auto &item : buttonsMap) {
            item.second.State = ButtonStates::None;
        }

        for (auto &item : axisMap) {
            item.second.Value = 0;
        }
    }
};