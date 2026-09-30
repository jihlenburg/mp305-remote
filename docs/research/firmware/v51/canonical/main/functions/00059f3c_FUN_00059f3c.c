/* Address: 00059f3c; name: FUN_00059f3c; body bytes: 146 */

int FUN_00059f3c(uint param_1)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  int *piVar4;
  int *piVar5;
  int iVar6;
  
  iVar6 = 0;
  FUN_00065c04();
  if (DAT_1ffe0060 == (int *)0x0) {
    FUN_00059aa4();
  }
  if ((((param_1 != 0) && (uVar3 = 0x10 - (param_1 & 7), param_1 <= ~uVar3)) &&
      (param_1 = param_1 + uVar3, 0 < (int)param_1)) && (param_1 <= DAT_1ffe0064)) {
    piVar1 = (int *)&DAT_1ffe0074;
    piVar2 = DAT_1ffe0074;
    do {
      piVar5 = piVar2;
      piVar4 = piVar1;
      if (param_1 <= (uint)piVar5[1]) break;
      piVar1 = piVar5;
      piVar2 = (int *)*piVar5;
    } while ((int *)*piVar5 != (int *)0x0);
    if (piVar5 != DAT_1ffe0060) {
      iVar6 = *piVar4;
      *piVar4 = *piVar5;
      iVar6 = iVar6 + 8;
      if (0x10 < piVar5[1] - param_1) {
        *(uint *)((int)piVar5 + param_1 + 4) = piVar5[1] - param_1;
        piVar5[1] = param_1;
        FUN_00059bcc();
      }
      DAT_1ffe0064 = DAT_1ffe0064 - piVar5[1];
      if (DAT_1ffe0064 < DAT_1ffe0068) {
        DAT_1ffe0068 = DAT_1ffe0064;
      }
      piVar5[1] = piVar5[1] | 0x80000000;
      *piVar5 = 0;
      DAT_1ffe006c = DAT_1ffe006c + 1;
    }
  }
  FUN_00066f6c();
  return iVar6;
}

