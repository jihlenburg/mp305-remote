/* Address: 00022768; name: FUN_00022768; body bytes: 204 */

void FUN_00022768(undefined4 param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  
  if (199 < DAT_1ffe0294) {
    uVar2 = 0;
    do {
      (&DAT_1fffb620)[uVar2] = (&DAT_1fffb624)[uVar2];
      uVar2 = uVar2 + 1 & 0xff;
    } while (uVar2 < 199);
    uVar3 = FUN_00052960(param_1);
    FUN_0003f9a4(uVar3,DAT_1ffe0334,&DAT_1fffb620);
    DAT_1ffe0294 = 199;
  }
  iVar1 = DAT_1ffe0294;
  (&DAT_1fffb620)[DAT_1ffe0294] = (uint)DAT_1fffab7a;
  if (iVar1 < 200) {
    uVar3 = FUN_00052960(param_1);
    FUN_0003fa78(uVar3,DAT_1ffe0334,DAT_1ffe0294,(&DAT_1fffb620)[DAT_1ffe0294]);
  }
  FUN_00052960(param_1);
  thunk_FUN_0004d3d8();
  DAT_1ffe0294 = DAT_1ffe0294 + 1;
  uVar2 = (uint)DAT_1fffab7a;
  uVar4 = (uint)DAT_1fffab72 * 10;
  if (uVar4 < uVar2) {
    uVar2 = uVar4 & 0xffff;
  }
  uVar4 = (uVar2 * 100) / uVar4 & 0xffff;
  FUN_0003cb2a(&DAT_1fffbb70,DAT_1ffe0560);
  FUN_0003cafa(&DAT_1fffbb70,0x5e799);
  uVar2 = (uint)DAT_1ffe026c;
  if (uVar4 < uVar2) {
    if (0x13 < (uVar2 - uVar4 & 0xffff)) {
      uVar4 = uVar2 - 0x14 & 0xffff;
    }
    uVar3 = 0x5a;
  }
  else {
    uVar3 = 10;
  }
  FUN_0003cb16(&DAT_1fffbb70,uVar3);
  FUN_0003cb1e(&DAT_1fffbb70,DAT_1ffe026c,uVar4);
  FUN_0003cb6c(&DAT_1fffbb70);
  DAT_1ffe026c = (short)uVar4;
  return;
}

