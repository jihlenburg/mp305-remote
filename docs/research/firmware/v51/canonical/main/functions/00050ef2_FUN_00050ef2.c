/* Address: 00050ef2; name: FUN_00050ef2; body bytes: 138 */

void FUN_00050ef2(int *param_1,uint param_2,undefined4 param_3)

{
  uint uVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  
  uVar3 = (uint)*(byte *)(param_1 + 2);
  if (uVar3 != 0xff) {
    if (param_2 == 0) {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    iVar5 = *param_1;
    if (iVar5 == 0) {
LAB_00050f28:
      iVar5 = FUN_0004f588(iVar5,(uVar3 + 1) * 5);
      if (iVar5 != 0) {
        *param_1 = iVar5;
        uVar3 = (uint)*(byte *)(param_1 + 2);
        iVar4 = iVar5 + uVar3 * 4;
        while (uVar3 = uVar3 - 1, -1 < (int)uVar3) {
          *(undefined1 *)(iVar4 + uVar3 + 4) = *(undefined1 *)(iVar4 + uVar3);
        }
        bVar2 = (char)param_1[2] + 1;
        *(byte *)(param_1 + 2) = bVar2;
        *(char *)(iVar5 + (uint)bVar2 * 5 + -1) = (char)param_2;
        *(undefined4 *)(iVar5 + (uint)*(byte *)(param_1 + 2) * 4 + -4) = param_3;
        param_2 = param_2 >> 2;
        if (0x1e < param_2) {
          param_2 = 0x1f;
        }
        param_1[1] = param_1[1] | 1 << (param_2 & 0xff);
      }
    }
    else {
      uVar1 = uVar3;
      do {
        uVar1 = uVar1 - 1;
        if ((int)uVar1 < 0) goto LAB_00050f28;
      } while (*(byte *)(iVar5 + uVar3 * 4 + uVar1) != param_2);
      *(undefined4 *)(iVar5 + uVar1 * 4) = param_3;
    }
  }
  return;
}

