/* Address: 00017be4; name: FUN_00017be4; body bytes: 94 */

void FUN_00017be4(void)

{
  undefined4 uVar1;
  
  FUN_0001814c();
  DAT_1ffe0246 = 1;
  FUN_00018114(DAT_1ffe048c);
  FUN_00018114(DAT_1ffe0498);
  FUN_00018114(DAT_1ffe04a4);
  FUN_00018114(DAT_1ffe04b0);
  DAT_1ffe0246 = 0;
  uVar1 = DAT_1ffe048c;
  if (((current_mode != '\0') && (uVar1 = DAT_1ffe0498, current_mode != '\x01')) &&
     (uVar1 = DAT_1ffe04a4, current_mode != '\x02')) {
    uVar1 = DAT_1ffe04b0;
  }
  FUN_00047208(uVar1);
  return;
}

