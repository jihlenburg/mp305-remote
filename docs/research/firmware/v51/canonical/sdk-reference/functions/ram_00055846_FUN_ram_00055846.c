/* Address: ram:00055846; name: FUN_ram_00055846; body bytes: 148 */

void FUN_ram_00055846(int param_1)

{
  gp = 0x20004000;
  *(undefined1 *)(param_1 + 0x16) = 0xff;
  if (*(short *)(param_1 + 0x6c) == 0) {
    if (((*(byte *)(param_1 + 0xe) & 0xf) == 1) || ((*(byte *)(param_1 + 0x60) & 4) != 0)) {
      if ((DAT_ram_20001e30 & 0x200) == 0) {
        FUN_ram_00068284(0x3c,0,1,0,0,0,0,0,0);
      }
      else {
        FUN_ram_000682aa(0x3c,0,1,0,0,0,0,0,0,0,0);
      }
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x17) = 0x3c;
    thunk_FUN_ram_00051fa2(0x3c,*(undefined1 *)(param_1 + 8),0,*(undefined1 *)(param_1 + 0x6e));
  }
  FUN_ram_0005501c(param_1);
  return;
}

