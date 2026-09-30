/* Address: 0003f028; name: FUN_0003f028; body bytes: 44 */

void FUN_0003f028(int param_1,uint param_2)

{
  if ((*(uint *)(param_1 + 0x38) <= param_2) && (param_2 != 0xffff)) {
    return;
  }
  FUN_0003aa70(param_1,*(undefined4 *)(param_1 + 0x40));
  *(uint *)(param_1 + 0x40) = param_2;
  FUN_0003aa70(param_1,param_2);
  return;
}

