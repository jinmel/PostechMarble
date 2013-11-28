#pragma once
#include <QDebug>   //for convinence

namespace BlockType {
    enum Type {
        Subject, Corner, Event, Friday
    };
}

namespace CornerType {
    enum Type {
        DORMITORY, THE61CALL, BREAKSEMESTER, PLURALMAJOR
    };
}

namespace FireFridayType {
    enum Type {
        TWODARI,SEOULJONGBIN,TONGZIP,CHAMPYO
    };
}

namespace SubjectType {
    enum Type {
        CSE, ME, MATH, EE, PHYS, BIO, CHEM, MSE
    };
}

namespace CharacterType {
    enum Type {
           NONE, LOL, GENIUS, HARD_WORKER, OUTSIDER, ALCOHOLIC
       };
}

namespace SceneType {
    enum Type {
        MAIN,LOGO,READY,INGAME
    };
}
