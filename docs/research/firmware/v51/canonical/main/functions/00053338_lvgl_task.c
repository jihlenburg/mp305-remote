/* Address: 00053338; name: lvgl_task; body bytes: 130 */

/* Confirmed by task-create function pointer and literal name lvgl_task. */

void lvgl_task(void)

{
  undefined4 uVar1;
  uint uVar2;
  
  uVar2 = 0;
  FUN_000488b8();
  FUN_0004f2d8();
  FUN_0004f314();
  FUN_0005017c();
  DAT_1fffaad1 = 0;
  DAT_1fffaace = 0;
LAB_00053354:
  while( true ) {
    FUN_00052964();
    FUN_000658d4(1);
    FUN_0001f37c();
    if (DAT_1fffab1f == '\0') {
      FUN_000658d4(1000);
    }
    FUN_0001e284();
    if (DAT_1fffaae5 == '\x01') break;
    if ((DAT_1fffaae5 != '\x02') || (DAT_1fffaacd != '\x01')) goto LAB_0005338e;
    DAT_1fffaacd = '\0';
  }
  DAT_1fffab20 = 0;
  uVar1 = 0;
  goto LAB_000533b0;
LAB_0005338e:
  if ((DAT_1fffaacd == '\0') && (uVar2 = uVar2 + 1, 0x31 < uVar2)) {
    DAT_1fffab88 = 0;
    DAT_1fffab8c = 0;
    DAT_1fffab90 = 0;
    DAT_1fffaacd = '\x01';
    uVar1 = 100;
    DAT_1fffab20 = 100;
LAB_000533b0:
    FUN_0001cd54(uVar1);
  }
  goto LAB_00053354;
}

