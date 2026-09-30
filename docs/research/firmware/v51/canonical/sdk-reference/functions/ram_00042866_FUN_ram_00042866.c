/* Address: ram:00042866; name: FUN_ram_00042866; body bytes: 64 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_ram_00042866(undefined4 param_1,int param_2)

{
  uint uVar1;
  ushort auStack_20 [12];
  
  gp = 0x20004000;
  FUN_ram_0006be7a(auStack_20,&DAT_ram_0006bf30,0x10);
  if ((uint)_DAT_ram_20001b8e + (uint)auStack_20[param_2] == 0) {
    uVar1 = 0xffffffff;
  }
  else {
    uVar1 = 1000000 / ((uint)_DAT_ram_20001b8e + (uint)auStack_20[param_2]);
  }
  return uVar1;
}

