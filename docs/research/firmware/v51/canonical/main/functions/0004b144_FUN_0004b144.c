/* Address: 0004b144; name: FUN_0004b144; body bytes: 200 */

undefined4 * FUN_0004b144(undefined4 *param_1,int param_2)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  ushort uVar4;
  int iVar5;
  uint uVar6;
  
  uVar6 = 0;
  puVar1 = param_1;
  do {
    if (puVar1 == (undefined4 *)0x0) {
LAB_0004b164:
      puVar1 = (undefined4 *)FUN_0004a360(uVar6);
      if (puVar1 != (undefined4 *)0x0) {
        *puVar1 = param_1;
        puVar1[1] = param_2;
        if (param_2 == 0) {
          iVar3 = FUN_00040890();
          if (iVar3 == 0) {
            FUN_00046bec(puVar1);
            puVar1 = (undefined4 *)0x0;
          }
          else {
            if (*(int *)(iVar3 + 0x2b4) == 0) {
              *(undefined4 *)(iVar3 + 0x2d0) = 0;
            }
            iVar2 = FUN_0004f588(*(int *)(iVar3 + 0x2b4),*(int *)(iVar3 + 0x2d0) * 4 + 4);
            if (iVar2 == 0) {
              do {
                    /* WARNING: Do nothing block with infinite loop */
              } while( true );
            }
            iVar5 = *(int *)(iVar3 + 0x2d0) + 1;
            *(int *)(iVar3 + 0x2d0) = iVar5;
            *(int *)(iVar3 + 0x2b4) = iVar2;
            *(undefined4 **)(iVar2 + iVar5 * 4 + -4) = puVar1;
            puVar1[5] = 0;
            puVar1[6] = 0;
            iVar3 = FUN_000408b0(0);
            puVar1[7] = iVar3 + -1;
            iVar3 = FUN_00040960(0);
            puVar1[8] = iVar3 + -1;
          }
        }
        else {
          if (*(int *)(param_2 + 8) == 0) {
            FUN_0004af28(param_2);
          }
          uVar4 = *(short *)(*(int *)(param_2 + 8) + 0x28) + 1;
          *(ushort *)(*(int *)(param_2 + 8) + 0x28) = uVar4;
          iVar3 = FUN_0004f588(**(undefined4 **)(param_2 + 8),(uint)uVar4 << 2);
          **(int **)(param_2 + 8) = iVar3;
          *(undefined4 **)(iVar3 + (uint)*(ushort *)(*(int *)(param_2 + 8) + 0x28) * 4 + -4) =
               puVar1;
        }
      }
      return puVar1;
    }
    if ((puVar1[8] & 0xffff0) != 0) {
      uVar6 = (puVar1[8] & 0xfffff) >> 4;
      goto LAB_0004b164;
    }
    puVar1 = (undefined4 *)*puVar1;
  } while( true );
}

