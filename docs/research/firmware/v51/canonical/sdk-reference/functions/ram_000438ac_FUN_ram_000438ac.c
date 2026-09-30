/* Address: ram:000438ac; name: FUN_ram_000438ac; body bytes: 46 */

void FUN_ram_000438ac(undefined4 param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  gp = 0x20004000;
  uVar1 = 0;
  if (*(int *)(param_2 + 8) != 0) {
    uVar1 = FUN_ram_00041bf2(*(int *)(param_2 + 8),5,param_3,param_2);
  }
  FUN_ram_0004332a(param_1,&LAB_ram_0004351e,0x16,param_2,uVar1);
  return;
}

