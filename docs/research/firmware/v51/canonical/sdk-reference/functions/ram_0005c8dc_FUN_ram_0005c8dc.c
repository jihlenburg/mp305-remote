/* Address: ram:0005c8dc; name: FUN_ram_0005c8dc; body bytes: 144 */

undefined4 FUN_ram_0005c8dc(int param_1)

{
  undefined4 uVar1;
  
  gp = 0x20004000;
  uVar1 = 1;
  if (*(char *)(param_1 + 0x16) == '\t') {
    uVar1 = 1;
    if (*(char *)(param_1 + 0x10) == '0') {
      tmos_memcpy(param_1 + 0x100,*(int *)(param_1 + 0x114) + 3,8);
      *(undefined1 *)(param_1 + 0x10) = 1;
      *(undefined1 *)(param_1 + 0x2a) = 0;
      uVar1 = 0;
      *(uint *)(param_1 + 0x108) =
           *(uint *)(param_1 + 0xf8) & (*(uint *)(param_1 + 0x100) | 0x87830d0);
      *(uint *)(param_1 + 0x10c) = *(uint *)(param_1 + 0xfc) & (*(uint *)(param_1 + 0x104) | 0x10);
      *(uint *)(param_1 + 0xa0) = *(uint *)(param_1 + 0xa0) | 0x20;
      *(byte *)(param_1 + 0x11) = *(byte *)(param_1 + 0x11) | 0x80;
    }
  }
  return uVar1;
}

