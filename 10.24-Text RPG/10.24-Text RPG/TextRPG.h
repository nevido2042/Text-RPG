#pragma once
#include "info.h"

enum DUNGEON { Grassland = 1, Mountain, Cave };

//»©Áà¾ß ÇÒ °Í °°Àº ÇÔ¼ö
void TryAttack(CInfo* _pAttacker, CInfo* _pTarget);
int SelectItem(CInfo* _pPlayer, CInfo* _pMonster);

void BuyItem(CInfo* _pPlayer, CInfo* _pMerchant);
void SellItem(CInfo* _pPlayer, CInfo* _pMerchant);
//

void CreateCharacter(CInfo** _ppPlayer);
void SetSTAT(CInfo* _pPlayer);
void SelectTask(CInfo* _pPlayer);
int GetInput(int* _pInput);
void OpenShop(CInfo* _pPlayer, CInfo* _pMerchant);
void RenderShop(CInfo* _pPlayer, CInfo* _pMerchant);

void SelectDungeon(CInfo* _pPlayer);
int InputCheck();
int RollDice(int iValue);

void Enter_Dungeon(CInfo* _pPlayer, int _iValue = 2);
//void Enter_Grassland(CInfo* _pPlayer);
//void Enter_Mountain(CInfo* _pPlayer);
//void Enter_Cave(CInfo* _pPlayer);

void TriggerRandomEvent(CInfo* _pPlayer, int _iValue);
void TriggerTrap(CInfo* _pPlayer, int _iValue = 1);
void FindMagicBox(CInfo* _pPlayer, int _iValue = 1);
void FaceMonster(CInfo* _pPlayer, int _iValue = 2);
void StartBattle(CInfo* _pPlayer, CInfo* _pMonster);
void RenderBattleInfo(CInfo* _pPlayer, CInfo* _pMonster);



void LoadCharacter(CInfo** _pPlayer);
void SaveCharacter(CInfo* _pPlayer);
void Run_TextRPG();