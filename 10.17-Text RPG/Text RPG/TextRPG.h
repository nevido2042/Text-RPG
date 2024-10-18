#pragma once
#include "info.h"

#define INPUT_ERROR -1

void CreateCharacter(INFO** _ppPlayer);
void SetSTAT(INFO* _pPlayer);
void SelectTask(INFO* _pPlayer);
int GetInput(int* _pInput);
void SelectDungeon(INFO* _pPlayer);
int InputCheck();
void Enter_Grassland(INFO* _pPlayer);
void FaceMonster(INFO* _pPlayer);
void StartBattle(INFO* _pPlayer, INFO* _pMonster);
void RenderBattleInfo(INFO* _pPlayer, INFO* _pMonster);
void LoadCharacter(INFO** _pPlayer);
void SaveCharacter(INFO* _pPlayer);
void Run_TextRPG();