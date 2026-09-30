/* Address: 00055940; name: FUN_00055940; body bytes: 242 */

void FUN_00055940(uint param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  
  uVar2 = DAT_1ffe02e0;
  uVar4 = (uint)(byte)(DAT_1ffe0267 + 1);
  if (8 < uVar4) {
    uVar4 = 0;
  }
  if (param_1 == 0) {
    DAT_1ffe02e0 = 0;
    DAT_1ffe0267 = 9;
    if (DAT_1ffe034c != 0) {
      uVar3 = 0xffa600;
LAB_00055a20:
      uVar3 = FUN_0004037c(uVar3);
      FUN_0004ea90(DAT_1ffe0374,uVar3,0);
      return;
    }
  }
  else if (((DAT_1ffe0330 != DAT_1ffe0468) && (DAT_1ffe0248 == '\0')) &&
          (iVar1 = FUN_00040928(), iVar1 == DAT_1ffe0344)) {
    uVar2 = uVar2 >> uVar4;
    for (param_1 = param_1 >> uVar4;
        (uVar5 = 9, uVar4 < 9 && (uVar5 = uVar4, (param_1 & ~uVar2 & 1) == 0));
        param_1 = param_1 >> 1) {
      if ((uVar2 & ~param_1 & 1) != 0) {
        DAT_1ffe02e0 = DAT_1ffe02e0 & ~(1 << uVar4);
      }
      uVar2 = uVar2 >> 1;
      uVar4 = uVar4 + 1 & 0xff;
    }
    if (DAT_1ffe0267 == uVar5) {
      if (uVar5 < 9) {
        return;
      }
    }
    else if (uVar5 < 9) {
      if (DAT_1ffe0330 != 0) {
        FUN_0001ba58();
        return;
      }
      DAT_1ffe02e0 = 1 << uVar5 | DAT_1ffe02e0;
      DAT_1ffe0267 = (byte)uVar5;
      uVar3 = FUN_00016060(uVar5);
      FUN_0001d100(1,uVar3);
      if (DAT_1ffe034c == 0) {
        return;
      }
      uVar3 = 0x999999;
      goto LAB_00055a20;
    }
    DAT_1ffe0267 = 9;
  }
  return;
}

