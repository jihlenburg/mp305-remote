/* Address: 00053fb8; name: FUN_00053fb8; body bytes: 178 */

void FUN_00053fb8(int param_1,int param_2,uint param_3,int *param_4)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  if (*param_4 != 0) {
    uVar4 = *(uint *)(param_1 + 0x70);
    if (*(int *)(param_2 + 0xc) == 0) {
      iVar1 = FUN_0004f588(*param_4,param_3 << 2);
      *param_4 = iVar1;
      if (iVar1 == 0) {
        do {
                    /* WARNING: Do nothing block with infinite loop */
        } while( true );
      }
      if (uVar4 < param_3) {
        for (uVar4 = uVar4 - 1; uVar4 < param_3; uVar4 = uVar4 + 1) {
          *(undefined4 *)(*param_4 + uVar4 * 4) = 0x7fffffff;
        }
      }
    }
    else {
      iVar1 = FUN_0004a318();
      if (iVar1 == 0) {
        do {
                    /* WARNING: Do nothing block with infinite loop */
        } while( true );
      }
      uVar2 = 0;
      if (param_3 < uVar4) {
        for (; uVar2 < param_3; uVar2 = uVar2 + 1) {
          uVar3 = *(int *)(param_2 + 0xc) + uVar2;
          *(undefined4 *)(iVar1 + uVar2 * 4) =
               *(undefined4 *)(*param_4 + (uVar3 - uVar4 * (uVar3 / uVar4)) * 4);
        }
      }
      else {
        for (; uVar2 < uVar4; uVar2 = uVar2 + 1) {
          uVar3 = *(int *)(param_2 + 0xc) + uVar2;
          *(undefined4 *)(iVar1 + uVar2 * 4) =
               *(undefined4 *)(*param_4 + (uVar3 - uVar4 * (uVar3 / uVar4)) * 4);
        }
        for (; uVar4 < param_3; uVar4 = uVar4 + 1) {
          *(undefined4 *)(iVar1 + uVar4 * 4) = 0x7fffffff;
        }
      }
      FUN_00046bec(*param_4);
      *param_4 = iVar1;
    }
  }
  return;
}

