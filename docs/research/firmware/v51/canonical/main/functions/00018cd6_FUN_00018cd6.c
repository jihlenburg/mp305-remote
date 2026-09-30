/* Address: 00018cd6; name: FUN_00018cd6; body bytes: 68 */

uint FUN_00018cd6(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = FUN_00015ee8();
  iVar2 = FUN_00012c98(param_1,0x13);
  uVar3 = FUN_00012c98(param_1,0x14);
  if ((iVar2 == 0xff) && (uVar3 == 0xff)) {
    iVar2 = 0;
    uVar3 = 0;
  }
  return ((((uVar3 | iVar2 << 8) >> 6) + 1) * 0x14 * (uint)*(ushort *)(iVar1 + 0xe)) / 0xc & 0xffff;
}

