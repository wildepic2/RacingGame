//
// Created by wildepic on 01/07/2026.
//

#ifndef RACINGGAME_ERRORMANAGER_H
#define RACINGGAME_ERRORMANAGER_H

//Definition ErrorType
typedef enum ErrorType {
    UNDEFINED,
    INIT_ERROR,
} ErrorType;
extern ErrorType errorType;
extern char errorMessage[94];

void errorMenu();

#endif //RACINGGAME_ERRORMANAGER_H
