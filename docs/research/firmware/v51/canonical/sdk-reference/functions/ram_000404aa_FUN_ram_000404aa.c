/* Address: ram:000404aa; name: FUN_ram_000404aa; body bytes: 48 */

int FUN_ram_000404aa(undefined4 param_1,uint param_2)

{
  int iVar1;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_000402b0(param_2 & 0xffff,0x4f);
  if (iVar1 != 0) {
    FUN_ram_0004044c(iVar1,param_1,param_2);
  }
  return iVar1;
}

