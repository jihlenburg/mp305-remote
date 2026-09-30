/* Address: ram:0004e1a2; name: linkDB_PerformFunc; body bytes: 94 */

void linkDB_PerformFunc(code *param_1)

{
  int iVar1;
  
  gp = 0x20004000;
  if (param_1 != (code *)0x0) {
    for (iVar1 = 0; iVar1 < (int)(uint)DAT_ram_20001d54; iVar1 = iVar1 + 1) {
      if (*(short *)(iVar1 * 0x3c + DAT_ram_20001d00 + 2) != -1) {
        (*param_1)();
      }
    }
    return;
  }
  return;
}

