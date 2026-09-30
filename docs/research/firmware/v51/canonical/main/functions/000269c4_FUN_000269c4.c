/* Address: 000269c4; name: FUN_000269c4; body bytes: 642 */

void FUN_000269c4(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  uint uVar8;
  
  iVar1 = FUN_00046688();
  uVar2 = FUN_00046756(param_1);
  if (iVar1 == 0x20) {
    DAT_1ffe02f8 = FUN_0003f90a();
    if (DAT_1ffe02f8 != 0x7fffffff) {
      FUN_0003f960(uVar2,DAT_1ffe0340,0,DAT_1ffe02f8,param_4);
      uVar3 = FUN_0003f778(uVar2);
      if (DAT_1ffe02f8 < uVar3 >> 1) {
        uVar4 = FUN_0004b9de(uVar2,0);
        FUN_0004ac0a(uVar4,3,0xfffffffe);
        uVar4 = FUN_0004b9de(uVar2,0);
        uVar5 = FUN_0004b9de(uVar2,1);
        uVar6 = 0x10;
      }
      else {
        uVar4 = FUN_0004b9de(uVar2,0);
        FUN_0004ac0a(uVar4,0,2);
        uVar4 = FUN_0004b9de(uVar2,0);
        uVar5 = FUN_0004b9de(uVar2,1);
        uVar6 = 0x13;
      }
      FUN_0004ac28(uVar5,uVar4,uVar6,0,0);
      if ((int)DAT_1ffe02f8 < DAT_1ffe029c) {
        iVar1 = FUN_0003f91a(uVar2,DAT_1ffe033c);
        iVar7 = *(int *)(iVar1 + DAT_1ffe02f8 * 4);
        iVar1 = FUN_0003f91a(uVar2,DAT_1ffe0338);
        uVar3 = (*(int *)(iVar1 + DAT_1ffe02f8 * 4) * iVar7) / 10000;
        iVar1 = FUN_0003f91a(uVar2,DAT_1ffe033c);
        iVar7 = *(int *)(iVar1 + DAT_1ffe02f8 * 4);
        iVar1 = FUN_0003f91a(uVar2,DAT_1ffe033c);
        iVar1 = *(int *)(iVar1 + DAT_1ffe02f8 * 4);
        uVar4 = FUN_0004b9de(uVar2,0);
        uVar4 = FUN_0004b9de(uVar4,0);
        FUN_000499de(uVar4,"V-%02d.%02dV",iVar1 / 100,iVar7 % 100);
        iVar1 = FUN_0003f91a(uVar2,DAT_1ffe0338);
        iVar1 = *(int *)(iVar1 + DAT_1ffe02f8 * 4);
        iVar7 = FUN_0003f91a(uVar2,DAT_1ffe0338);
        iVar7 = *(int *)(iVar7 + DAT_1ffe02f8 * 4);
        uVar4 = FUN_0004b9de(uVar2,0);
        uVar4 = FUN_0004b9de(uVar4,1);
        FUN_000499de(uVar4,"I-%d.%03dA",iVar7 / 1000,iVar1 % 1000);
        uVar8 = uVar3 % 10;
        uVar3 = uVar3 / 10;
        uVar4 = FUN_0004b9de(uVar2,0);
        uVar4 = FUN_0004b9de(uVar4,2);
      }
      else {
        uVar4 = FUN_0004b9de(uVar2,0);
        uVar4 = FUN_0004b9de(uVar4,0);
        FUN_000499de(uVar4,"V-%02d.%02dV",0);
        uVar4 = FUN_0004b9de(uVar2,0);
        uVar4 = FUN_0004b9de(uVar4,1);
        FUN_000499de(uVar4,"I-%d.%03dA",0);
        uVar4 = FUN_0004b9de(uVar2,0);
        uVar4 = FUN_0004b9de(uVar4,2);
        uVar8 = 0;
        uVar3 = 0;
      }
      FUN_000499de(uVar4,"P-%03d.%01dW",uVar3,uVar8);
      if (DAT_1ffe02ac == 0) {
        uVar4 = FUN_0004b9de(uVar2,0);
        uVar4 = FUN_0004b9de(uVar4,3);
        FUN_000499de(uVar4,"T-0:00:00");
      }
      else {
        if ((int)DAT_1ffe02f8 < DAT_1ffe029c) {
          iVar1 = (&DAT_1fffb300)[DAT_1ffe02f8];
          uVar4 = FUN_0004b9de(uVar2,0);
          uVar4 = FUN_0004b9de(uVar4,3);
          FUN_000499de(uVar4,"T-%ld:%02ld:%02ld",iVar1 / 0xe10,(iVar1 % 0xe10) / 0x3c,
                       (iVar1 % 0xe10) % 0x3c);
        }
        else {
          uVar4 = FUN_0004b9de(uVar2,0);
          uVar4 = FUN_0004b9de(uVar4,3);
          FUN_000499de(uVar4,"T-0:00:00");
        }
        FUN_0001cb8c(0xf);
      }
      uVar4 = FUN_0004b9de(uVar2,0);
      FUN_0004e00e(uVar4,1);
      uVar2 = FUN_0004b9de(uVar2,1);
      FUN_0004e00e(uVar2,1);
    }
    DAT_1fffabc0 = DAT_1ffe02f8;
  }
  return;
}

