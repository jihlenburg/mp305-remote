/* Address: 00059e24; name: FUN_00059e24; body bytes: 24 */

void FUN_00059e24(void)

{
  if (*DAT_1ffe0038 == 0) {
    DAT_1ffe0028 = 0xffffffff;
  }
  else {
    DAT_1ffe0028 = *(undefined4 *)DAT_1ffe0038[3];
  }
  return;
}

