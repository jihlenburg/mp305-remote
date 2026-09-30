/* Address: 0001f054; name: FUN_0001f054; body bytes: 138 */

void FUN_0001f054(int param_1,undefined4 param_2,undefined4 *param_3)

{
  int iVar1;
  uint local_28;
  undefined4 uStack_24;
  int local_20;
  uint local_1c;
  undefined4 local_18;
  
  local_28 = FUN_0001f004();
  local_28 = local_28 / (uint)(1 << ((*(uint *)(param_1 + 0x18) & 3) << 1));
  local_18 = 0;
  local_1c = 0xff;
  uStack_24 = param_2;
  if ((*(uint *)(param_1 + 0xc) & 0x1000000) == 0) {
    if (*(int *)(param_1 + 0x14) << 0x1a < 0) {
      iVar1 = FUN_0001d228(param_1,&local_28);
    }
    else {
      iVar1 = FUN_0001e0bc();
    }
  }
  else {
    iVar1 = FUN_00013f40(param_1,&local_28);
  }
  if ((iVar1 == 0) &&
     (*(uint *)(param_1 + 8) =
           (local_1c | local_20 << 8) & 0xff7f | *(uint *)(param_1 + 8) & 0xffff0080,
     local_1c != 0xff)) {
    *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) | 0x20000000;
  }
  if (param_3 != (undefined4 *)0x0) {
    *param_3 = local_18;
  }
  return;
}

