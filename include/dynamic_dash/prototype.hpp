#pragma once

#include <string>
#include <vector>

namespace dynamic_dash {

enum class Screen {
    Loading,
    MainMenu,
    LevelSelect,
    Gameplay
};

struct LevelInfo {
    std::string id;
    std::string name;
    std::string difficulty;
    int order;
};

class Prototype {
public:
    Prototype();

    void finish_loading();
    void open_level_select();
    bool select_level(const std::string& level_id);
    void return_to_menu();

    Screen screen() const noexcept;
    const std::vector<LevelInfo>& levels() const noexcept;
    const LevelInfo* selected_level() const noexcept;

private:
    Screen screen_;
    std::vector<LevelInfo> levels_;
    std::string selected_level_id_;
};

} // namespace dynamic_dash
