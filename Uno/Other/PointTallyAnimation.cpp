//
// Created by Brandon Martin on 8/21/19.
//

#include "PointTallyAnimation.h"
#include "Uno/Forms/MatchForm.h"
#include "Uno/Match/MatchController.h"

using namespace cursen;

PointTallyAnimation::PointTallyAnimation() :
    winner(-1), current_player(0), points_won(0), point_accumulator(0)
{
    point_animation.setInfinite(true);
    point_animation.setVariableTime(false);
    point_animation.setFrameDuration(.1);
    point_animation.add([this]() {
        Player& player = matchForm->getMatch().getPlayer(current_player);
        if (player.getHandSize() > 0)
        {
            const Card& card = player.getHand().get(0);
            point_accumulator += Card::Score(card);
            player.getHand().remove(0);
            matchForm->getConsole().setMessage(winner_name + " won " + std::to_string(point_accumulator) + " points!");
            matchForm->updateHand(current_player);
            matchForm->getPlayerTile(current_player).setCardCount(player.getHandSize());
        }
        else
        {
            matchForm->getPlayerTile(current_player).unhighlight();
            ++current_player;
            if (current_player == winner) ++current_player;
            if (current_player == matchForm->getMatch().getNumPlayers())
            {
                point_animation.stop();
            }
            else
            {
                matchForm->getPlayerTile(current_player).highlight();
                matchForm->updateHand(current_player);
            }
        }
    });
    point_animation.onEnd([this]() {
        matchForm->getController()->handlePostPointTally(winner, points_won);
    });
}

void PointTallyAnimation::setForm(MatchForm* matchForm)
{
    this->matchForm = matchForm;
}


void PointTallyAnimation::run(int winner, int points_won)
{
    this->winner = winner;
    this->current_player = 0;
    this->point_accumulator = 0;
    this->points_won = points_won;
    this->winner_name = matchForm->getMatch().getPlayer(winner).getName();
    if (winner == current_player) current_player = 1;
    matchForm->updateHand(current_player);
    matchForm->getPlayerTile(current_player).highlight();
    point_animation.start(.2);
}
