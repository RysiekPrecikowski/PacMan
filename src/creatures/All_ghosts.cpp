//
// Created by rprec on 31.05.2021.
//

#include "All_ghosts.h"

using namespace sf;

All_ghosts::All_ghosts(RenderWindow &window, Labirynth *labirynth) : labirynth(labirynth) {
    ghosts[Blinky] = new Ghost(*labirynth->starting_positions[blinky], window, labirynth);
    ghosts[Blinky]->console = new Console("Blinky");
    ghosts[Blinky]->setGoesThroughFake(true);
    ghosts[Blinky]->scatter_mode_target = Vector2i (Labirynth::size_x -1, 0);
    ghosts[Blinky]->change_mode(scatter);

    ghosts[Pinky]  = new Ghost(*labirynth->starting_positions[pinky], window, labirynth);
    ghosts[Pinky]->console = new Console("Pinky");
    ghosts[Pinky]->setGoesThroughFake(true);
    ghosts[Pinky]->scatter_mode_target = Vector2i (0, 0);
    ghosts[Pinky]->change_mode(scatter);

    ghosts[Inky]   = new Ghost(*labirynth->starting_positions[inky], window, labirynth);
    ghosts[Inky]->console = new Console("Inky");
    ghosts[Inky]->setGoesThroughFake(false);
    ghosts[Inky]->scatter_mode_target = Vector2i (Labirynth::size_x -1, Labirynth::size_y-1);
    ghosts[Inky]->change_mode(scatter);

    ghosts[Clyde]  = new Ghost(*labirynth->starting_positions[clyde], window, labirynth);
    ghosts[Clyde]->console = new Console("Clyde");
    ghosts[Clyde]->setGoesThroughFake(false);
    ghosts[Clyde]->scatter_mode_target = Vector2i (0, Labirynth::size_y-1);
    ghosts[Clyde]->change_mode(scatter);
}

sf::Vector2i get_target_ahead_pac_man(PacMan *pacMan, int tiles){
    Vector2i target = pacMan->tile_position;

    if (pacMan->get_directions()->empty()){
        return target;
    }

    switch (pacMan->get_directions()->front()) {
        case up:
            target += Vector2i (-tiles, -tiles); // bug in original game
            break;
        case down:
            target += Vector2i (0, tiles);
            break;
        case left:
            target += Vector2i (-tiles, 0);
            break;
        case right:
            target += Vector2i (tiles, 0);
            break;
    }
    return target;
}

void All_ghosts::move_ghosts(PacMan *PacMan) {
    if (ghosts[Blinky]->time_to_move()) {
        ghosts[Blinky]->scaleDelay((1 - ( 1-(float)labirynth->food_in_maze/(float)labirynth->starting_food_in_maze)/2));
        ghosts[Blinky]->next_move(PacMan->tile_position);
        ghosts[Blinky]->actualize_mode();
        ghosts[Blinky]->move();
    }

    if (ghosts[Pinky]->time_to_move()) {
        ghosts[Pinky]->next_move(get_target_ahead_pac_man(PacMan, 4));
        ghosts[Pinky]->actualize_mode();
        ghosts[Pinky]->move();
    }

    if (ghosts[Inky]->time_to_move()) {
        if (PacMan->get_food_eaten() >= 30)
            ghosts[Inky]->setGoesThroughFake(true);


        Vector2i Inkys_target = get_target_ahead_pac_man(PacMan, 2);
        Vector2i Blinkys_vector = Inkys_target - ghosts[Blinky]->target;
        Inkys_target += Blinkys_vector;

        ghosts[Inky]->next_move(Inkys_target);
        ghosts[Inky]->actualize_mode();
        ghosts[Inky]->move();
    }

    if (ghosts[Clyde]->time_to_move()) {
        if ((1 - (float)labirynth->food_in_maze / (float)labirynth->starting_food_in_maze) >= 1.f/3.f)
            ghosts[Clyde]->setGoesThroughFake(true);

        int Clyde_distance = Ghost::get_distance(PacMan->tile_position.x, PacMan->tile_position.y,
                                                 ghosts[Clyde]->tile_position);
        Vector2i Clyde_target;

        if (Clyde_distance >= 8 * 8) {
            Clyde_target = PacMan->tile_position;
        } else {
            Clyde_target = ghosts[Clyde]->scatter_mode_target;
        }

        ghosts[Clyde]->next_move(Clyde_target);
        ghosts[Clyde]->actualize_mode();
        ghosts[Clyde]->move();
    }
}
