/* Address: 00052c1c; name: FUN_00052c1c; body bytes: 228 */

int FUN_00052c1c(undefined4 param_1,int param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  
  iVar4 = 0;
  if (param_2 == 0) {
    iVar4 = FUN_00052bf6(param_1,param_3);
    return iVar4;
  }
  if (param_3 != 0) {
    iVar5 = param_2 + -8;
    iVar4 = FUN_00024cea(iVar5);
    uVar6 = *(uint *)(param_2 + -4) & 0xfffffffc;
    uVar1 = *(uint *)(iVar4 + 4);
    uVar2 = FUN_000229b4(param_3,4);
    if ((uVar6 < param_3) && (uVar2 == 0)) {
      return 0;
    }
    if ((*(byte *)(param_2 + -4) & 1) != 0) {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    if ((uVar2 <= uVar6) ||
       (((*(byte *)(iVar4 + 4) & 1) != 0 && (uVar2 <= (uVar1 & 0xfffffffc) + uVar6 + 4)))) {
      if (uVar6 < uVar2) {
        FUN_00024cb4(param_1,iVar5);
        FUN_00024c9a(iVar5);
      }
      if ((*(byte *)(param_2 + -4) & 1) == 0) {
        iVar4 = FUN_00024b56(iVar5,uVar2);
        if (iVar4 == 0) {
          return param_2;
        }
        iVar4 = FUN_00024d72(iVar5,uVar2);
        *(uint *)(iVar4 + 4) = *(uint *)(iVar4 + 4) & 0xfffffffd;
        uVar3 = FUN_00024cb4(param_1);
        FUN_00024b6a(param_1,uVar3);
        return param_2;
      }
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    iVar4 = FUN_00052bf6(param_1,param_3);
    if (iVar4 == 0) {
      return 0;
    }
    if (param_3 <= uVar6) {
      uVar6 = param_3;
    }
    FUN_0004a404(iVar4,param_2,uVar6);
  }
  FUN_00052b98(param_1,param_2);
  return iVar4;
}

