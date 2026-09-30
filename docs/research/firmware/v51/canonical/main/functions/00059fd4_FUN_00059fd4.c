/* Address: 00059fd4; name: FUN_00059fd4; body bytes: 18 */

int FUN_00059fd4(void)

{
  if (DAT_1ffe0000 != 0) {
    *(int *)(DAT_1ffe0000 + 0x44) = *(int *)(DAT_1ffe0000 + 0x44) + 1;
  }
  return DAT_1ffe0000;
}

