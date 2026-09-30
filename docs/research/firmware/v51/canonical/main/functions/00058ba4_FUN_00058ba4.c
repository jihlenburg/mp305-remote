/* Address: 00058ba4; name: FUN_00058ba4; body bytes: 376 */

void FUN_00058ba4(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined *puVar3;
  
  do {
    FUN_0001a5fc();
    if (((&DAT_1fffa3f4)[DAT_1fffa408] == '\0') || (iVar1 = get_output_faults(), iVar1 != 0)) {
      DAT_1fffaaec = '\x01';
      uVar2 = FUN_0004b9de(DAT_1ffe0508,8);
      FUN_0004e00e(uVar2,1);
      uVar2 = FUN_0004b9de(DAT_1ffe0508,9);
      FUN_0004aa6e(uVar2,1);
      if (DAT_1ffe02c0 != 0) {
        FUN_000528ac();
        DAT_1ffe02c0 = 0;
        DAT_1fffab48 = 0;
        DAT_1fffab84 = 0;
        DAT_1fffab94 = 0;
        DAT_1fffaaf5 = 1;
        FUN_0001b994();
        FUN_000499de(DAT_1ffe0514,&DAT_00058d30,DAT_1fffab94);
      }
      param_1 = 0;
LAB_00058c1a:
      FUN_0001aebc(param_1);
      return;
    }
    DAT_1fffaaec = param_1 == 0;
    uVar2 = FUN_0004b9de(DAT_1ffe052c,0);
    if (DAT_1fffaaec == '\0') {
      puVar3 = &DAT_0007ce38;
    }
    else {
      puVar3 = &DAT_0007e988;
    }
    FUN_00047d8e(uVar2,puVar3);
    if (param_1 == 0) {
      uVar2 = FUN_0004b9de(DAT_1ffe0508,8);
      FUN_0004e00e(uVar2,1);
      uVar2 = FUN_0004b9de(DAT_1ffe0508,9);
      FUN_0004aa6e(uVar2,1);
      if (DAT_1ffe02c0 != 0) {
        FUN_000528ac();
        DAT_1ffe02c0 = 0;
        DAT_1fffab48 = 0;
        DAT_1fffab94 = 0;
        DAT_1fffaaf5 = 1;
        FUN_0001b994();
        FUN_000499de(DAT_1ffe0514,&DAT_00058d30,DAT_1fffab94);
      }
      goto LAB_00058c1a;
    }
    uVar2 = FUN_0004b9de(DAT_1ffe0508,8);
    FUN_0004aa6e(uVar2,1);
    uVar2 = FUN_0004b9de(DAT_1ffe0508,9);
    FUN_0004e00e(uVar2,1);
    if (DAT_1ffe02c0 != 0) goto LAB_00058c1a;
    DAT_1ffe02c0 = FUN_0005285c(0x58d51,500,DAT_1ffe04fc);
    DAT_1fffab94 = 0;
    DAT_1fffaaf5 = 1;
    FUN_00026470(DAT_1ffe04fc,(undefined1)DAT_1fffab48,1);
    if ((&DAT_1fffa41c)[DAT_1fffab48 * 3] != 0) {
      set_voltage_raw(((uint)*(ushort *)(&DAT_1fffa414 + DAT_1fffab48 * 3) << 0x11) / 0x140000);
      set_current_raw((&DAT_1fffa418)[DAT_1fffab48 * 3]);
      goto LAB_00058c1a;
    }
    param_1 = 0;
  } while( true );
}

