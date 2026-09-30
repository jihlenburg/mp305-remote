/* Address: 00016a6e; name: FUN_00016a6e; body bytes: 100 */

undefined4 FUN_00016a6e(undefined4 param_1,uint param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  FUN_00038ee2();
  FUN_00038e9e(param_1,(param_2 & 0x7f) << 1);
  FUN_00038f48(param_1);
  FUN_00038e9e(param_1,param_3);
  FUN_00038f48(param_1);
  FUN_00038ee2(param_1);
  FUN_00038e9e(param_1,param_2 * 2 + 1 & 0xff);
  iVar1 = FUN_00038f48(param_1);
  uVar2 = FUN_00038df6(param_1);
  FUN_00038dc4(param_1);
  FUN_00038f22(param_1);
  if (iVar1 != 0) {
    return 0;
  }
  return uVar2;
}

