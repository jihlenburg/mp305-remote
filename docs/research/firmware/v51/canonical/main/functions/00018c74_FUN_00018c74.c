/* Address: 00018c74; name: FUN_00018c74; body bytes: 48 */

void FUN_00018c74(int param_1)

{
  int iVar1;
  undefined1 *puVar2;
  
  iVar1 = FUN_00015ee8();
  if (*(char *)(iVar1 + 4) == '\0') {
    return;
  }
  puVar2 = (undefined1 *)FUN_00015ee8(param_1);
  *puVar2 = 1;
  if (param_1 != 1) {
    FUN_0001bcd0();
    return;
  }
  FUN_0001bce4(1);
  return;
}

