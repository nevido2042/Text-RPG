#pragma once
#include "info.h"

void CreateCharacter(INFO** _ppPlayer);
void SetSTAT(INFO* _pPlayer);
void SelectTask(INFO* _pPlayer);
int GetInput(int* _pInput);
void OpenShop(INFO* _pPlayer, INFO* _pMerchant);
void RenderShop(INFO* _pPlayer, INFO* _pMerchant);
void BuyItem(INFO* _pPlayer, INFO* _pMerchant);
void SellItem(INFO* _pPlayer, INFO* _pMerchant);
void SelectDungeon(INFO* _pPlayer);
int InputCheck();
int RollDice(int iValue);

void Enter_Grassland(INFO* _pPlayer);
void Enter_Mountain(INFO* _pPlayer);
void Enter_Cave(INFO* _pPlayer);

void TriggerRandomEvent(INFO* _pPlayer);
void TriggerTrap(INFO* _pPlayer, int _iValue = 1);
void FindMagicBox(INFO* _pPlayer, int _iValue = 1);
void FaceMonster(INFO* _pPlayer, int _iValue = 2);
void StartBattle(INFO* _pPlayer, INFO* _pMonster);
void RenderBattleInfo(INFO* _pPlayer, INFO* _pMonster);
void TryAttack(INFO* _pAttacker, INFO* _pTarget);


void LoadCharacter(INFO** _pPlayer);
void SaveCharacter(INFO* _pPlayer);
void Run_TextRPG();