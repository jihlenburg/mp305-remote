/* Address: 000535b0; name: FUN_000535b0; body bytes: 344 */

void FUN_000535b0(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  byte bVar5;
  undefined4 uVar6;
  
  DAT_1ffe02b4 = 0;
  if ((DAT_1fffaace == '\0') && (DAT_1fffaadb == '\0')) {
    bVar5 = 1;
    uVar6 = 0xffffff;
    do {
      uVar1 = FUN_0004675a(param_1);
      iVar2 = FUN_0004b9de(uVar1,bVar5);
      iVar3 = FUN_00046756(param_1);
      if (iVar2 == iVar3) {
        requested_mode = bVar5 - 1;
      }
      uVar1 = FUN_0004675a(param_1);
      iVar2 = FUN_0004b9de(uVar1,bVar5);
      iVar3 = FUN_00046756(param_1);
      uVar1 = uVar6;
      if (iVar2 == iVar3) {
        uVar1 = 0;
      }
      uVar1 = FUN_0004037c(uVar1);
      uVar4 = FUN_0004675a(param_1);
      uVar4 = FUN_0004b9de(uVar4,bVar5);
      FUN_0004e8b2(uVar4,uVar1,0);
      uVar1 = FUN_0004675a(param_1);
      iVar2 = FUN_0004b9de(uVar1,bVar5);
      iVar3 = FUN_00046756(param_1);
      uVar1 = uVar6;
      if (iVar2 != iVar3) {
        uVar1 = 0;
      }
      uVar1 = FUN_0004037c(uVar1);
      uVar4 = FUN_0004675a(param_1);
      uVar4 = FUN_0004b9de(uVar4,bVar5);
      uVar4 = FUN_0004b9de(uVar4,1);
      FUN_0004ea90(uVar4,uVar1,0);
      uVar1 = FUN_0004675a(param_1);
      iVar2 = FUN_0004b9de(uVar1,bVar5);
      iVar3 = FUN_00046756(param_1);
      uVar1 = uVar6;
      if (iVar2 != iVar3) {
        uVar1 = 0;
      }
      uVar1 = FUN_0004037c(uVar1);
      uVar4 = FUN_0004675a(param_1);
      uVar4 = FUN_0004b9de(uVar4,bVar5);
      uVar4 = FUN_0004b9de(uVar4,0);
      FUN_0004e960(uVar4,uVar1,0);
      bVar5 = bVar5 + 1;
    } while (bVar5 < 5);
    DAT_1ffe0240 = 0;
    if ((DAT_1ffe04f4 != 0) && (iVar2 = FUN_000527ec(DAT_1ffe0504), iVar2 == DAT_1ffe0534)) {
      FUN_000527f0(DAT_1ffe0504,DAT_1ffe0508,0);
    }
    iVar2 = FUN_000527ec(DAT_1ffe0344);
    if (iVar2 == DAT_1ffe04f0) {
      FUN_000527f0(DAT_1ffe0344,DAT_1ffe0348,0);
    }
    if (DAT_1ffe0330 != 0) {
      FUN_0001ba58();
      return;
    }
  }
  return;
}

