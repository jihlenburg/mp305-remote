/* Address: ram:00056968; name: FUN_ram_00056968; body bytes: 136 */

undefined4 FUN_ram_00056968(int param_1,undefined1 param_2)

{
  gp = 0x20004000;
  if (DAT_ram_20001dfc == param_1) {
    DAT_ram_20001dfc = 0;
  }
  if (*(int *)(param_1 + 0x120) != 0) {
    FUN_ram_0005d5f6(*(undefined2 *)(param_1 + 8),0x80,0);
  }
  if (*(short *)(param_1 + 0x42) != 0) {
    FUN_ram_0005d5f6(*(undefined2 *)(param_1 + 8),0x81,0x13);
  }
  FUN_ram_0005d5f6(*(undefined2 *)(param_1 + 8),0x81,5);
  *(undefined1 *)(param_1 + 10) = 0;
  *(undefined1 *)(param_1 + 0x10) = 0;
  *(undefined1 *)(param_1 + 0x52) = param_2;
  if (DAT_ram_20001e04 < 2) {
    FUN_ram_00042570(0,1);
  }
  return 0;
}

