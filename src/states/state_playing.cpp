//
// Created by rprec on 30.05.2021.
//

#include "state_playing.h"

using namespace sf;

void State_playing::init() {
    console = new Console("State playing");

    resources.load();
    labirynth = new Labirynth(*window);
    pacMan = new PacMan(*window, labirynth);
    ghosts = new All_ghosts(*window, labirynth);

    resources.point->setScale(resources.get_scale(*window, resources.point_texture));
    resources.PacMan->setScale(resources.get_scale(*window, resources.PacMan_texture));
    resources.tile->setScale(resources.get_scale(*window, resources.tile_texture));

    for (auto p:resources.ghosts){
        p.second->setScale(resources.get_scale(*window, resources.ghosts_textures[p.first]));
    }

    console->write("Initialized");
}

void State_playing::move_creature(Moving* creature){
    Directions direction = creature->get_directions()->empty() ? NONE : creature->get_directions()->front();

    if (creature->can_move(direction)) {
        creature->move();
    }
    else {
//        console->write("STOP");
        creature->stop();
    }



    if (labirynth->is_crossing(creature->tile_position)){
        if (creature->get_directions()->size() > 1) {
            if (creature->can_move(creature->get_directions()->back())) {
                creature->stop();

            }
        }
    }


}

void State_playing::loop() {
    ghosts->move_ghosts(pacMan);

    if (pacMan->time_to_move()) {
        move_creature(pacMan);
        pacMan->eat_food();
    }

    for (auto p : ghosts->ghosts){
        if (p.second->tile_position == pacMan->tile_position){
            console->write("OOPSIE");
            pacMan->teleport(15, 13);
        }
    }
}


void State_playing::render() {
    for(int i = 0 ; i < Labirynth::size_x; i++){
        for(int j = 0 ; j < Labirynth::size_y ; j++) {
            if (labirynth->tiles[i][j]->type == tiles_type::block) {
                resources.tile->setPosition(labirynth->tiles[i][j]->screen_position);

                window->draw(*resources.tile);
            } else {
                Sprite xd = Sprite(resources.tile_texture);
                xd.setPosition(labirynth->tiles[i][j]->screen_position);
                xd.setScale(resources.get_scale(*window, resources.tile_texture));

                if (labirynth->tiles[i][j]->type == tiles_type::crossing) {
                    xd.setColor(Color::Green);
                    window->draw(xd);
                } else if (labirynth->tiles[i][j]->type == tiles_type::fake_block){
                    xd.setColor(Color::Cyan);
                    window->draw(xd);
                } else if (labirynth->tiles[i][j]->type == tiles_type::none){
//                    xd.setColor(Color::Cyan);
//                    window->draw(xd);
                }

                if (labirynth->tiles[i][j]->point == point){
                    resources.point->setPosition(labirynth->tiles[i][j]->screen_position);
                    window->draw(*resources.point);
                }
            }
        }
    }

    for (auto p : resources.ghosts){
        auto ghost_sprite = p.second;
        auto ghost = p.first;

        ghost_sprite->setPosition(ghosts->ghosts[ghost]->screen_position);
        window->draw(*ghost_sprite);
    }

    resources.PacMan->setPosition(pacMan->screen_position);
    window->draw(*resources.PacMan);

}


void State_playing::keyPressed(int code) {
    switch (code) {
        case sf::Keyboard::Up:
//            check_direction(pacMan, Directions::up);
            pacMan->enqueueDirection(Directions::up);
            break;
        case sf::Keyboard::Down:
//            check_direction(pacMan, Directions::down);
            pacMan->enqueueDirection(Directions::down);
            break;
        case sf::Keyboard::Right:
//            check_direction(pacMan, Directions::right);
            pacMan->enqueueDirection(Directions::right);
            break;
        case sf::Keyboard::Left:
//            check_direction(pacMan, Directions::left);
            pacMan->enqueueDirection(Directions::left);
            break;
    }
}

void State_playing::keyReleased(int code) {

}
