/* Address: ram:000534a8; name: FUN_ram_000534a8; body bytes: 124 */

void FUN_ram_000534a8(int param_1)

{
  gp = 0x20004000;
  *(char *)(param_1 + 0x11) = *(char *)(param_1 + 0x1e) + '\x06';
  *(undefined1 *)(param_1 + 0x10) = 4;
  **(undefined1 **)(param_1 + 0x4c) = 4;
  *(undefined1 *)(*(int *)(param_1 + 0x4c) + 1) = *(undefined1 *)(param_1 + 0x11);
  if ((*(byte *)(param_1 + 0x35) & 1) == 0) {
    if (*(char *)(param_1 + 0x34) != '\x02') goto LAB_ram_000534f0;
  }
  **(byte **)(param_1 + 0x4c) = **(byte **)(param_1 + 0x4c) | 0x40;
LAB_ram_000534f0:
  tmos_memcpy(*(int *)(param_1 + 0x4c) + 2,param_1 + 0x36,6);
  tmos_memcpy(*(int *)(param_1 + 0x4c) + 8,*(undefined4 *)(param_1 + 0x2c),
              *(undefined2 *)(param_1 + 0x1e));
  *(undefined1 *)(param_1 + 0xb) = 0x93;
  return;
}

