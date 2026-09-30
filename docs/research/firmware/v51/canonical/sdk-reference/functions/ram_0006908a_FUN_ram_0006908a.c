/* Address: ram:0006908a; name: FUN_ram_0006908a; body bytes: 82 */

uint FUN_ram_0006908a(undefined4 param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  gp = 0x20004000;
  uVar1 = 0;
  while ((uVar3 = (uint)DAT_ram_20001a8d, uVar1 < uVar3 &&
         (iVar2 = tmos_memcmp(uVar1 * 0x10 + DAT_ram_20001a88,param_1,6), uVar3 = uVar1, iVar2 == 0)
         )) {
    uVar1 = uVar1 + 1 & 0xff;
  }
  return uVar3;
}

