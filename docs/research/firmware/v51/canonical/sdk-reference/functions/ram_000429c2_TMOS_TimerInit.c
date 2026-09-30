/* Address: ram:000429c2; name: TMOS_TimerInit; body bytes: 178 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 TMOS_TimerInit(code *param_1)

{
  undefined *puVar1;
  
  gp = 0x20004000;
  if (DAT_ram_20001be8 != (code *)0x0) {
    (*DAT_ram_20001be8)();
  }
  if (param_1 == (code *)0x0) {
    if ((char)DAT_ram_20001bd2 < '\0') {
      DAT_ram_20001b80 = 0;
      _DAT_ram_20001b8c = 0x327a12;
      DAT_ram_4000c268 = 0xffffffff;
      DAT_ram_20001c00 = (code *)&LAB_ram_200005dc;
    }
    else {
      if ((DAT_ram_20001bd2 & 1) == 0) {
        if (DAT_ram_20001bd2 == 0) {
          puVar1 = (undefined *)0x32;
        }
        else {
          puVar1 = &mcountinhibit;
        }
        _DAT_ram_20001b8c = CONCAT22(puVar1,0x8000);
      }
      else {
        _DAT_ram_20001b8c = 0x3207d00;
      }
      DAT_ram_20001c00 = FUN_ram_2000060e;
    }
  }
  else {
    _DAT_ram_20001b8c = 0x327a12;
    DAT_ram_20001c00 = param_1;
  }
  FUN_ram_00042552(&LAB_ram_000427f4);
  return 0;
}

