//
// Created by Brandon Martin on 5/22/19.
//

#include "LobbyEffectGenerator.h"

void LobbyEffectGenerator::drawLine(char val, int x, int y, int length)
{
    for (int i = x; i < x+length; ++i) {
        maze[y][i] = val;
    }
}


LobbyEffectGenerator::LobbyEffectGenerator()
{
    maze = new char*[32];
    for (int i = 0; i < 32; i++) {
        maze[i] = new char[70];
        for (int j = 0; j < 70; j++) {
            maze[i][j] = '0';
        }
    }

    // row 0
    for (int i = 0; i < 70; i++) {
        maze[0][i] = '1';
    }

    maze[1][0] = '1'; maze[1][69] = '1';
    maze[2][0] = '1'; maze[2][69] = '1';
    maze[3][0] = '1'; maze[3][69] = '1';

    for (int i = 0; i < 70; i++) {
        maze[4][i] = '1';
    }

    maze[5][0] = '1'; maze[5][69] = '1';

    for (int i = 0; i < 70; i++) {
        maze[6][i] = '2';
    }
    maze[6][0] = '1'; maze[6][69] = '1';

    maze[7][0] = '1'; drawLine('1', 17, 7, 36); maze[7][69] = '1';

    maze[8][0] = '1'; maze[8][17] = '1'; maze[8][52] = '1'; maze[8][69] = '1';
    maze[9][0] = '1'; maze[9][17] = '1'; maze[9][52] = '1'; maze[9][69] = '1';
    maze[10][0] = '1'; maze[10][17] = '1'; maze[10][52] = '1'; maze[10][69] = '1';
    maze[11][0] = '1'; maze[11][17] = '1'; maze[11][52] = '1'; maze[11][69] = '1';

    maze[12][0] = '1'; drawLine('1', 17, 12, 36); maze[12][69] = '1';

    maze[13][0] = '1'; maze[13][17] = '1'; maze[13][52] = '1'; maze[13][69] = '1';

    maze[14][0] = '1'; drawLine('1', 17, 14, 36); maze[14][69] = '1';

    drawLine('1', 0, 15, 18); drawLine('1', 52, 15, 18);

    maze[16][0] = '1'; maze[16][17] = '1'; maze[16][52] = '1'; maze[16][69] = '1';
    maze[17][0] = '1'; maze[17][17] = '1'; maze[17][52] = '1'; maze[17][69] = '1';
    maze[18][0] = '1'; maze[18][17] = '1'; maze[18][52] = '1'; maze[18][69] = '1';
    maze[19][0] = '1'; maze[19][17] = '1'; maze[19][52] = '1'; maze[19][69] = '1';
    maze[20][0] = '1'; maze[20][17] = '1'; maze[20][52] = '1'; maze[20][69] = '1';
    maze[21][0] = '1'; maze[21][17] = '1'; maze[21][52] = '1'; maze[21][69] = '1';
    maze[22][0] = '1'; maze[22][17] = '1'; maze[22][52] = '1'; maze[22][69] = '1';
    maze[23][0] = '1'; maze[23][17] = '1'; maze[23][52] = '1'; maze[23][69] = '1';
    maze[24][0] = '1'; maze[24][17] = '1'; maze[24][52] = '1'; maze[24][69] = '1';
    maze[25][0] = '1'; maze[25][17] = '1'; maze[25][52] = '1'; maze[25][69] = '1';
    maze[26][0] = '1'; maze[26][17] = '1'; maze[26][52] = '1'; maze[26][69] = '1';

    maze[27][0] = '1'; drawLine('1', 17, 27, 36); maze[27][69] = '1';

    maze[28][0] = '1'; maze[28][69] = '1';
    maze[29][0] = '1'; maze[29][69] = '1';
    maze[30][0] = '1'; maze[30][69] = '1';

    for (int i = 0; i < 70; i++) maze[31][i] = '1';

    runners = new Runner[4];
    for (int i = 0; i < 4; i++)
    {
        runners[i].setColor(i);
    }


    reset();
    //runners.push_back(Runner(0,15));
    //runners.push_back(Runner(69,15));

}

void LobbyEffectGenerator::update()
{
    runners[0].update(maze);
    runners[1].update(maze);
    runners[2].update(maze);
    runners[3].update(maze);
}

Runner*& LobbyEffectGenerator::getRunners()
{
    return runners;
}

LobbyEffectGenerator::~LobbyEffectGenerator()
{
    for (int i = 0; i < 32; i++) {
        delete[] maze[i];
    }
    delete[] maze;
    delete[] runners;
}

void LobbyEffectGenerator::reset()
{
    runners[0].reset(0,0);
    runners[1].reset(69,0);
    runners[2].reset(0,31);
    runners[3].reset(69,31);
}
