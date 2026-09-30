/* Address: 00067090; name: FUN_00067090; body bytes: 44 */

undefined4 FUN_00067090(void)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  FUN_000599ac();
  if (DAT_1ffe0040 != 0) {
    uVar1 = FUN_00066ba4(0x59ead,"Tmr Svc",0x104,0,2,&DAT_1ffe0044);
  }
  return uVar1;
}

