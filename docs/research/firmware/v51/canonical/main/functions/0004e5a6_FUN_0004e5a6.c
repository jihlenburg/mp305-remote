/* Address: 0004e5a6; name: FUN_0004e5a6; body bytes: 62 */

undefined4 FUN_0004e5a6(int param_1,undefined2 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int local_28;
  int local_24;
  undefined2 local_20;
  undefined4 local_1c;
  undefined4 uStack_18;
  byte local_10;
  
  if (param_1 == 0) {
    uVar1 = 1;
  }
  else {
    local_1c = 0;
    local_10 = local_10 & 0xf8;
    local_28 = param_1;
    local_24 = param_1;
    local_20 = param_2;
    uStack_18 = param_3;
    FUN_00046794(&local_28);
    uVar1 = FUN_00035f5a(&local_28);
    FUN_00046788(&local_28);
  }
  return uVar1;
}

