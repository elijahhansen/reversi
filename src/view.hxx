#pragma once

#include "model.hxx"

#include <string>

class View
{
public:
    /// View dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// View positions will use `int` coordinates.
    using Position = ge211::Posn<int>;

    /// View rectangles will use `int` coordinates.
    using Rectangle = ge211::Rect<int>;

    /// Constructs a view that knows about the given model.
    explicit View(Model const&);

    // You will probably want to add arguments here so that the
    // controller can communicate UI state (such as a mouse or
    // cursor position):
    //Model const& model_;

    void draw(ge211::Sprite_set& set, Position mouse);

    Dimensions initial_window_dimensions() const;

    std::string initial_window_title() const;

    View :: Position
    board_to_screen (
            Model :: Position logical )
    const ;

    Model :: Position
    screen_to_board (
            View :: Position physical )
    const ;

    void
    add_player_sprite_ (
            ge211 :: Sprite_set & sprites ,
            Player which ,
            ge211 :: Posn <int > physical ,
            int z_layer )
    const ;

private:
    Model const& model_;


    ge211::Circle_sprite const light_sprite;
    ge211::Circle_sprite const dark_sprite;
    ge211::Rectangle_sprite const grid_sprite;
    //ge211::Circle_sprite const viable_move;
    //ge211::Rectangle_sprite const board_sprite;

};



