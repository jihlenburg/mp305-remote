/* Address: 0003f338; name: FUN_0003f338; body bytes: 310 */

void FUN_0003f338(int param_1,undefined2 param_2,char param_3)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  
  *(undefined2 *)(param_1 + 0x34) = param_2;
  iVar4 = (int)param_3;
  *(char *)(param_1 + 0x36) = param_3;
  *(undefined1 *)(param_1 + 0x37) = 1;
  FUN_0003e84e(*(undefined4 *)(param_1 + 0x2c),0x40);
  uVar6 = 0;
  do {
    FUN_0003ede0(*(undefined4 *)(param_1 + 0x2c),uVar6,0x40);
    uVar6 = uVar6 + 1;
  } while (uVar6 < 7);
  iVar2 = FUN_0003777c(param_2,iVar4);
  uVar3 = FUN_00037294(param_2,iVar4,1);
  cVar1 = '\x01';
  for (uVar6 = uVar3; uVar6 < iVar2 + uVar3; uVar6 = uVar6 + 1) {
    FUN_00050540(param_1 + uVar6 * 0x14 + 0x121,0x14,&DAT_0003f474,cVar1);
    cVar1 = cVar1 + '\x01';
  }
  iVar4 = FUN_0003777c(param_2,iVar4 + -1);
  uVar6 = iVar4 - uVar3;
  for (uVar5 = 0; uVar6 = uVar6 + 1 & 0xff, uVar5 < uVar3; uVar5 = uVar5 + 1) {
    FUN_00050540(param_1 + uVar5 * 0x14 + 0x121,0x14,&DAT_0003f474,uVar6);
    FUN_0003ede0(*(undefined4 *)(param_1 + 0x2c),uVar5 + 7,0x40);
  }
  cVar1 = '\x01';
  for (uVar6 = uVar3 + iVar2; uVar6 < 0x2a; uVar6 = uVar6 + 1) {
    FUN_00050540(param_1 + uVar6 * 0x14 + 0x121,0x14,&DAT_0003f474,cVar1);
    FUN_0003ede0(*(undefined4 *)(param_1 + 0x2c),uVar6 + 7,0x40);
    cVar1 = cVar1 + '\x01';
  }
  FUN_0003816c(param_1);
  iVar4 = FUN_0003edc4(*(undefined4 *)(param_1 + 0x2c));
  if (iVar4 != 0xffff) {
    FUN_0003f028(*(undefined4 *)(param_1 + 0x2c),uVar3 + 7);
  }
  FUN_0004d3d8(param_1);
  uVar6 = FUN_0004ba5c(param_1);
  for (uVar3 = 0; uVar3 < uVar6; uVar3 = uVar3 + 1) {
    iVar4 = FUN_0004b9de(param_1,uVar3);
    if (*(int *)(param_1 + 0x2c) != iVar4) {
      FUN_0004e5a6(iVar4,0x20,param_1);
    }
  }
  return;
}

