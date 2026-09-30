/* Address: 00018ca4; name: FUN_00018ca4; body bytes: 40 */

void FUN_00018ca4(undefined4 param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = FUN_00015ee8();
  uVar2 = FUN_00012c98(param_1,0xc);
  uVar2 = uVar2 & 0xffffffbf | (param_2 & 1) << 6;
  *(char *)(iVar1 + 8) = (char)uVar2;
  FUN_00012cb0(param_1,0xc,uVar2);
  return;
}

