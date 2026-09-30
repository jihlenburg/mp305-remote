/* Address: ram:00007568; name: FUN_ram_00007568; body bytes: 176 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_00007568(int param_1,uint param_2,undefined4 param_3,undefined4 param_4,
                     undefined4 param_5)

{
  uint uVar1;
  
  gp = &DAT_ram_20002000;
  (*_DAT_ram_0004004c)(&DAT_ram_20002e89,param_1,param_2,param_4,param_5,_DAT_ram_0004004c);
  (*_DAT_ram_00040174)(0x306,0x1f,&DAT_ram_20002e78);
  FUN_ram_200028d6(0xb,0x6e00,&DAT_ram_200042b0,param_2);
  for (uVar1 = 0; (uVar1 & 0xff) < param_2; uVar1 = uVar1 + 1) {
    (&DAT_ram_200042b0)[uVar1] = *(undefined1 *)(param_1 + uVar1);
  }
  FUN_ram_200028d6(9,0x6e00,0,0x100);
  FUN_ram_200028d6(10,0x6e00,&DAT_ram_200042b0,param_2);
  return;
}

