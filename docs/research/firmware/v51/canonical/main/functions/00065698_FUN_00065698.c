/* Address: 00065698; name: FUN_00065698; body bytes: 20 */

undefined4 FUN_00065698(void)

{
  undefined4 uVar1;
  
  uVar1 = *(undefined4 *)(DAT_1ffe0000 + 0x18);
  *(int *)(DAT_1ffe0000 + 0x18) = 5 - *(int *)(DAT_1ffe0000 + 0x2c);
  return uVar1;
}

