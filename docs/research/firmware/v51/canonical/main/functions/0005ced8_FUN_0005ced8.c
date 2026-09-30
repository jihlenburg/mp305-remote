/* Address: 0005ced8; name: FUN_0005ced8; body bytes: 354 */

void FUN_0005ced8(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  
  DAT_1ffe02b4 = 0;
  if (DAT_1ffe0242 == -1) {
    FUN_0001cb8c(0xf);
    return;
  }
  uVar1 = FUN_0004b9de(DAT_1ffe0454,1);
  iVar2 = FUN_0004cd84(uVar1,1);
  iVar3 = (int)DAT_1ffe0242;
  if (iVar2 != 0) {
    DAT_1fffab74 = (&DAT_1fffa0f8)[iVar3 * 2];
    DAT_1fffab76 = (&DAT_1fffa0fa)[iVar3 * 2];
    set_voltage_raw();
    set_current_raw(DAT_1fffab76);
    uVar1 = FUN_0004037c(0xffffff);
    uVar4 = FUN_0004b9de(DAT_1ffe0458,(int)DAT_1ffe0242);
    FUN_0004e8b2(uVar4,uVar1,0);
    uVar1 = FUN_0004037c(0xffffff);
    uVar4 = FUN_00046756(param_1);
    FUN_0004e8b2(uVar4,uVar1,0);
    FUN_00058268(DAT_1fffab74);
    FUN_000569b8(DAT_1fffab76);
    goto LAB_0005cf64;
  }
  if ((&DAT_1fffa0f8)[iVar3 * 2] == DAT_1fffab74) {
    if ((&DAT_1fffa0fa)[iVar3 * 2] != DAT_1fffab76) goto LAB_0005cf94;
  }
  else {
LAB_0005cf94:
    (&DAT_1fffa0f8)[iVar3 * 2] = DAT_1fffab74;
    (&DAT_1fffa0fa)[iVar3 * 2] = DAT_1fffab76;
  }
  uVar1 = FUN_0004037c(0xffffff);
  uVar4 = FUN_0004b9de(DAT_1ffe0458,(int)DAT_1ffe0242);
  FUN_0004e8b2(uVar4,uVar1,0);
  uVar1 = FUN_0004037c(0xffffff);
  uVar4 = FUN_00046756(param_1);
  FUN_0004e8b2(uVar4,uVar1,0);
  uVar5 = (uint)DAT_1fffab74;
  uVar1 = FUN_0004b9de(DAT_1ffe0458,(int)DAT_1ffe0242);
  uVar1 = FUN_0004b9de(uVar1,1);
  FUN_000499de(uVar1,"%02d.%02d",uVar5 / 100,uVar5 % 100);
  uVar5 = (uint)DAT_1fffab76;
  uVar1 = FUN_0004b9de(DAT_1ffe0458,(int)DAT_1ffe0242);
  uVar1 = FUN_0004b9de(uVar1,3);
  FUN_000499de(uVar1,"%01d.%03d",uVar5 / 1000,uVar5 % 1000);
LAB_0005cf64:
  DAT_1ffe0242 = 0xff;
  FUN_0004e5a6(DAT_1ffe0330,7,0);
  return;
}

