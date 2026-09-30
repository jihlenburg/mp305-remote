/* Address: 00027388; name: FUN_00027388; body bytes: 92 */

void FUN_00027388(void)

{
  undefined4 uVar1;
  int iVar2;
  
  FUN_0001814c();
  DAT_1fffaad3 = 0;
  uVar1 = FUN_00037604();
  FUN_0004eb0e(DAT_1ffe04c8,uVar1);
  if (current_mode == '\0') {
    FUN_0004aa6e(DAT_1ffe0344,0x10);
  }
  else {
    if (current_mode == '\x01') {
      FUN_00017cf8();
      goto LAB_000273da;
    }
    if ((current_mode != '\x02') &&
       ((current_mode != '\x03' || (iVar2 = FUN_0004cd1e(DAT_1ffe0654), iVar2 == 0))))
    goto LAB_000273da;
  }
  FUN_00018114(DAT_1ffe0348);
LAB_000273da:
  FUN_0001cb8c(0xf);
  return;
}

