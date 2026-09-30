/* Address: 000402f4; name: FUN_000402f4; body bytes: 28 */

undefined4 FUN_000402f4(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 extraout_r2;
  int extraout_r3;
  undefined8 uVar2;
  
  uVar2 = FUN_00040554();
  iVar1 = FUN_00040554(param_2,(int)((ulonglong)uVar2 >> 0x20),extraout_r2,(int)uVar2);
  if (extraout_r3 == iVar1) {
    return 1;
  }
  return 0;
}

