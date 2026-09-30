/* Address: ram:00043a74; name: FUN_ram_00043a74; body bytes: 82 */

undefined4 FUN_ram_00043a74(undefined4 param_1,short *param_2)

{
  undefined4 uVar1;
  
  gp = 0x20004000;
  if (((byte)((char)param_2[1] - 1U) < 2) && (*param_2 != 0)) {
    if (*(int *)(param_2 + 2) != 0) {
      uVar1 = FUN_ram_00041bf2(*(int *)(param_2 + 2),2);
      uVar1 = FUN_ram_000433e0(param_1,&LAB_ram_00043948,5,param_2,uVar1);
      return uVar1;
    }
    return 2;
  }
  return 2;
}

