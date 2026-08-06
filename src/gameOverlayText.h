//
// Created by wildepic on 30/07/2026.
//

#ifndef RACINGGAME_GAMEOVERLAYTEXT_H
#define RACINGGAME_GAMEOVERLAYTEXT_H
#include "raylib.h"

void overlayText(Vector2 *pos);
void timer();
void reconstructTime(int *minute , int *sec , int *ms , int time );

#endif //RACINGGAME_GAMEOVERLAYTEXT_H
