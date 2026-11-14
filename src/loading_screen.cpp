#include "dynamic_dash/loading_screen.hpp"

#include <algorithm>
#include <utility>

namespace dynamic_dash {

LoadingScreen::LoadingScreen()
    : progress_(0.0f), status_("Preparing game..."), complete_(false) {}

void LoadingScreen::set_progress(float progress) {
    progress_ = std::max(0.0f, std::min(1.0f, progress));
    if (progress_ >= 1.0f) {
        finish();
    }
}

void LoadingScreen::set_status(std::string status) {
    status_ = std::move(status);
}

void LoadingScreen::finish() {
    progress_ = 1.0f;
    status_ = "Ready!";
    complete_ = true;
}

float LoadingScreen::progress() const noexcept {
    return progress_;
}

const std::string& LoadingScreen::status() const noexcept {
    return status_;
}

bool LoadingScreen::is_complete() const noexcept {
    return complete_;
}

} // namespace dynamic_dash
