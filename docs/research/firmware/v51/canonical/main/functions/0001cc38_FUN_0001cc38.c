/* Address: 0001cc38; name: FUN_0001cc38; body bytes: 116 */

undefined4 FUN_0001cc38(uint param_1,uint param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  bool bVar5;
  
  uVar3 = DAT_4004800c;
  uVar2 = DAT_40048008;
  uVar1 = DAT_40048004;
  uVar4 = DAT_40048000;
  bVar5 = (DAT_40054026 & 7) == 5;
  if (bVar5) {
    DAT_40048000 = 0xfffffa0e;
    DAT_40048004 = 0xffffffff;
    DAT_40048008 = 0xffffffff;
    DAT_4004800c = 0xffffffff;
    FUN_000144fc(0x1e);
  }
  DAT_40054020 = DAT_40054020 & ~param_1 | param_2 & param_1;
  FUN_000144fc(0x1e);
  if (bVar5) {
    DAT_40048000 = uVar4;
    DAT_40048004 = uVar1;
    DAT_40048008 = uVar2;
    DAT_4004800c = uVar3;
    uVar4 = FUN_000144fc(0x1e);
    return uVar4;
  }
  return uVar4;
}

