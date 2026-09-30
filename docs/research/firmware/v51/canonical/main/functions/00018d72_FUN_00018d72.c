/* Address: 00018d72; name: FUN_00018d72; body bytes: 66 */

uint FUN_00018d72(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = FUN_00015ee8();
  iVar2 = FUN_00012c98(param_1,0xf);
  uVar3 = FUN_00012c98(param_1,0x10);
  if ((iVar2 == 0xff) && (uVar3 == 0xff)) {
    iVar2 = 0;
    uVar3 = 0;
  }
  return ((((uVar3 | iVar2 << 8) >> 6) + 1) * (uint)*(ushort *)(iVar1 + 0x12) * 2 + 5) / 10 & 0xffff
  ;
}

