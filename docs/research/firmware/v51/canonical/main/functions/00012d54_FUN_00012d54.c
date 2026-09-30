/* Address: 00012d54; name: FUN_00012d54; body bytes: 262 */

void FUN_00012d54(void)

{
  ushort uVar1;
  short sVar2;
  uint uVar3;
  uint uVar4;
  int extraout_r2;
  int extraout_r2_00;
  undefined1 extraout_r3;
  bool bVar5;
  
  if (DAT_1fffa0a5 != '\0') {
    if (DAT_1fffa0a5 != '\x01') {
      uVar4 = (uint)DAT_1fffa0b0;
      if (DAT_1fffa0a5 != '\x02') {
        if (DAT_1fffa0a5 == '\x03') {
          if ((DAT_1fffa0b4 != 0) &&
             (sVar2 = DAT_1fffa0b4 + -1, bVar5 = DAT_1fffa0b4 != 1, DAT_1fffa0b4 = sVar2, bVar5)) {
            return;
          }
          DAT_1fffa0b0 = (byte)(uVar4 + 1);
          if ((uVar4 + 1 & 0xff) < (uint)*DAT_1fffa0a8) {
            DAT_1fffa0a5 = 2;
            return;
          }
          if (DAT_1fffa0b2 != 0) {
            sVar2 = DAT_1fffa0b2 + -1;
            bVar5 = DAT_1fffa0b2 != 1;
            DAT_1fffa0b2 = sVar2;
            if (bVar5) {
              DAT_1fffa0a5 = 2;
              DAT_1fffa0b0 = 0;
              return;
            }
          }
        }
        FUN_00012e00();
        *(undefined1 *)(extraout_r2_00 + 1) = 0;
        return;
      }
      uVar3 = (uint)*(ushort *)(DAT_1fffa0ac + uVar4 * 4);
      DAT_1fffa0a5 = 3;
      DAT_1fffa0b4 = *(short *)(DAT_1fffa0ac + uVar4 * 4 + 2) * 10;
      uVar4 = (uint)DAT_1fffa0b1;
      if ((uVar4 == 0) && ((DAT_1fffa0a4 == '\x03' || (DAT_1fffa0a4 == '\x04')))) {
        uVar1 = DAT_1fffa0a8[3];
        uVar4 = 0x32;
      }
      else {
        uVar1 = DAT_1fffa0a8[3];
      }
      if ((uVar3 != 0) && ((uVar1 != 1 || (uVar4 != 0)))) {
        if (uVar3 < 100) {
          uVar3 = 100;
        }
        else if (5000 < uVar3) {
          uVar3 = 5000;
        }
        uVar3 = 0x393870 / uVar3 & 0xffff;
        if (uVar1 == 0) {
          uVar4 = uVar3 >> 1;
        }
        else {
          uVar4 = (uVar3 >> 1) / uVar4;
        }
        FUN_0001df0c(&DAT_4003a400,uVar3);
        FUN_0001df02(&DAT_4003a400,3,uVar4);
        DAT_4003a400 = 0;
        DAT_4003a480 = DAT_4003a480 | 1;
        return;
      }
      FUN_00012e00();
      return;
    }
    FUN_00012e00();
    *(undefined1 *)(extraout_r2 + 1) = extraout_r3;
    *(undefined1 *)(extraout_r2 + 0xc) = 0;
    *(undefined2 *)(extraout_r2 + 0xe) = *(undefined2 *)(*(int *)(extraout_r2 + 4) + 4);
  }
  return;
}

