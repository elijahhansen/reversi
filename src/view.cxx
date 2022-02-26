#include "view.hxx"

// Convenient type aliases:
using Color = ge211::Color;
using Sprite_set = ge211::Sprite_set;

// You can change this or even determine it some other way:
static int const grid_size = 36;

static ge211::Color const light_color {255,255,255};
static ge211::Color const dark_color {0,0,0};
static ge211::Color const board_color {0,128,0};
static ge211::Color const red_color {128,0,0};
static ge211::Color const gray_color {128,128,128};


View::View(Model const& model)
        : model_(model),
          light_sprite((grid_size)/2 -5, light_color),
          dark_sprite((grid_size)/2 -5, dark_color),
          grid_sprite({grid_size - 5 , grid_size - 5}, board_color),
          viable_move({grid_size - 5, grid_size - 5}, red_color),
          gray_sprite((grid_size)/2 -5, gray_color),
          back_drop({grid_size * model_.board().dimensions().width, grid_size *
        model_.board().dimensions().height+ 100}, gray_color)
          //board_sprite(initial_window_dimensions(), board_color)

//

{ }

void View::draw(Sprite_set& set)
{
    for (int i = 0; i< model_.board().dimensions().width; i++)
    {
        for (int j = 0; j< model_.board().dimensions().height; j++)
        {
            set.add_sprite(back_drop,{0,0}, 0);
            add_player_sprite_(set, model_.turn(),{(grid_size * model_.board
            ().dimensions().width)/2 -20,
                                                   grid_size *model_.board()
                                                   .dimensions().height+
                                                   30}, 10);
            set.add_sprite(grid_sprite, board_to_screen({i,j}), 5);
            if(model_[{i,j}] == Player::dark)
            {
                add_player_sprite_(set, Player::dark, board_to_screen({i,j}),
                                   10);
            }
            if(model_[{i,j}] == Player::light)
            {
                add_player_sprite_(set, Player::light, board_to_screen({i,j})
                                   , 10);
            }
            if (model_.find_move({i,j}) != nullptr)
            {
                set.add_sprite(viable_move, board_to_screen({i,j}), 10);
            }
            if (model_.is_game_over())
            {

            }
        }
    }

        if (model_.is_game_over())
        {
            if (model_.winner() == Player::light)
            {
                for (Position pos: model_.board())
                {
                    if (model_[pos] == Player::dark)
                    {
                        set.add_sprite(gray_sprite, board_to_screen(pos), 20);
                    }
                }
            }
            if (model_.winner() == Player::dark)
            {
                for (Position pos: model_.board())
                {
                    if (model_[pos] == Player::light)
                    {
                        set.add_sprite(gray_sprite, board_to_screen(pos), 20);
                    }
                }
            }
        }

}

View::Dimensions
View::initial_window_dimensions() const
{
    // You can change this if you want:
    return {grid_size * model_.board().dimensions().width, grid_size *
    model_.board().dimensions().height+ 100};
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
