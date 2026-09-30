/* Address: 0001ccb8; name: FUN_0001ccb8; body bytes: 110 */

undefined4 FUN_0001ccb8(int param_1)

{
  bool bVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  uVar4 = DAT_4004800c;
  uVar3 = DAT_40048008;
  uVar2 = DAT_40048004;
  uVar5 = DAT_40048000;
  bVar1 = false;
  if (((DAT_40054026 & 7) == 5) || (param_1 == 5)) {
    bVar1 = true;
    DAT_40048000 = 0xfffffa0e;
    DAT_40048004 = 0xffffffff;
    DAT_40048008 = 0xffffffff;
    DAT_4004800c = 0xffffffff;
    FUN_000144fc(0x1e);
  }
  DAT_40054026 = (byte)param_1;
  FUN_000144fc(0x1e);
  if (bVar1) {
    DAT_40048000 = uVar5;
    DAT_40048004 = uVar2;
    DAT_40048008 = uVar3;
    DAT_4004800c = uVar4;
    uVar5 = FUN_000144fc(0x1e);
    return uVar5;
  }
  return uVar5;
}

