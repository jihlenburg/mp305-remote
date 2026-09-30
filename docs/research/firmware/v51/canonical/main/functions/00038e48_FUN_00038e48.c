/* Address: 00038e48; name: FUN_00038e48; body bytes: 52 */

void FUN_00038e48(int param_1,int param_2)

{
  byte bVar1;
  ushort uVar2;
  bool bVar3;
  ushort uVar4;
  
  if (param_2 == 2) {
    uVar2 = *(ushort *)(param_1 + 6);
    bVar1 = *(byte *)(param_1 + 2);
    bVar3 = true;
  }
  else {
    if (param_2 != 0) {
      return;
    }
    uVar2 = *(ushort *)(param_1 + 6);
    bVar1 = *(byte *)(param_1 + 2);
    bVar3 = false;
  }
  uVar4 = *(ushort *)(&DAT_40053806 + (uint)bVar1 * 0x10);
  if (bVar3) {
    uVar4 = uVar4 | uVar2;
  }
  else {
    uVar4 = uVar4 & ~uVar2;
  }
  *(ushort *)(&DAT_40053806 + (uint)bVar1 * 0x10) = uVar4;
  return;
}

