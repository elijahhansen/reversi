#include "model.hxx"

using namespace ge211;

Model::Model(int size)
        : Model(size, size)
{ }

Model::Model(int width, int height)
        : board_({width, height})
{
    compute_next_moves_();
}

Model::Rectangle
Model::board() const
{
    return board_.all_positions();
}

Player
Model::operator[](Position pos) const
{
    return board_[pos];
}

const Move*
Model::find_move(Position pos) const
{
    auto i = next_moves_.find(pos);

    if (i == next_moves_.end()) {
        // Nothing was found, so return NULL (nullptr in C++)
        return nullptr;
    } else {
        // Dereferences the iterator to get the value then returns a pointer
        // to that value. This is safe as the pointer is to a value living
        // within the `next_moves_` structure.
        return &(*i);
    }
}

void
Model::play_move(Position pos)
{
    if (is_game_over()) {
        throw Client_logic_error("Model::play_move: game over");
    }

    const Move* movep = find_move(pos);
    if (movep == nullptr) { // check if there was no such move
        throw Client_logic_error("Model::play_move: no such move");
    }

    else
    {
        really_play_move_(*movep);

    }

    
}

//
// BELOW ARE HELPER FUNCTIONS
// Our tests will run on the public functions, not the helper functions
// However, these will be extremely useful in writing the above functions
//

Position_set
Model::find_flips_(Position current, Dimensions dir) const
{
    Position_set pset;
    for (;;)
    {
        current += dir;
        if (!board_.good_position(current) || board_[current] != other_player
        (turn_))
        {
            return pset;
        }
        else if (board_[current] == turn_)
        {
            return pset;

        }
        else
        {
            pset[current] = true;
        }
    }

}

Position_set
Model::evaluate_position_(Position pos) const
{
    Position_set pset;
    for ( Dimensions dir : board_.all_directions())
    {
        pset | find_flips_(pos, dir);
    }
    if (!pset.empty())
    {
        pset[pos] = true;
        return pset;
    }
    else
    {
        return pset;
    }

}

void
Model::compute_next_moves_()
{
    next_moves_.clear();
    for (Position pos : board_.center_positions())
    {
        if (board_[pos] != turn_ && board_[pos] != other_player(turn_))
        {
            next_moves_[pos] = {pos};
        }
        if (!next_moves_.empty())
        {
            return;
        }
    }
    for (Position p : board_.all_positions())
    {
        if(!evaluate_position_(p).empty())
        {
            next_moves_[p] = evaluate_position_(p);
        }
    }
}

bool
Model::advance_turn_()
{
    other_player(turn_);
    compute_next_moves_();
    if (!next_moves_.empty())
    {
        return true;
    }
    else
    {
        return false;
    }

}

void
Model::set_game_over_()
{
    turn_ = Player::neither;
    if (board_.count_player(Player::light) == board_.count_player(Player::dark))
    {
        winner_ = turn_;
    }
    else if (board_.count_player(Player::light) < board_.count_player(Player::dark))
    {
        winner_ = Player::dark;
    }
    else
    {
        winner_ = Player::light;
    }

}

void
Model::really_play_move_(Move move)
{
    for (Position p : move.second)
    {
         board_[p] = turn_;
    }
    bool a = advance_turn_();
    bool b = advance_turn_();
    if (!a && !b)
    {
        set_game_over_();
    }
}
