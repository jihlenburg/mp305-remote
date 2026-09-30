/* Address: ram:00049e22; name: FUN_ram_00049e22; body bytes: 32 */

void FUN_ram_00049e22(undefined2 *param_1)

{
  uint uVar1;
  uint uVar2;
  
  gp = 0x20004000;
  uVar1 = (uint)DAT_ram_20001d55;
  for (uVar2 = 0; uVar2 < uVar1; uVar2 = uVar2 + 1) {
    *param_1 = 0xffff;
    *(undefined1 *)(param_1 + 1) = 0;
    param_1 = param_1 + 2;
  }
  return;
}

