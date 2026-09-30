/* Address: ram:00043cde; name: FUN_ram_00043cde; body bytes: 56 */

undefined4 FUN_ram_00043cde(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  gp = 0x20004000;
  if (*(int *)(param_2 + 4) != 0) {
    uVar1 = FUN_ram_00041bf2(*(int *)(param_2 + 4),1);
    uVar1 = FUN_ram_000433e0(param_1,&LAB_ram_000439a0,0xf,param_2,uVar1);
    return uVar1;
  }
  return 2;
}

