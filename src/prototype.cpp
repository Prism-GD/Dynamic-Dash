#include "dynamic_dash/prototype.hpp"

namespace dynamic_dash {

Prototype::Prototype()
    : screen_(Screen::Loading),
      levels_{{"first-steps", "First Steps", "Easy", 1}} {}

void Prototype::finish_loading() {
    screen_ = Screen::MainMenu;
}

void Prototype::open_level_select() {
    if (screen_ == Screen::MainMenu) {
        screen_ = Screen::LevelSelect;
    }
}

bool Prototype::select_level(const std::string& level_id) {
    for (const auto& level : levels_) {
        if (level.id == level_id) {
            selected_level_id_ = level.id;
            screen_ = Screen::Gameplay;
            return true;
        }
    }
    return false;
}

void Prototype::return_to_menu() {
    if (screen_ == Screen::LevelSelect || screen_ == Screen::Gameplay) {
        screen_ = Screen::MainMenu;
    }
}

Screen Prototype::screen() const noexcept {
    return screen_;
}

const std::vector<LevelInfo>& Prototype::levels() const noexcept {
    return levels_;
}

const LevelInfo* Prototype::selected_level() const noexcept {
    for (const auto& level : levels_) {
        if (level.id == selected_level_id_) {
            return &level;
        }
    }
    return nullptr;
}

} // namespace dynamic_dash
