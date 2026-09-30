/* Address: 0005b380; name: FUN_0005b380; body bytes: 54 */

void FUN_0005b380(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = FUN_00027780(*(undefined4 *)(param_1 + 0x30),*(undefined4 *)(param_1 + 0x24),
                       *(undefined4 *)(param_1 + 0x2c));
  *(undefined4 *)(param_1 + 0x30) = uVar1;
  uVar1 = FUN_00027780(*(undefined4 *)(param_1 + 0x3c),*(undefined4 *)(param_1 + 0x24),
                       *(undefined4 *)(param_1 + 0x2c));
  *(undefined4 *)(param_1 + 0x3c) = uVar1;
  uVar1 = FUN_00027780(*(undefined4 *)(param_1 + 0x38),*(undefined4 *)(param_1 + 0x24),
                       *(undefined4 *)(param_1 + 0x2c));
  *(undefined4 *)(param_1 + 0x38) = uVar1;
  uVar1 = FUN_00027780(*(undefined4 *)(param_1 + 0x40),*(undefined4 *)(param_1 + 0x24),
                       *(undefined4 *)(param_1 + 0x2c));
  *(undefined4 *)(param_1 + 0x40) = uVar1;
  return;
}

