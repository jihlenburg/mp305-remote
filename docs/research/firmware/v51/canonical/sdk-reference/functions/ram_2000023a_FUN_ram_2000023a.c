/* Address: ram:2000023a; name: FUN_ram_2000023a; body bytes: 1 */

int FUN_ram_2000023a(undefined4 param_1,uint param_2)

{
  int iVar1;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_20000040(param_2 & 0xffff,0x4f);
  if (iVar1 != 0) {
    tmos_memcpy(iVar1,param_1,param_2);
  }
  return iVar1;
}

