//
// Created by rprec on 30.05.2021.
//

#include "state_playing.h"

using namespace sf;

void State_playing::init() {
    console = new Console("State playing");

    resources.load(window);
    maze = new Maze(*window);
    pacMan = new PacMan(*window, maze);
    ghosts = new All_ghosts(*window, maze);


    console->write("Initialized");
}

void State_playing::move_creature(Moving* creature){
    Directions direction = creature->get_directions()->empty() ? NONE : creature->get_directions()->front();

    if (creature->can_move(direction)) {
        creature->move();
    }
    else {
        creature->stop();
    }

    if (maze->is_crossing(creature->tile_position)){
        if (creature->get_directions()->size() > 1) {
            if (creature->can_move(creature->get_directions()->back())) {
                creature->stop();
            }
        }
    }
}

void State_playing::reset_positions(){
    pacMan->teleport(*maze->starting_positions[pac_man]);

    ghosts->ghosts[Blinky]->teleport(*maze->starting_positions[blinky]);
    ghosts->ghosts[Pinky]->teleport(*maze->starting_positions[pinky]);
    ghosts->ghosts[Pinky]->escaped = false;
    ghosts->ghosts[Clyde]->teleport(*maze->starting_positions[clyde]);
    ghosts->ghosts[Clyde]->escaped = false;
    ghosts->ghosts[Inky]->teleport(*maze->starting_positions[inky]);
    ghosts->ghosts[Inky]->escaped = false;
}

void State_playing::check_collisions() {
    for (auto p : ghosts->ghosts){
        if (p.second->tile_position == pacMan->tile_position){
            if (p.second->is_frightened){

                p.second->teleport(*maze->starting_positions[inky]);
                p.second->escaped= false;
                p.second->end_frightened();

                pacMan->points += 200;
            } else {
                pacMan->points -= 500;
                reset_positions();
            }
        }
    }
}

Game_state::state State_playing::loop() {
    ghosts->move_ghosts(pacMan);

    if (pacMan->time_to_move()) {
        move_creature(pacMan);

        if(maze->tiles[pacMan->tile_position.x][pacMan->tile_position.y]->point == big_point){
            ghosts->frighten_ghosts();
        }

        pacMan->eat_food();
    }

    check_collisions();

    if (maze->food_in_maze == 0){
        pause();
        win= true;
    }

    if (pacMan->points < 0){
        pacMan->points = 0;
        pause();
        win= false;
        lost = true;
    }

    return running;
}

void State_playing::render_maze(){
    for(int i = 0 ; i < Maze::size_x; i++){
        for(int j = 0 ; j < Maze::size_y ; j++) {
            if (maze->tiles[i][j]->type == tiles_type::block) {
                resources.tile->setPosition(maze->tiles[i][j]->screen_position);

                window->draw(*resources.tile);
            } else {
                if (maze->tiles[i][j]->point == point){
                    resources.point->setPosition(maze->tiles[i][j]->screen_position);
                    window->draw(*resources.point);
                } else if (maze->tiles[i][j]->point == big_point){
                    resources.big_point->setPosition(maze->tiles[i][j]->screen_position);
                    window->draw(*resources.big_point);
                }
            }
        }
    }
}

void State_playing::render_creatures(){
    for (auto p : resources.ghosts){
        auto ghost_sprite = p.second;
        auto ghost = p.first;

        if(ghosts->ghosts[ghost]->is_frightened){
            resources.frightened_ghost->setPosition(ghosts->ghosts[ghost]->screen_position);
            window->draw(*resources.frightened_ghost);
        } else {

            ghost_sprite->setPosition(ghosts->ghosts[ghost]->screen_position);
            window->draw(*ghost_sprite);
        }

    }

    resources.PacMan->setPosition(pacMan->screen_position);
    window->draw(*resources.PacMan);
}

void State_playing::render_text(){
    sf::Text text;
    text.setFont(resources.font);
    std::string points_str = "Points "+ std::to_string(pacMan->points);
    text.setString(points_str);
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::White);
    window->draw(text);

    if (lost or win or paused){
        if (paused and not lost and not win)
            text.setString("PAUSED");
        else if (lost)
            text.setString("YOU LOST");
        else if (win)
            text.setString("YOU WON!");
        text.setCharacterSize(80);
        text.setFillColor(sf::Color::Red);
        text.setPosition(maze->tiles[2][5]->screen_position);
        window->draw(text);
    }
}

void State_playing::render() {
    render_maze();

    render_creatures();

    render_text();
}

void State_playing::keyPressed(int code) {
    switch (code) {
        case sf::Keyboard::Up:
            pacMan->enqueueDirection(Directions::up);
            break;
        case sf::Keyboard::Down:
            pacMan->enqueueDirection(Directions::down);
            break;
        case sf::Keyboard::Right:
            pacMan->enqueueDirection(Directions::right);
            break;
        case sf::Keyboard::Left:
            pacMan->enqueueDirection(Directions::left);
            break;

        case sf::Keyboard::P:
            if (paused) {
                resume();
            } else {
                pause();
            }
            break;
        default:
            break;
    }
}

void State_playing::keyReleased(int code) {

}

void State_playing::pause() {
    paused = true;
    pacMan->pause();

    for (auto p:ghosts->ghosts){
        p.second->pause();
    }

}

void State_playing::resume() {
    paused = false;
    pacMan->resume();

    for (auto p:ghosts->ghosts){
        p.second->resume();
    }
}
