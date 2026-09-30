/* Address: 00066b3c; name: FUN_00066b3c; body bytes: 100 */

undefined4 FUN_00066b3c(int *param_1,uint *param_2)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  
  enter_critical();
  uVar1 = DAT_1ffe000c - param_1[1];
  if (*(char *)(DAT_1ffe0000 + 0x4d) == '\0') {
    uVar2 = *param_2;
    if (uVar2 != 0xffffffff) {
      if ((*param_1 != DAT_1ffe0020) && ((uint)param_1[1] <= DAT_1ffe000c)) {
        uVar3 = 1;
        *param_2 = 0;
        goto LAB_00066b96;
      }
      if (uVar2 <= uVar1) {
        *param_2 = 0;
        goto LAB_00066b94;
      }
      *param_2 = uVar2 - uVar1;
      FUN_000659ac(param_1);
    }
    uVar3 = 0;
  }
  else {
    *(undefined1 *)(DAT_1ffe0000 + 0x4d) = 0;
LAB_00066b94:
    uVar3 = 1;
  }
LAB_00066b96:
  exit_critical();
  return uVar3;
}

