/* Address: 0004181c; name: FUN_0004181c; body bytes: 282 */

undefined4 FUN_0004181c(int param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  int *piVar7;
  undefined4 *puVar8;
  
  puVar3 = *(undefined4 **)(param_2 + 0x38);
  puVar5 = (undefined4 *)0x0;
  do {
    do {
      puVar8 = puVar5;
      puVar5 = puVar3;
      if (puVar5 == (undefined4 *)0x0) {
        uVar6 = 0;
        puVar3 = DAT_2003a544;
        if (((*(int *)(param_2 + 0x3c) == 0) || (*(char *)(param_2 + 0x44) == '\0')) ||
           (*(int *)(param_2 + 0x38) != 0)) {
          for (; puVar3 != (undefined4 *)0x0; puVar3 = (undefined4 *)*puVar3) {
            iVar4 = (*(code *)puVar3[3])(puVar3,param_2);
            if (iVar4 != -1) {
              uVar6 = 1;
            }
          }
        }
        else {
          for (puVar3 = *(undefined4 **)(*(int *)(param_2 + 0x3c) + 0x38);
              puVar3 != (undefined4 *)0x0; puVar3 = (undefined4 *)*puVar3) {
            if (((*(char *)(puVar3 + 1) == '\x06') && (puVar3[0x12] == 0)) &&
               (*(int *)(puVar3[0x13] + 0x1c) == param_2)) {
              puVar3[0x12] = 1;
              DAT_2003a550 = 1;
              return 0;
            }
          }
        }
        return uVar6;
      }
      puVar3 = (undefined4 *)*puVar5;
    } while (puVar5[0x12] != 3);
    if (puVar8 == (undefined4 *)0x0) {
      *(undefined4 **)(param_2 + 0x38) = puVar3;
    }
    else {
      *puVar8 = puVar3;
    }
    if (*(char *)(puVar5 + 1) == '\x06') {
      piVar7 = *(int **)(puVar5[0x13] + 0x1c);
      if (*piVar7 != 0) {
        iVar4 = FUN_0003db0a(piVar7 + 1);
        iVar4 = FUN_000375de((uint)*(ushort *)(*piVar7 + 8) * iVar4);
        DAT_2003a54c = DAT_2003a54c - iVar4;
        FUN_000413fe(*piVar7);
        *piVar7 = 0;
      }
      if (param_1 != 0) {
        piVar1 = *(int **)(param_1 + 0x2a8);
        do {
          piVar2 = piVar1;
          if (piVar2 == (int *)0x0) goto LAB_000418b4;
          piVar1 = (int *)piVar2[0x10];
        } while ((int *)piVar2[0x10] != piVar7);
        piVar2[0x10] = piVar7[0x10];
LAB_000418b4:
        if (*(code **)(param_1 + 0x2b0) != (code *)0x0) {
          (**(code **)(param_1 + 0x2b0))(param_1,piVar7);
        }
        FUN_00046bec(piVar7);
      }
    }
    iVar4 = FUN_00045f9a(puVar5);
    if ((iVar4 != 0) && ((int)((uint)*(byte *)(iVar4 + 0x4c) << 0x19) < 0)) {
      FUN_00046bec(*(undefined4 *)(iVar4 + 0x1c));
      *(undefined4 *)(iVar4 + 0x1c) = 0;
    }
    FUN_00046bec(puVar5[0x13]);
    FUN_00046bec(puVar5);
    puVar5 = puVar8;
  } while( true );
}

