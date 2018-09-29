//
//  factories.cpp
//  EnTT Example
//
//  Created by Indi Kernick on 18/9/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "factories.hpp"

#include "comp/dir.hpp"
#include "comp/house.hpp"
#include "comp/ghost.hpp"
#include "comp/sprite.hpp"
#include "comp/target.hpp"
#include "comp/player.hpp"
#include "comp/position.hpp"
#include "comp/ghost_mode.hpp"
#include "comp/chase_target.hpp"
#include "comp/home_position.hpp"

Entity makeMaze(Registry &reg, const Sprite::Sheet &sheet) {
  const Entity e = reg.create();
  reg.assign<MazeSprite>(e, sheet.getIDfromName("maze"));
  return e;
}

Entity makePlayer(Registry &reg, const Sprite::Sheet &sheet) {
  const Entity e = reg.create();
  reg.assign<Player>(e);
  reg.assign<DesiredDir>(e, Grid::Dir::left);
  reg.assign<ActualDir>(e, Grid::Dir::left);
  reg.assign<Position>(e, Grid::Pos{9, 16});
  reg.assign<PlayerSprite>(e, sheet.getIDfromName("pacman 0"));
  return e;
}

namespace {

Entity makeGhost(Registry &reg, const Grid::Pos home, const Grid::Pos scatter) {
  const Entity e = reg.create();
  reg.assign<ChaseMode>(e);
  reg.assign<Position>(e, home);
  reg.assign<DesiredDir>(e);
  reg.assign<ActualDir>(e);
  reg.assign<Target>(e);
  reg.assign<Ghost>(e);
  reg.assign<LeaveHouse>(e);
  reg.assign<HomePosition>(e, home, scatter);
  return e;
}

}

Entity makeBlinky(Registry &reg, const Sprite::Sheet &sheet, const Entity player) {
  const Entity e = makeGhost(reg, {9, 8}, {18, 0});
  reg.assign<BlinkyChaseTarget>(e, player);
  reg.assign<GhostSprite>(e, sheet.getIDfromName("blinky 0"));
  return e;
}

Entity makePinky(Registry &reg, const Sprite::Sheet &sheet, const Entity player) {
  const Entity e = makeGhost(reg, {9, 10}, {0, 0});
  reg.assign<PinkyChaseTarget>(e, player);
  reg.assign<GhostSprite>(e, sheet.getIDfromName("pinky 0"));
  return e;
}

Entity makeInky(
  Registry &reg,
  const Sprite::Sheet &sheet,
  const Entity player,
  const Entity blinky
) {
  const Entity e = makeGhost(reg, {8, 10}, {18, 21});
  reg.assign<InkyChaseTarget>(e, player, blinky);
  reg.assign<GhostSprite>(e, sheet.getIDfromName("inky 0"));
  return e;
}

Entity makeClyde(Registry &reg, const Sprite::Sheet &sheet, const Entity player) {
  const Entity e = makeGhost(reg, {10, 10}, {0, 21});
  reg.assign<ClydeChaseTarget>(e, player);
  reg.assign<GhostSprite>(e, sheet.getIDfromName("clyde 0"));
  return e;
}