/* Address: 00038e78; name: FUN_00038e78; body bytes: 30 */

void FUN_00038e78(int param_1,int param_2)

{
  byte bVar1;
  ushort uVar2;
  bool bVar3;
  ushort uVar4;
  
  if (param_2 == 2) {
    uVar2 = *(ushort *)(param_1 + 4);
    bVar1 = *(byte *)(param_1 + 1);
    bVar3 = true;
  }
  else {
    if (param_2 != 0) {
      return;
    }
    uVar2 = *(ushort *)(param_1 + 4);
    bVar1 = *(byte *)(param_1 + 1);
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

