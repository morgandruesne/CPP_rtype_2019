/*
** EPITECH PROJECT, 2019
** Babel_2019
** File description:
** R-type instruction
*/

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

typedef enum itype_s {
    M_WEL,
    M_TXT,
    M_UDPNC,
    M_PORT,
    M_START,
    M_END,
    M_LOOSE,
    M_WIN,

    M_GC,
    M_INS,
    M_UDPC,
    M_MOVE,
    M_SHOOT,
    M_DEAD,

    E_CREATE,
    E_MOVE,
    E_SHOOT,
    E_DESTROY,

    PM_MOVE,
    PM_DESTROY,

    PE_MOVE,

    M_ERR,
} itype_t;

typedef struct instruction_s {
    itype_t _type;

    int _code;
    int x;
    int y;
    char _txt[20];
} instruction_t;

#endif //INSTRUCTION_H
