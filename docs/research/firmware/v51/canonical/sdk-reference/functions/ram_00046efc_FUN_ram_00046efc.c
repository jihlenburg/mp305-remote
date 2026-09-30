/* Address: ram:00046efc; name: FUN_ram_00046efc; body bytes: 208 */

undefined4 FUN_ram_00046efc(int param_1,int param_2)

{
  int iVar1;
  undefined2 auStack_18 [6];
  
  gp = 0x20004000;
  if (param_1 == 3) {
    if ((*(char *)(param_2 + 3) != '\x1a') || (DAT_ram_20001c0a != *(short *)(param_2 + 4))) {
      iVar1 = FUN_ram_0004df14();
      if (iVar1 != 0) {
        *(undefined2 *)(iVar1 + 0xe) = *(undefined2 *)(param_2 + 6);
      }
      FUN_ram_00044812(*(undefined1 *)(param_2 + 3),*(undefined2 *)(param_2 + 4),
                       *(undefined2 *)(param_2 + 6),*(undefined2 *)(param_2 + 8),
                       *(undefined2 *)(param_2 + 10));
      if (*(short *)(param_2 + 4) != DAT_ram_20001c0a) {
        gp = 0x20004000;
        return 1;
      }
      gp = 0x20004000;
      DAT_ram_20001c0a = 0xffff;
      return 1;
    }
  }
  else {
    if (param_1 != 0x2013) {
      if (param_1 == 0xc) {
        FUN_ram_000448c6(DAT_ram_20001d51);
        gp = 0x20004000;
        return 1;
      }
      if (param_1 == 0xffff) {
        if (*(char *)(param_2 + 5) == '\x12') {
          auStack_18[0] = 0;
          FUN_ram_0004ddcc(*(undefined2 *)(param_2 + 2),*(undefined1 *)(param_2 + 4),auStack_18);
          gp = 0x20004000;
          return 1;
        }
        gp = 0x20004000;
        return 0;
      }
      gp = 0x20004000;
      return 0;
    }
    if ((*(char *)(param_2 + 2) != '\f') && (*(char *)(param_2 + 2) != '\x11')) {
      gp = 0x20004000;
      return 1;
    }
  }
  FUN_ram_00044110();
  return 1;
}

