/* Address: ram:0004de30; name: FUN_ram_0004de30; body bytes: 58 */

void FUN_ram_0004de30(undefined4 param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  
  gp = 0x20004000;
  puVar1 = &DAT_ram_20001d04;
  do {
    if ((code *)*puVar1 != (code *)0x0) {
      (*(code *)*puVar1)(param_1,param_2);
    }
    puVar1 = puVar1 + 1;
  } while (puVar1 != &DAT_ram_20001d34);
  return;
}

