//
// Created by Brandon Martin on 5/22/19.
//

#include <Cursen/Tools/StopWatch.h>
#include "Cursen/Drawing/CursesManager.h"
#include "LobbyGlowBorder.h"

using namespace cursen;

LobbyGlowBorder::LobbyGlowBorder() :
        TextComponent(Vect2(0,0), Vect2(70, 32)), animation(1)
{
    reference.resize(Vect2(70,32));
    colorFlag = false;
}


void LobbyGlowBorder::initialize()
{

    chtype UL = ACS_ULCORNER;
    chtype UR = ACS_URCORNER;
    chtype HL = ACS_HLINE;
    chtype VL = ACS_VLINE;
    chtype LT = ACS_LTEE;
    chtype RT = ACS_RTEE;
    chtype LL = ACS_LLCORNER;
    chtype LR = ACS_LRCORNER;
    chtype X = Content::TRANSPARENT;

    /* Cache the pair values */
    blue_pair = CursesManager::GetColorPair(ColorPair(Color::BLUE));
    red_pair = CursesManager::GetColorPair(ColorPair(Color::RED));
    green_pair = CursesManager::GetColorPair(ColorPair(Color::GREEN));
    yellow_pair = CursesManager::GetColorPair(ColorPair(Color::YELLOW));
    white_pair = CursesManager::GetColorPair(ColorPair(Color::WHITE));

    /* Create a table for fast lookups (no ifs) */
    COLOR_LUT[0] = blue_pair;
    COLOR_LUT[1] = red_pair;
    COLOR_LUT[2] = green_pair;
    COLOR_LUT[3] = yellow_pair;
    COLOR_LUT[4] = CursesManager::GetColorPair(ColorPair(Color::PURPLE));
    COLOR_LUT[5] = CursesManager::GetColorPair(ColorPair(Color::ORANGE));

    Content& content = getContent();
    content[0][0] = UL | white_pair;
    for (int i = 1; i < 69; i++) content[0][i] = HL | white_pair;
    content[0][69] = UR | white_pair;

    content[1][0] = VL | white_pair;
    for (int i = 1; i < 69; i++) content[1][i] = X;
    content[1][69] = VL | white_pair;

    content[2][0] = VL | white_pair;
    for (int i = 1; i < 69; i++) content[2][i] = X;
    content[2][69] = VL | white_pair;

    content[3][0] = VL | white_pair;
    for (int i = 1; i < 69; i++) content[3][i] = X;
    content[3][69] = VL | white_pair;

    content[4][0] = LT | white_pair;
    for (int i = 1; i < 69; i++) content[4][i] = HL | white_pair;
    content[4][69] = RT | white_pair;

    content[5][0] = VL | white_pair;
    for (int i = 1; i < 69; i++) content[5][i] = X;
    content[5][69] = VL | white_pair;

    content[6][0] = LT | white_pair;
    for (int i = 1; i < 69; i++) content[6][i] = HL | white_pair;
    content[6][69] = RT | white_pair;

    content[7][0] = VL | white_pair;
    for (int i = 1; i < 17; i++) content[7][i] = X;
    content[7][17] = UL | white_pair;
    for (int i = 18; i < 52; i++) content[7][i] = HL | white_pair;
    content[7][52] = UR | white_pair;
    for (int i = 53; i < 69; i++) content[7][i] = X;
    content[7][69] = VL | white_pair;

    content[8][0] = VL | white_pair;
    for (int i = 1; i < 17; i++) content[8][i] = X;
    content[8][17] = VL | white_pair;
    for (int i = 18; i < 52; i++) content[8][i] = X;
    content[8][52] = VL | white_pair;
    for (int i = 53; i < 69; i++) content[8][i] = X;
    content[8][69] = VL | white_pair;

    content[9][0] = VL | white_pair;
    for (int i = 1; i < 17; i++) content[9][i] = X;
    content[9][17] = VL | white_pair;
    for (int i = 18; i < 52; i++) content[9][i] = X;
    content[9][52] = VL | white_pair;
    for (int i = 53; i < 69; i++) content[9][i] = X;
    content[9][69] = VL | white_pair;

    content[10][0] = VL | white_pair;
    for (int i = 1; i < 17; i++) content[10][i] = X;
    content[10][17] = VL | white_pair;
    for (int i = 18; i < 52; i++) content[10][i] = X;
    content[10][52] = VL | white_pair;
    for (int i = 53; i < 69; i++) content[10][i] = X;
    content[10][69] = VL | white_pair;

    content[11][0] = VL | white_pair;
    for (int i = 1; i < 17; i++) content[11][i] = X;
    content[11][17] = VL | white_pair;
    for (int i = 18; i < 52; i++) content[11][i] = X;
    content[11][52] = VL | white_pair;
    for (int i = 53; i < 69; i++) content[11][i] = X;
    content[11][69] = VL | white_pair;

    content[12][0] = VL | white_pair;
    for (int i = 1; i < 17; i++) content[12][i] = X;
    content[12][17] = LT | white_pair;
    for (int i = 18; i < 52; i++) content[12][i] = HL | white_pair;
    content[12][52] = RT | white_pair;
    for (int i = 53; i < 69; i++) content[12][i] = X;
    content[12][69] = VL | white_pair;

    content[13][0] = VL | white_pair;
    for (int i = 1; i < 17; i++) content[13][i] = X;
    content[13][17] = VL | white_pair;
    for (int i = 18; i < 52; i++) content[13][i] = X;
    content[13][52] = VL | white_pair;
    for (int i = 53; i < 69; i++) content[13][i] = X;
    content[13][69] = VL | white_pair;

    content[14][0] = VL | white_pair;
    for (int i = 1; i < 17; i++) content[14][i] = X;
    content[14][17] = LT | white_pair;
    for (int i = 18; i < 52; i++) content[14][i] = HL | white_pair;
    content[14][52] = RT | white_pair;
    for (int i = 53; i < 69; i++) content[14][i] = X;
    content[14][69] = VL | white_pair;

    content[15][0] = LT | white_pair;
    for (int i = 1; i < 17; i++) content[15][i] = HL | white_pair;
    content[15][17] = RT | white_pair;
    for (int i = 18; i < 52; i++) content[15][i] = X;
    content[15][52] = LT | white_pair;
    for (int i = 53; i < 69; i++) content[15][i] = HL | white_pair;
    content[15][69] = RT | white_pair;

    content[16][0] = VL | white_pair;
    for (int i = 1; i < 17; i++) content[16][i] = X;
    content[16][17] = VL | white_pair;
    for (int i = 18; i < 52; i++) content[16][i] = X;
    content[16][52] = VL | white_pair;
    for (int i = 53; i < 69; i++) content[16][i] = X;
    content[16][69] = VL | white_pair;

    content[17][0] = VL | white_pair;
    for (int i = 1; i < 17; i++) content[17][i] = X;
    content[17][17] = VL | white_pair;
    for (int i = 18; i < 52; i++) content[17][i] = X;
    content[17][52] = VL | white_pair;
    for (int i = 53; i < 69; i++) content[17][i] = X;
    content[17][69] = VL | white_pair;

    content[18][0] = VL | white_pair;
    for (int i = 1; i < 17; i++) content[18][i] = X;
    content[18][17] = VL | white_pair;
    for (int i = 18; i < 52; i++) content[18][i] = X;
    content[18][52] = VL | white_pair;
    for (int i = 53; i < 69; i++) content[18][i] = X;
    content[18][69] = VL | white_pair;

    content[19][0] = VL | white_pair;
    for (int i = 1; i < 17; i++) content[19][i] = X;
    content[19][17] = VL | white_pair;
    for (int i = 18; i < 52; i++) content[19][i] = X;
    content[19][52] = VL | white_pair;
    for (int i = 53; i < 69; i++) content[19][i] = X;
    content[19][69] = VL | white_pair;

    content[20][0] = VL | white_pair;
    for (int i = 1; i < 17; i++) content[20][i] = X;
    content[20][17] = VL | white_pair;
    for (int i = 18; i < 52; i++) content[20][i] = X;
    content[20][52] = VL | white_pair;
    for (int i = 53; i < 69; i++) content[20][i] = X;
    content[20][69] = VL | white_pair;

    content[21][0] = VL | white_pair;
    for (int i = 1; i < 17; i++) content[21][i] = X;
    content[21][17] = VL | white_pair;
    for (int i = 18; i < 52; i++) content[21][i] = X;
    content[21][52] = VL | white_pair;
    for (int i = 53; i < 69; i++) content[21][i] = X;
    content[21][69] = VL | white_pair;

    content[22][0] = VL | white_pair;
    for (int i = 1; i < 17; i++) content[22][i] = X;
    content[22][17] = VL | white_pair;
    for (int i = 18; i < 52; i++) content[22][i] = X;
    content[22][52] = VL | white_pair;
    for (int i = 53; i < 69; i++) content[22][i] = X;
    content[22][69] = VL | white_pair;

    content[23][0] = VL | white_pair;
    for (int i = 1; i < 17; i++) content[23][i] = X;
    content[23][17] = VL | white_pair;
    for (int i = 18; i < 52; i++) content[23][i] = X;
    content[23][52] = VL | white_pair;
    for (int i = 53; i < 69; i++) content[23][i] = X;
    content[23][69] = VL | white_pair;

    content[24][0] = VL | white_pair;
    for (int i = 1; i < 17; i++) content[24][i] = X;
    content[24][17] = VL | white_pair;
    for (int i = 18; i < 52; i++) content[24][i] = X;
    content[24][52] = VL | white_pair;
    for (int i = 53; i < 69; i++) content[24][i] = X;
    content[24][69] = VL | white_pair;

    content[25][0] = VL | white_pair;
    for (int i = 1; i < 17; i++) content[25][i] = X;
    content[25][17] = VL | white_pair;
    for (int i = 18; i < 52; i++) content[25][i] = X;
    content[25][52] = VL | white_pair;
    for (int i = 53; i < 69; i++) content[25][i] = X;
    content[25][69] = VL | white_pair;

    content[26][0] = VL | white_pair;
    for (int i = 1; i < 17; i++) content[26][i] = X;
    content[26][17] = VL | white_pair;
    for (int i = 18; i < 52; i++) content[26][i] = X;
    content[26][52] = VL | white_pair;
    for (int i = 53; i < 69; i++) content[26][i] = X;
    content[26][69] = VL | white_pair;

    content[27][0] = VL | white_pair;
    for (int i = 1; i < 17; i++) content[27][i] = X;
    content[27][17] = LL | white_pair;
    for (int i = 18; i < 52; i++) content[27][i] = HL | white_pair;
    content[27][52] = LR | white_pair;
    for (int i = 53; i < 69; i++) content[27][i] = X;
    content[27][69] = VL | white_pair;

    content[28][0] = VL | white_pair;
    for (int i = 1; i < 69; i++) content[28][i] = X;
    content[28][69] = VL | white_pair;

    content[29][0] = VL | white_pair;
    for (int i = 1; i < 69; i++) content[29][i] = X;
    content[29][69] = VL | white_pair;

    content[30][0] = VL | white_pair;
    for (int i = 1; i < 69; i++) content[30][i] = X;
    content[30][69] = VL | white_pair;

    content[31][0] = LL | white_pair;
    for (int i = 1; i < 69; i++) content[31][i] = HL | white_pair;
    content[31][69] = LR | white_pair;

    reference[0][0] = UL;
    for (int i = 1; i < 69; i++) reference[0][i] = HL;
    reference[0][69] = UR;

    reference[1][0] = VL;
    for (int i = 1; i < 69; i++) reference[1][i] = X;
    reference[1][69] = VL;

    reference[2][0] = VL;
    for (int i = 1; i < 69; i++) reference[2][i] = X;
    reference[2][69] = VL;

    reference[3][0] = VL;
    for (int i = 1; i < 69; i++) reference[3][i] = X;
    reference[3][69] = VL;

    reference[4][0] = LT;
    for (int i = 1; i < 69; i++) reference[4][i] = HL;
    reference[4][69] = RT;

    reference[5][0] = VL;
    for (int i = 1; i < 69; i++) reference[5][i] = X;
    reference[5][69] = VL;

    reference[6][0] = LT;
    for (int i = 1; i < 69; i++) reference[6][i] = HL;
    reference[6][69] = RT;

    reference[7][0] = VL;
    for (int i = 1; i < 17; i++) reference[7][i] = X;
    reference[7][17] = UL;
    for (int i = 18; i < 52; i++) reference[7][i] = HL;
    reference[7][52] = UR;
    for (int i = 53; i < 69; i++) reference[7][i] = X;
    reference[7][69] = VL;

    reference[8][0] = VL;
    for (int i = 1; i < 17; i++) reference[8][i] = X;
    reference[8][17] = VL;
    for (int i = 18; i < 52; i++) reference[8][i] = X;
    reference[8][52] = VL;
    for (int i = 53; i < 69; i++) reference[8][i] = X;
    reference[8][69] = VL;

    reference[9][0] = VL;
    for (int i = 1; i < 17; i++) reference[9][i] = X;
    reference[9][17] = VL;
    for (int i = 18; i < 52; i++) reference[9][i] = X;
    reference[9][52] = VL;
    for (int i = 53; i < 69; i++) reference[9][i] = X;
    reference[9][69] = VL;

    reference[10][0] = VL;
    for (int i = 1; i < 17; i++) reference[10][i] = X;
    reference[10][17] = VL;
    for (int i = 18; i < 52; i++) reference[10][i] = X;
    reference[10][52] = VL;
    for (int i = 53; i < 69; i++) reference[10][i] = X;
    reference[10][69] = VL;

    reference[11][0] = VL;
    for (int i = 1; i < 17; i++) reference[11][i] = X;
    reference[11][17] = VL;
    for (int i = 18; i < 52; i++) reference[11][i] = X;
    reference[11][52] = VL;
    for (int i = 53; i < 69; i++) reference[11][i] = X;
    reference[11][69] = VL;

    reference[12][0] = VL;
    for (int i = 1; i < 17; i++) reference[12][i] = X;
    reference[12][17] = LT;
    for (int i = 18; i < 52; i++) reference[12][i] = HL;
    reference[12][52] = RT;
    for (int i = 53; i < 69; i++) reference[12][i] = X;
    reference[12][69] = VL;

    reference[13][0] = VL;
    for (int i = 1; i < 17; i++) reference[13][i] = X;
    reference[13][17] = VL;
    for (int i = 18; i < 52; i++) reference[13][i] = X;
    reference[13][52] = VL;
    for (int i = 53; i < 69; i++) reference[13][i] = X;
    reference[13][69] = VL;

    reference[14][0] = VL;
    for (int i = 1; i < 17; i++) reference[14][i] = X;
    reference[14][17] = LT;
    for (int i = 18; i < 52; i++) reference[14][i] = HL;
    reference[14][52] = RT;
    for (int i = 53; i < 69; i++) reference[14][i] = X;
    reference[14][69] = VL;

    reference[15][0] = LT;
    for (int i = 1; i < 17; i++) reference[15][i] = HL;
    reference[15][17] = RT;
    for (int i = 18; i < 52; i++) reference[15][i] = X;
    reference[15][52] = LT;
    for (int i = 53; i < 69; i++) reference[15][i] = HL;
    reference[15][69] = RT;

    reference[16][0] = VL;
    for (int i = 1; i < 17; i++) reference[16][i] = X;
    reference[16][17] = VL;
    for (int i = 18; i < 52; i++) reference[16][i] = X;
    reference[16][52] = VL;
    for (int i = 53; i < 69; i++) reference[16][i] = X;
    reference[16][69] = VL;

    reference[17][0] = VL;
    for (int i = 1; i < 17; i++) reference[17][i] = X;
    reference[17][17] = VL;
    for (int i = 18; i < 52; i++) reference[17][i] = X;
    reference[17][52] = VL;
    for (int i = 53; i < 69; i++) reference[17][i] = X;
    reference[17][69] = VL;

    reference[18][0] = VL;
    for (int i = 1; i < 17; i++) reference[18][i] = X;
    reference[18][17] = VL;
    for (int i = 18; i < 52; i++) reference[18][i] = X;
    reference[18][52] = VL;
    for (int i = 53; i < 69; i++) reference[18][i] = X;
    reference[18][69] = VL;

    reference[19][0] = VL;
    for (int i = 1; i < 17; i++) reference[19][i] = X;
    reference[19][17] = VL;
    for (int i = 18; i < 52; i++) reference[19][i] = X;
    reference[19][52] = VL;
    for (int i = 53; i < 69; i++) reference[19][i] = X;
    reference[19][69] = VL;

    reference[20][0] = VL;
    for (int i = 1; i < 17; i++) reference[20][i] = X;
    reference[20][17] = VL;
    for (int i = 18; i < 52; i++) reference[20][i] = X;
    reference[20][52] = VL;
    for (int i = 53; i < 69; i++) reference[20][i] = X;
    reference[20][69] = VL;

    reference[21][0] = VL;
    for (int i = 1; i < 17; i++) reference[21][i] = X;
    reference[21][17] = VL;
    for (int i = 18; i < 52; i++) reference[21][i] = X;
    reference[21][52] = VL;
    for (int i = 53; i < 69; i++) reference[21][i] = X;
    reference[21][69] = VL;

    reference[22][0] = VL;
    for (int i = 1; i < 17; i++) reference[22][i] = X;
    reference[22][17] = VL;
    for (int i = 18; i < 52; i++) reference[22][i] = X;
    reference[22][52] = VL;
    for (int i = 53; i < 69; i++) reference[22][i] = X;
    reference[22][69] = VL;

    reference[23][0] = VL;
    for (int i = 1; i < 17; i++) reference[23][i] = X;
    reference[23][17] = VL;
    for (int i = 18; i < 52; i++) reference[23][i] = X;
    reference[23][52] = VL;
    for (int i = 53; i < 69; i++) reference[23][i] = X;
    reference[23][69] = VL;

    reference[24][0] = VL;
    for (int i = 1; i < 17; i++) reference[24][i] = X;
    reference[24][17] = VL;
    for (int i = 18; i < 52; i++) reference[24][i] = X;
    reference[24][52] = VL;
    for (int i = 53; i < 69; i++) reference[24][i] = X;
    reference[24][69] = VL;

    reference[25][0] = VL;
    for (int i = 1; i < 17; i++) reference[25][i] = X;
    reference[25][17] = VL;
    for (int i = 18; i < 52; i++) reference[25][i] = X;
    reference[25][52] = VL;
    for (int i = 53; i < 69; i++) reference[25][i] = X;
    reference[25][69] = VL;

    reference[26][0] = VL;
    for (int i = 1; i < 17; i++) reference[26][i] = X;
    reference[26][17] = VL;
    for (int i = 18; i < 52; i++) reference[26][i] = X;
    reference[26][52] = VL;
    for (int i = 53; i < 69; i++) reference[26][i] = X;
    reference[26][69] = VL;

    reference[27][0] = VL;
    for (int i = 1; i < 17; i++) reference[27][i] = X;
    reference[27][17] = LL;
    for (int i = 18; i < 52; i++) reference[27][i] = HL;
    reference[27][52] = LR;
    for (int i = 53; i < 69; i++) reference[27][i] = X;
    reference[27][69] = VL;

    reference[28][0] = VL;
    for (int i = 1; i < 69; i++) reference[28][i] = X;
    reference[28][69] = VL;

    reference[29][0] = VL;
    for (int i = 1; i < 69; i++) reference[29][i] = X;
    reference[29][69] = VL;

    reference[30][0] = VL;
    for (int i = 1; i < 69; i++) reference[30][i] = X;
    reference[30][69] = VL;

    reference[31][0] = LL;
    for (int i = 1; i < 69; i++) reference[31][i] = HL;
    reference[31][69] = LR;

    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 70; j++) {
            reference[i][j] |= white_pair;
            //content[i][j] |= Color::WHITE;
        }
    }

    animation.add([&]() {
        invalidate();
    });
    animation.setFrameDuration(.01);
    animation.setVariableTime(false);
    validate();
}

