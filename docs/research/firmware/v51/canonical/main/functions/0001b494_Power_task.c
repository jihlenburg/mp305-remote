/* Address: 0001b494; name: Power_task; body bytes: 56 */

/* Confirmed by task-create function pointer and literal name Power_task. */

void Power_task(void)

{
  uint uVar1;
  
  DAT_1ffe0224 = FUN_000664d6();
  do {
    while( true ) {
      uVar1 = FUN_00066554(DAT_1ffe0224,3,1,0,10);
      if ((uVar1 & 3) != 0) break;
      FUN_000657dc();
    }
    if ((uVar1 & 1) != 0) {
      FUN_00019f18();
    }
    if ((int)(uVar1 << 0x1e) < 0) {
      FUN_0001a620();
    }
  } while( true );
}

