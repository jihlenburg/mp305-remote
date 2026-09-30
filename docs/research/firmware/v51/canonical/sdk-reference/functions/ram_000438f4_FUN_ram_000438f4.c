/* Address: ram:000438f4; name: FUN_ram_000438f4; body bytes: 52 */

undefined4
FUN_ram_000438f4(undefined4 param_1,undefined4 param_2,undefined2 *param_3,uint param_4,
                undefined2 *param_5)

{
  undefined4 uVar1;
  
  gp = 0x20004000;
  uVar1 = 4;
  if (1 < param_4) {
    *param_5 = *param_3;
    param_5[1] = (short)param_4 + -2;
    if (param_4 == 2) {
      *(undefined4 *)(param_5 + 2) = 0;
    }
    else {
      *(undefined2 **)(param_5 + 2) = param_3 + 1;
    }
    uVar1 = 0;
  }
  return uVar1;
}

