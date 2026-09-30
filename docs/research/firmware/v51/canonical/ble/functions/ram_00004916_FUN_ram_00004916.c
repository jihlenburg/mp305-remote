/* Address: ram:00004916; name: FUN_ram_00004916; body bytes: 78 */

void FUN_ram_00004916(uint param_1)

{
  uint uVar1;
  uint uVar2;
  
  gp = &DAT_ram_20002000;
  uVar1 = param_1 >> 8 & 0xff;
  uVar2 = param_1 >> 0x10 & 0xff;
  FUN_ram_00007968("GRB:(%d,%d,%d)",uVar2,uVar1,param_1 & 0xff);
  FUN_ram_000048c2(0x40,uVar2);
  FUN_ram_000048c2(1,uVar1);
  FUN_ram_000048c2(8,param_1 & 0xff);
  return;
}

