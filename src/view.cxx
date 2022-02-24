#include "view.hxx"

// Convenient type aliases:
using Color = ge211::Color;
using Sprite_set = ge211::Sprite_set;

// You can change this or even determine it some other way:
static int const grid_size = 36;

static ge211::Color const light_color {255,255,255};
static ge211::Color const dark_color {0,0,0};
static ge211::Color const board_color {0,0,0};

View::View(Model const& model)
        : model_(model),
        light_sprite((grid_size)/2 -1, light_color),
        dark_sprite((grid_size)/2 -1, dark_color),
        grid_sprite({grid_size, grid_size}, board_color),
        board_sprite(initial_window_dimensions(), board_color)

        //

{ }

void View::draw(Sprite_set& set, Position mouse)
{
    for (int i = 0; i< model_.board().dimensions().width)
    {
        for (int j = 0; j< model_.board().dimensions().height)
        {
            set.add_sprite(grid_sprite, board_to_screen({i,j}), 0);
        }
    }

    while (!model_.is_game_over())
    {

        if (model_.is_game_over())
        {

        }
        if (model_.find_move(screen_to_board(mouse)) != nullptr)
        {
            
        }
        if (model_.find_move(screen_to_board(mouse)) != nullptr)
        {
            add_player_sprite_(set,model_.turn(), screen_to_board(mouse), 0.5);
        }


    }
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

