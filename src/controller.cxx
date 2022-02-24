#include "controller.hxx"

Controller::Controller(int size)
        : Controller(size, size, ge211::Posn<int>(0, 0))
{ }

Controller::Controller(
        int width,
        int height,
        ge211::Posn<int> position)
        : model_(width, height),
          view_(model_),
          Position(position)
{ }

void
Controller::draw(ge211::Sprite_set& sprites)
{
    view_.draw(sprites, Position);
}



View::Dimensions
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

std::string
Controller::initial_window_title() const
{
    return view_.initial_window_title();
}

void
Controller::on_mouse_down(ge211::Mouse_button, ge211::Posn<int> position)
{
    model_.play_move(view_.screen_to_board(position));
}

void
Controller::on_mouse_move(ge211::Posn<int> position)
{
    Position = view_.screen_to_board(position);
}

