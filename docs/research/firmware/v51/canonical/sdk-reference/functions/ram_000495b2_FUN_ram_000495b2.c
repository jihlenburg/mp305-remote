/* Address: ram:000495b2; name: FUN_ram_000495b2; body bytes: 138 */

void FUN_ram_000495b2(int param_1)

{
  uint uVar1;
  
  gp = 0x20004000;
  FUN_ram_00048886(param_1 + 8);
  if ((*(char *)(param_1 + 2) - 0x17U & 0xfd) == 0) {
    if (*(char *)(param_1 + 0xc) == '\x01') {
      uVar1 = 0;
      if (*(int *)(param_1 + 0x10) == 0) goto LAB_ram_000495e2;
      for (; uVar1 < *(byte *)(param_1 + 0x14); uVar1 = uVar1 + 1 & 0xff) {
        if (*(int *)(*(int *)(param_1 + 0x10) + uVar1 * 0xc + 8) != 0) {
          FUN_ram_20000104();
        }
      }
    }
    else if (*(int *)(param_1 + 0x18) == 0) goto LAB_ram_000495e2;
    FUN_ram_20000104();
  }
LAB_ram_000495e2:
  *(undefined1 *)(param_1 + 2) = 0;
  *(undefined1 *)(param_1 + 9) = 0xff;
  *(undefined1 *)(param_1 + 0x24) = 0;
  tmos_memset(param_1 + 0xc,0,0x18);
  return;
}

