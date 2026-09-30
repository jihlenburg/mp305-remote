/* Address: 00018d1a; name: FUN_00018d1a; body bytes: 78 */

undefined2 FUN_00018d1a(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined2 uVar4;
  
  iVar1 = FUN_00015ee8();
  uVar4 = 0;
  iVar2 = FUN_00018ccc(param_1);
  if (iVar2 != 0) {
    iVar2 = FUN_00012c98(param_1,0x11);
    uVar3 = FUN_00012c98(param_1,0x12);
    if ((iVar2 == 0xff) && (uVar3 == 0xff)) {
      iVar2 = 0;
      uVar3 = 0;
    }
    uVar4 = (undefined2)
            (((((uVar3 | iVar2 << 8) >> 6) + 1) * 0x14 * (uint)*(ushort *)(iVar1 + 0xc)) / 0xc);
  }
  return uVar4;
}

