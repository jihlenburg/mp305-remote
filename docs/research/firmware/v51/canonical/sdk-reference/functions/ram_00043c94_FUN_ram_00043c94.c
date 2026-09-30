/* Address: ram:00043c94; name: FUN_ram_00043c94; body bytes: 48 */

void FUN_ram_00043c94(undefined4 param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  gp = 0x20004000;
  uVar1 = 0;
  if (*(int *)(param_2 + 4) != 0) {
    uVar1 = FUN_ram_00041bf2(*(int *)(param_2 + 4),1,param_3,param_2);
  }
  FUN_ram_000433e0(param_1,&LAB_ram_0004399a,0xd,param_2,uVar1);
  return;
}

