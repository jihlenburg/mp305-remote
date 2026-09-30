/* Address: 0001a158; name: FUN_0001a158; body bytes: 222 */

ushort FUN_0001a158(int param_1)

{
  int iVar1;
  ushort uVar2;
  uint uVar3;
  uint in_fpscr;
  undefined4 uVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  
  uVar3 = 0;
  if (param_1 == 0) {
    return 0;
  }
  do {
    if (DAT_1fffa9a4 <= (ushort)(&DAT_0007b136)[uVar3 * 2]) break;
    uVar3 = uVar3 + 1 & 0xff;
  } while (uVar3 < 0xb);
  if (uVar3 < 10) {
    if (uVar3 == 0) {
      uVar2 = (ushort)((uint)(param_1 * 0x4af) / 100);
      goto LAB_0001a22a;
    }
    iVar1 = uVar3 * 4;
    fVar6 = (float)VectorUnsignedToFloat
                             ((uint)*(ushort *)(&UNK_0007b138 + iVar1),(byte)(in_fpscr >> 0x16) & 3)
    ;
    fVar7 = (float)VectorUnsignedToFloat
                             ((uint)*(ushort *)(&UNK_0007b134 + iVar1),(byte)(in_fpscr >> 0x16) & 3)
    ;
    fVar8 = (float)VectorUnsignedToFloat
                             ((uint)(ushort)(&DAT_0007b136)[uVar3 * 2],(byte)(in_fpscr >> 0x16) & 3)
    ;
    fVar5 = (float)VectorUnsignedToFloat
                             ((uint)*(ushort *)(&UNK_0007b132 + iVar1),(byte)(in_fpscr >> 0x16) & 3)
    ;
    fVar7 = (fVar6 - fVar7) / (fVar8 - fVar5);
    fVar9 = (float)VectorUnsignedToFloat
                             ((uint)*(ushort *)(&UNK_0007b138 + iVar1),(byte)(in_fpscr >> 0x16) & 3)
    ;
    fVar6 = (float)VectorUnsignedToFloat
                             ((uint)(ushort)(&DAT_0007b136)[uVar3 * 2],(byte)(in_fpscr >> 0x16) & 3)
    ;
    fVar8 = (float)VectorUnsignedToFloat(DAT_1fffa9a4,(byte)(in_fpscr >> 0x16) & 3);
    fVar5 = (float)VectorUnsignedToFloat(param_1,(byte)(in_fpscr >> 0x16) & 3);
    fVar5 = ((fVar9 - fVar7 * fVar6) + fVar7 * fVar8) * fVar5;
  }
  else {
    fVar7 = (float)VectorUnsignedToFloat(DAT_1fffa9a4,(byte)(in_fpscr >> 0x16) & 3);
    fVar5 = (float)VectorUnsignedToFloat(param_1,(byte)(in_fpscr >> 0x16) & 3);
    fVar5 = (fVar7 * -0.03 + 750.0) * fVar5;
  }
  uVar4 = VectorFloatToUnsigned(fVar5 / 100.0,3);
  uVar2 = (ushort)uVar4;
LAB_0001a22a:
  if (uVar2 < 0x1e) {
    uVar2 = 0x1e;
  }
  return uVar2;
}

