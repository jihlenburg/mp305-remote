/* Address: ram:00055ca8; name: FUN_ram_00055ca8; body bytes: 200 */

undefined4 FUN_ram_00055ca8(int param_1)

{
  ushort uVar1;
  
  gp = 0x20004000;
  uVar1 = *(ushort *)(param_1 + 0x1be);
  if (*(ushort *)(param_1 + 0x1ba) < *(ushort *)(param_1 + 0x1be)) {
    uVar1 = *(ushort *)(param_1 + 0x1ba);
  }
  if (*(char *)(param_1 + 0x146) == '\x02') {
    if (uVar1 < 0xa90) {
      uVar1 = 0xa90;
    }
  }
  else if ((0x848 < uVar1) && ((*(uint *)(param_1 + 0x100) & 0x800) == 0)) {
    uVar1 = 0x848;
  }
  if (*(ushort *)(param_1 + 0x1ca) != uVar1) {
    *(ushort *)(param_1 + 0x1ca) = uVar1;
    *(undefined1 *)(param_1 + 0x7a) = 1;
  }
  uVar1 = *(ushort *)(param_1 + 0x1c2);
  if (*(ushort *)(param_1 + 0x1b6) < *(ushort *)(param_1 + 0x1c2)) {
    uVar1 = *(ushort *)(param_1 + 0x1b6);
  }
  if (*(char *)(param_1 + 0x147) == '\x02') {
    if (uVar1 < 0xa90) {
      uVar1 = 0xa90;
    }
  }
  else if ((0x848 < uVar1) && ((*(uint *)(param_1 + 0x100) & 0x800) == 0)) {
    uVar1 = 0x848;
  }
  if (*(ushort *)(param_1 + 0x1c6) != uVar1) {
    *(ushort *)(param_1 + 0x1c6) = uVar1;
    *(undefined1 *)(param_1 + 0x7a) = 1;
  }
  FUN_ram_00055afc();
  return 0;
}

