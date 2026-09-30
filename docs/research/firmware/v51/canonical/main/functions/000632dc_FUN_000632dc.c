/* Address: 000632dc; name: FUN_000632dc; body bytes: 76 */

/* Recovered from stored Thumb pointer at 0004f35c; callback identification is inferred until
   reviewed. */

void FUN_000632dc(undefined4 param_1,uint *param_2)

{
  if ((DAT_1ffe0154 == '\b') && (DAT_1ffe0129 == '\0')) {
    if (DAT_1fffab1b == '\0') {
      DAT_1ffe012c = (uint)DAT_1ffe0156;
      DAT_1ffe0130 = (uint)DAT_1ffe0158;
      *(undefined1 *)((int)param_2 + 0x12) = 1;
      DAT_1ffe0128 = 1;
      DAT_1fffab88 = 0;
      DAT_1fffab8c = 0;
      goto LAB_00063302;
    }
    DAT_1fffab88 = 0;
    DAT_1fffab8c = 0;
    DAT_1fffab90 = 0;
  }
  *(undefined1 *)((int)param_2 + 0x12) = 0;
  DAT_1ffe0128 = 0;
LAB_00063302:
  *param_2 = DAT_1ffe012c;
  param_2[1] = DAT_1ffe0130;
  return;
}