void LobbyGlowBorder::render()
{
    Runner*& runners = generator.getRunners();
    Content& content = getContent();

    // Erase lines
    for (int j = 0; j < 4; ++j) {
        Runner& runner = runners[j];
        for (int i = 0; i < 20; ++i) {
            const Vect2& p = runner.get(i);
            content[p.y][p.x] = reference[p.y][p.x];
        }
    }

    generator.update();

    // Redraw
    for (int j = 0; j < 4; ++j) {
        Runner& runner = runners[j];
        const int colorNum = runner.getColor();
        const short pair = COLOR_LUT[colorNum];
        for (int i = 0; i < 20; ++i) {
            const Vect2& p = runner.get(i);
            chtype ref = reference[p.y][p.x];
            ref ^= white_pair;
            content[p.y][p.x] = ref | pair;
        }
    }
}

void LobbyGlowBorder::setEnabled(bool value)
{
    Component::setEnabled(value);
    Component::setHidden(!value);

    if (isEnabled()) {
        animation.start();
    }
    else
        {
        animation.stop();
        Runner*& runners = generator.getRunners();
        Content& content = getContent();
        for (int i = 0; i < 4; i++)
        {
            Runner& runner = runners[i];
            for (int j = 0; j < 20; ++j)
            {
                const Vect2& p = runner.get(i);
                content[p.y][p.x] = reference[p.y][p.x];
            }
        }

        generator.reset();
    }
}

bool LobbyGlowBorder::isEnabled() const
{
    return Component::isEnabled();
}
