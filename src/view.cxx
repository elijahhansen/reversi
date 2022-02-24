#include "view.hxx"

// Convenient type aliases:
using Color = ge211::Color;
using Sprite_set = ge211::Sprite_set;

// You can change this or even determine it some other way:
static int const grid_size = 36;

static Color const light_color {255,255,255};
static Color const dark_color {0,0,0};
static Color const board_color {0,128,0};

View::View(Model const& model)
        : model_(model),
        light_sprite((grid_size)/2 -5, light_color),
        dark_sprite((grid_size)/2 -5, dark_color),
        grid_sprite({grid_size - 5, grid_size - 5}, board_color)

        { }

void View::draw(Sprite_set& set, Position mouse)
{
    add_player_sprite_(set, Player::dark, mouse)

    if (model_.find_move(mouse) != nullptr) {
        //if hovering over , do this...


      }
    for (Position p : model_.board()) {
        set.add_sprite(grid_sprite, board_to_screen({p}), 0);
        if (model_.find_move(p) != nullptr) {
            add_player_sprite_(set, model_.turn(), mouse, 10);

            if (model_[p] == Player::dark) {
                //set.add_sprite(dark_sprite, mouse, 20);
                add_player_sprite_(set, Player::dark, mouse,
                                   10);
            }
            if (model_[p] == Player::light) {
                //set.add_sprite(light_sprite, mouse, 20);
                add_player_sprite_(set, Player::light, mouse, 10);
            }
        }
    }



       // if (model_.find_move(p) != nullptr) {
       //     add_player_sprite_(set, model_.turn(), mouse, 10);

       // }



    //}

}


View::Dimensions
View::initial_window_dimensions() const
{
    // You can change this if you want:
    return grid_size * model_.board().dimensions();
}

std::string
View::initial_window_title() const
{
    // You can change this if you want:
    return "Reversi";
}

View::Position
View::board_to_screen(Model::Position logical) const
{
    return View::Position(logical.x * grid_size, logical.y *grid_size);
}

Model::Position
View::screen_to_board(View::Position physical) const
{
    return Model::Position(physical.x / grid_size, physical.y / grid_size);
}

void
View::add_player_sprite_(
        Sprite_set& sprites,
        Player which,
        ge211::Posn<int> physical,
        int z_layer) const
{
    if(which == Player::light)
    {
        sprites.add_sprite(light_sprite, physical, z_layer);
    }
    if(which == Player::dark)
    {
        sprites.add_sprite(dark_sprite, physical, z_layer);
    }


}

