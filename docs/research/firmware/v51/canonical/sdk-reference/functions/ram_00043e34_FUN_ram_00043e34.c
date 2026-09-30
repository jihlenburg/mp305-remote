/* Address: ram:00043e34; name: FUN_ram_00043e34; body bytes: 50 */

void FUN_ram_00043e34(undefined4 param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  gp = 0x20004000;
  uVar1 = 0;
  if (*(int *)(param_2 + 4) != 0) {
    uVar1 = FUN_ram_00041bf2(*(int *)(param_2 + 4),3,param_3,param_2,0);
  }
  FUN_ram_0004332a(param_1,&LAB_ram_000439f2,0x1b,param_2,uVar1);
  return;
}

