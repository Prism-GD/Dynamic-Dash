#pragma once

#include <string>

namespace dynamic_dash {

// State model for the game's first scene. A Cocos2d scene will render this
// model once the engine adapter is integrated.
class LoadingScreen {
public:
    LoadingScreen();

    void set_progress(float progress);
    void set_status(std::string status);
    void finish();

    float progress() const noexcept;
    const std::string& status() const noexcept;
    bool is_complete() const noexcept;

private:
    float progress_;
    std::string status_;
    bool complete_;
};

} // namespace dynamic_dash
