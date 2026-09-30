/* Address: 00015ca0; name: FUN_00015ca0; body bytes: 412 */

uint FUN_00015ca0(char *param_1,int param_2,char *param_3,int param_4)

{
  byte bVar1;
  uint uVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  
  *param_3 = *param_1 + '\x01';
  bVar1 = param_1[1];
  param_3[1] = (&DAT_1fffa3fe)[bVar1];
  uVar2 = 2;
  if (DAT_1ffe0187 < (byte)(&DAT_1fffa3f4)[bVar1]) {
    bVar3 = 0;
    do {
      param_3[uVar2] = (&DAT_1fff8f7c)[(uint)DAT_1ffe0187 * 0xc];
      uVar2 = uVar2 + 1 & 0xff;
      param_3[uVar2] =
           (char)((ushort)*(undefined2 *)(&DAT_1fff8f7c + (uint)DAT_1ffe0187 * 0xc) >> 8);
      uVar2 = uVar2 + 1 & 0xff;
      param_3[uVar2] =
           (char)((uint)*(undefined4 *)(&DAT_1fff8f7c + (uint)DAT_1ffe0187 * 0xc) >> 0x10);
      uVar2 = uVar2 + 1 & 0xff;
      param_3[uVar2] =
           (char)((uint)*(undefined4 *)(&DAT_1fff8f7c + (uint)DAT_1ffe0187 * 0xc) >> 0x18);
      uVar2 = uVar2 + 1 & 0xff;
      param_3[uVar2] = (&DAT_1fff8f80)[(uint)DAT_1ffe0187 * 0xc];
      uVar2 = uVar2 + 1 & 0xff;
      param_3[uVar2] =
           (char)((ushort)*(undefined2 *)(&DAT_1fff8f80 + (uint)DAT_1ffe0187 * 0xc) >> 8);
      uVar2 = uVar2 + 1 & 0xff;
      param_3[uVar2] =
           (char)((uint)*(undefined4 *)(&DAT_1fff8f80 + (uint)DAT_1ffe0187 * 0xc) >> 0x10);
      uVar2 = uVar2 + 1 & 0xff;
      param_3[uVar2] =
           (char)((uint)*(undefined4 *)(&DAT_1fff8f80 + (uint)DAT_1ffe0187 * 0xc) >> 0x18);
      uVar2 = uVar2 + 1 & 0xff;
      param_3[uVar2] = (&DAT_1fff8f84)[(uint)DAT_1ffe0187 * 0xc];
      uVar2 = uVar2 + 1 & 0xff;
      param_3[uVar2] =
           (char)((ushort)*(undefined2 *)(&DAT_1fff8f84 + (uint)DAT_1ffe0187 * 0xc) >> 8);
      uVar2 = uVar2 + 1 & 0xff;
      param_3[uVar2] =
           (char)((uint)*(undefined4 *)(&DAT_1fff8f84 + (uint)DAT_1ffe0187 * 0xc) >> 0x10);
      uVar2 = uVar2 + 1 & 0xff;
      param_3[uVar2] =
           (char)((uint)*(undefined4 *)(&DAT_1fff8f84 + (uint)DAT_1ffe0187 * 0xc) >> 0x18);
      bVar4 = DAT_1ffe0187 + 1;
      bVar5 = DAT_1ffe0187 + 1;
      uVar2 = uVar2 + 1 & 0xff;
      DAT_1ffe0187 = bVar4;
      if ((byte)(&DAT_1fffa3f4)[bVar1] <= bVar5) break;
      bVar3 = bVar3 + 1;
    } while (bVar3 < 10);
  }
  if (param_4 == 6) {
    param_3[uVar2] = param_1[param_2 + -1];
    uVar2 = uVar2 + 1 & 0xff;
  }
  return uVar2;
}

