/* Address: 00066df4; name: FUN_00066df4; body bytes: 168 */

undefined4 FUN_00066df4(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  
  uVar1 = 0;
  if (param_1 != 0) {
    if (*(uint *)(param_1 + 0x2c) < *(uint *)(DAT_1ffe0000 + 0x2c)) {
      if (-1 < *(int *)(param_1 + 0x18)) {
        *(int *)(param_1 + 0x18) = 5 - *(int *)(DAT_1ffe0000 + 0x2c);
      }
      if (*(undefined4 **)(param_1 + 0x14) == &DAT_1ffe0d9c + *(uint *)(param_1 + 0x2c) * 5) {
        iVar2 = FUN_00065666(param_1 + 4);
        if (iVar2 == 0) {
          DAT_1ffe0010 = DAT_1ffe0010 & ~(1 << *(sbyte *)(param_1 + 0x2c));
        }
        uVar3 = *(uint *)(DAT_1ffe0000 + 0x2c);
        *(uint *)(param_1 + 0x2c) = uVar3;
        DAT_1ffe0010 = 1 << (uVar3 & 0xff) | DAT_1ffe0010;
        iVar2 = *(int *)(&DAT_1ffe0da0 + uVar3 * 0x14);
        *(int *)(param_1 + 8) = iVar2;
        *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(iVar2 + 8);
        *(int *)(*(int *)(iVar2 + 8) + 4) = param_1 + 4;
        *(int *)(iVar2 + 8) = param_1 + 4;
        *(undefined4 **)(param_1 + 0x14) = &DAT_1ffe0d9c + *(int *)(param_1 + 0x2c) * 5;
        (&DAT_1ffe0d9c)[*(int *)(param_1 + 0x2c) * 5] =
             (&DAT_1ffe0d9c)[*(int *)(param_1 + 0x2c) * 5] + 1;
      }
      else {
        *(undefined4 *)(param_1 + 0x2c) = *(undefined4 *)(DAT_1ffe0000 + 0x2c);
      }
    }
    else if (*(uint *)(DAT_1ffe0000 + 0x2c) <= *(uint *)(param_1 + 0x40)) {
      return 0;
    }
    uVar1 = 1;
  }
  return uVar1;
}

