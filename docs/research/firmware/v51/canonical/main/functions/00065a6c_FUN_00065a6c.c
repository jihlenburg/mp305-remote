/* Address: 00065a6c; name: FUN_00065a6c; body bytes: 148 */

void FUN_00065a6c(int param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  
  if (param_1 != 0) {
    if (param_2 <= *(uint *)(param_1 + 0x40)) {
      param_2 = *(uint *)(param_1 + 0x40);
    }
    uVar1 = *(uint *)(param_1 + 0x2c);
    if ((uVar1 != param_2) && (*(int *)(param_1 + 0x44) == 1)) {
      *(uint *)(param_1 + 0x2c) = param_2;
      if (-1 < *(int *)(param_1 + 0x18)) {
        *(uint *)(param_1 + 0x18) = 5 - param_2;
      }
      if (*(undefined4 **)(param_1 + 0x14) == &DAT_1ffe0d9c + uVar1 * 5) {
        iVar2 = FUN_00065666(param_1 + 4);
        if (iVar2 == 0) {
          DAT_1ffe0010 = DAT_1ffe0010 & ~(1 << *(sbyte *)(param_1 + 0x2c));
        }
        DAT_1ffe0010 = 1 << (*(uint *)(param_1 + 0x2c) & 0xff) | DAT_1ffe0010;
        iVar2 = *(int *)(&DAT_1ffe0da0 + *(uint *)(param_1 + 0x2c) * 0x14);
        *(int *)(param_1 + 8) = iVar2;
        *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(iVar2 + 8);
        *(int *)(*(int *)(iVar2 + 8) + 4) = param_1 + 4;
        *(int *)(iVar2 + 8) = param_1 + 4;
        *(undefined4 **)(param_1 + 0x14) = &DAT_1ffe0d9c + *(int *)(param_1 + 0x2c) * 5;
        (&DAT_1ffe0d9c)[*(int *)(param_1 + 0x2c) * 5] =
             (&DAT_1ffe0d9c)[*(int *)(param_1 + 0x2c) * 5] + 1;
      }
    }
  }
  return;
}

