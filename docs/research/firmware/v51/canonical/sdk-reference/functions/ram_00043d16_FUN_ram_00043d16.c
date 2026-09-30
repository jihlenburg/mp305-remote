/* Address: ram:00043d16; name: FUN_ram_00043d16; body bytes: 66 */

undefined4 FUN_ram_00043d16(undefined4 param_1,short *param_2)

{
  undefined4 uVar1;
  
  gp = 0x20004000;
  if (*param_2 == 0) {
    return 2;
  }
  if (*(int *)(param_2 + 2) != 0) {
    uVar1 = FUN_ram_00041bf2(*(int *)(param_2 + 2),2);
    uVar1 = FUN_ram_000433e0(param_1,&LAB_ram_000439a6,0x11,param_2,uVar1);
    return uVar1;
  }
  return 2;
}

