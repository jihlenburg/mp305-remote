/* Address: ram:0005c84c; name: FUN_ram_0005c84c; body bytes: 144 */

undefined4 FUN_ram_0005c84c(int param_1)

{
  undefined4 uVar1;
  
  gp = 0x20004000;
  uVar1 = 1;
  if (*(char *)(param_1 + 0xb) == '\0') {
    uVar1 = 1;
    if ((*(char *)(param_1 + 0x16) == '\t') && ((*(uint *)(param_1 + 0xf8) & 8) != 0)) {
      tmos_memcpy(param_1 + 0x100,*(int *)(param_1 + 0x114) + 3,8);
      *(uint *)(param_1 + 0x108) =
           *(uint *)(param_1 + 0xf8) & (*(uint *)(param_1 + 0x100) | 0x87830d0);
      *(uint *)(param_1 + 0x10c) = *(uint *)(param_1 + 0xfc) & (*(uint *)(param_1 + 0x104) | 0x10);
      if (*(char *)(param_1 + 0x10) == '\x01') {
        *(undefined1 *)(param_1 + 0x10) = 0x31;
      }
      else {
        *(uint *)(param_1 + 0xa8) = *(uint *)(param_1 + 0xa8) | 0x10;
      }
      uVar1 = 0;
    }
  }
  return uVar1;
}

