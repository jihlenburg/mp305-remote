/* Address: ram:000690dc; name: FUN_ram_000690dc; body bytes: 472 */

undefined4 FUN_ram_000690dc(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined1 auStack_38 [24];
  
  gp = 0x20004000;
  if (DAT_ram_20001aa8 == 0) {
    if (param_1 == 0) {
      gp = 0x20004000;
      return 1;
    }
    if (param_2 == 0) {
      gp = 0x20004000;
      return 1;
    }
    uVar1 = FUN_ram_0006908a();
    DAT_ram_20001a86 = (byte)uVar1;
    if (DAT_ram_20001a8d <= uVar1) {
      uVar1 = 0;
      while ((uVar3 = (uint)DAT_ram_20001a8d, uVar1 < uVar3 &&
             (iVar2 = tmos_isbufset(uVar1 * 0x10 + DAT_ram_20001a88,0xff,6), uVar3 = uVar1,
             iVar2 == 0))) {
        uVar1 = uVar1 + 1 & 0xff;
      }
      DAT_ram_20001a86 = (byte)uVar3;
    }
  }
  if (DAT_ram_20001a8d <= DAT_ram_20001a86) {
    return 1;
  }
  if (DAT_ram_20001aa8 == 0) {
    FUN_ram_00042e5e(DAT_ram_20001a86 * '\x06' + ' ',0x10,param_1);
    tmos_memset(auStack_38,0xff,0x18);
    FUN_ram_00042e5e(DAT_ram_20001a86 + 0x70,0x18,auStack_38);
    tmos_memcpy(DAT_ram_20001a88 + (uint)DAT_ram_20001a86 * 0x10,param_1,0x10);
    DAT_ram_20001aa8 = param_2;
  }
  else if (*(int *)(DAT_ram_20001aa8 + 8) == 0) {
    if (*(int *)(DAT_ram_20001aa8 + 0x10) == 0) {
      if (*(int *)(DAT_ram_20001aa8 + 0x14) == 0) {
        if (*(int *)(DAT_ram_20001aa8 + 0xc) == 0) {
          if (DAT_ram_20001a85 != '\0') {
            FUN_ram_00068c88();
          }
          if (DAT_ram_20001a84 != '\0') {
            FUN_ram_00068cec();
          }
          FUN_ram_00068d94();
          gp = 0x20004000;
          return 1;
        }
        FUN_ram_00042e5e(DAT_ram_20001a86 * '\x06' + '$',0x10);
        FUN_ram_00042e5e(DAT_ram_20001a86 * '\x06' + '%',4,*(int *)(DAT_ram_20001aa8 + 0xc) + 0x10);
        *(undefined4 *)(DAT_ram_20001aa8 + 0xc) = 0;
      }
      else {
        FUN_ram_00042e5e(DAT_ram_20001a86 * '\x06' + '#',0x10);
        *(undefined4 *)(DAT_ram_20001aa8 + 0x14) = 0;
      }
    }
    else {
      FUN_ram_00042e5e(DAT_ram_20001a86 * '\x06' + '\"',0x1c);
      *(undefined4 *)(DAT_ram_20001aa8 + 0x10) = 0;
    }
  }
  else {
    FUN_ram_00042e5e(DAT_ram_20001a86 * '\x06' + '!',0x1c);
    *(undefined4 *)(DAT_ram_20001aa8 + 8) = 0;
  }
  FUN_ram_00042e10(DAT_ram_200019c4);
  gp = 0x20004000;
  return 0;
}

