/* Address: ram:0004367c; name: FUN_ram_0004367c; body bytes: 62 */

undefined4 FUN_ram_0004367c(undefined4 param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  gp = 0x20004000;
  if (*(char *)(param_2 + 4) == '\x02') {
    uVar1 = 0;
    if (*(int *)(param_2 + 0xc) != 0) {
      uVar1 = FUN_ram_00041bf2(*(int *)(param_2 + 0xc),7,param_3,param_2,0);
    }
    uVar1 = FUN_ram_0004332a(param_1,&LAB_ram_00043476,6,param_2,uVar1);
    return uVar1;
  }
  return 2;
}

