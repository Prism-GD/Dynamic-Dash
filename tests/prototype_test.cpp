#include "dynamic_dash/prototype.hpp"

#include <cassert>

int main() {
    dynamic_dash::Prototype game;

    assert(game.screen() == dynamic_dash::Screen::Loading);
    game.finish_loading();
    assert(game.screen() == dynamic_dash::Screen::MainMenu);

    game.open_level_select();
    assert(game.screen() == dynamic_dash::Screen::LevelSelect);
    assert(game.levels().size() == 1);
    assert(game.levels()[0].id == "first-steps");
    assert(game.levels()[0].name == "First Steps");

    assert(!game.select_level("missing-level"));
    assert(game.screen() == dynamic_dash::Screen::LevelSelect);

    assert(game.select_level("first-steps"));
    assert(game.screen() == dynamic_dash::Screen::Gameplay);
    assert(game.selected_level() != nullptr);
    assert(game.selected_level()->difficulty == "Easy");

    game.return_to_menu();
    assert(game.screen() == dynamic_dash::Screen::MainMenu);
    return 0;
}
