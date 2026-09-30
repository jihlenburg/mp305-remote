/* Address: 00012850; name: FUN_00012850; body bytes: 74 */

void FUN_00012850(void)

{
  undefined1 *puVar1;
  int iVar2;
  
  FUN_0001fd50();
  puVar1 = &DAT_1fffa00c;
  if (DAT_1fffa00e == '\x02') goto LAB_0001288e;
  if (DAT_1ffe01c4 == '\x01') {
    while ((iVar2 = FUN_0001a24c(), iVar2 == 0 && (0 < DAT_1ffe01c6))) {
      if (0 < (short)(DAT_1ffe01c6 + -1)) {
        DAT_1ffe01c6 = DAT_1ffe01c6 + -1;
        return;
      }
      DAT_1ffe01c6 = 200;
      DAT_1ffe01c4 = 0;
      puVar1 = (undefined1 *)FUN_0001b71c();
LAB_0001288e:
      puVar1[2] = 0;
      DAT_1ffe01c4 = '\x01';
      DAT_1ffe01c6 = 200;
    }
  }
  return;
}

