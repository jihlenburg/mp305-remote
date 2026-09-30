/* Address: 00015a5c; name: FUN_00015a5c; body bytes: 54 */

undefined * FUN_00015a5c(uint param_1)

{
  undefined *puVar1;
  
  puVar1 = &DAT_00015a94;
  if (DAT_1ffe0b34 < 2) {
    if (1 < DAT_1fffa0ce) {
      return &DAT_00015a94;
    }
  }
  else {
    DAT_1fffa0ce = 0;
  }
  if ((DAT_1ffe0b3c != 0) && (param_1 < 0x59)) {
    puVar1 = *(undefined **)((&DAT_1ffe0b38)[DAT_1fffa0ce] + param_1 * 4);
  }
  return puVar1;
}

