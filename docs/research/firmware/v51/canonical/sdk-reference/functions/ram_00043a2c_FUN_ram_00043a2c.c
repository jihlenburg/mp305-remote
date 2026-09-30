/* Address: ram:00043a2c; name: FUN_ram_00043a2c; body bytes: 30 */

undefined4 FUN_ram_00043a2c(undefined4 param_1,ushort *param_2)

{
  undefined4 uVar1;
  
  gp = 0x20004000;
  if (0x16 < *param_2) {
    uVar1 = FUN_ram_000433e0(param_1,&LAB_ram_00043932,3,param_2,0);
    return uVar1;
  }
  return 2;
}

