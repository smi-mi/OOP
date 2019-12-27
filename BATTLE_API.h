#ifndef BATTLE_API_H
#define BATTLE_API_H

#ifdef BATTLE_EXPORTS
#define BATTLE_API __declspec(dllexport)
#else
#define BATTLE_API __declspec(dllimport)
#endif

#endif