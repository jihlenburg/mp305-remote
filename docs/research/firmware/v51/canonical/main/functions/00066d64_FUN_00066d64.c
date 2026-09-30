/* Address: 00066d64; name: FUN_00066d64; body bytes: 134 */

undefined4 FUN_00066d64(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  if (param_1 != 0) {
    iVar1 = *(int *)(param_1 + 0x44) + -1;
    *(int *)(param_1 + 0x44) = iVar1;
    if ((*(int *)(param_1 + 0x2c) != *(int *)(param_1 + 0x40)) && (iVar1 == 0)) {
      iVar1 = FUN_00065666(param_1 + 4);
      if (iVar1 == 0) {
        DAT_1ffe0010 = DAT_1ffe0010 & ~(1 << *(sbyte *)(param_1 + 0x2c));
      }
      *(int *)(param_1 + 0x2c) = *(int *)(param_1 + 0x40);
      *(int *)(param_1 + 0x18) = 5 - *(int *)(param_1 + 0x40);
      DAT_1ffe0010 = 1 << (*(uint *)(param_1 + 0x2c) & 0xff) | DAT_1ffe0010;
      iVar1 = *(int *)(&DAT_1ffe0da0 + *(uint *)(param_1 + 0x2c) * 0x14);
      *(int *)(param_1 + 8) = iVar1;
      *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(iVar1 + 8);
      *(int *)(*(int *)(iVar1 + 8) + 4) = param_1 + 4;
      *(int *)(iVar1 + 8) = param_1 + 4;
      *(undefined4 **)(param_1 + 0x14) = &DAT_1ffe0d9c + *(int *)(param_1 + 0x2c) * 5;
      (&DAT_1ffe0d9c)[*(int *)(param_1 + 0x2c) * 5] =
           (&DAT_1ffe0d9c)[*(int *)(param_1 + 0x2c) * 5] + 1;
      uVar2 = 1;
    }
  }
  return uVar2;
}

