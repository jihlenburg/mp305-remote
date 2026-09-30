/* Address: ram:00007106; name: FUN_ram_00007106; body bytes: 416 */

/* WARNING: Removing unreachable block (ram,0x00007208) */
/* WARNING: Removing unreachable block (ram,0x000071ee) */
/* WARNING: Removing unreachable block (ram,0x000071de) */
/* WARNING: Removing unreachable block (ram,0x000071f2) */
/* WARNING: Removing unreachable block (ram,0x00007214) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_00007106(uint param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  
  gp = &DAT_ram_20002000;
  uVar1 = param_1 & 0xf;
  if (uVar1 == 2) {
    if (*(char *)(param_2 + 2) == '\x06') {
      FUN_ram_00007080(param_2);
      DAT_ram_20002fb0 = *(undefined1 *)(param_2 + 6);
    }
    DAT_ram_20002ff4 = 0;
  }
  else if (uVar1 < 3) {
    if (uVar1 == 1) {
      (*_DAT_ram_00040178)(0x304,&DAT_ram_20002fe8);
      uVar1 = (uint)(DAT_ram_20002feb ^ DAT_ram_20002fea) << 0x10 |
              (uint)(DAT_ram_20002fe9 ^ DAT_ram_20002fe8) << 0x18 |
              (DAT_ram_20002fec & 0xff) << 8 | (uint)(DAT_ram_20002fec >> 8);
      DAT_ram_20002eb4 = (char)(uVar1 % 0x5e) + '!';
      DAT_ram_20002eb5 = (char)((uVar1 / 0x5e) % 0x5e) + '!';
      DAT_ram_20002eb6 = (char)((uVar1 / 0x2284) % 0x5e) + '!';
      (*_DAT_ram_00040174)(0x307,0x1f,&DAT_ram_20002e98,0x5e,&DAT_ram_2000321c,_DAT_ram_00040174);
    }
  }
  else {
    if (uVar1 == 3) {
      if (*(char *)(param_2 + 2) != '\x06') {
        gp = &DAT_ram_20002000;
        DAT_ram_20002ff8 = param_1;
        return;
      }
      FUN_ram_00007080(param_2);
    }
    else {
      if (uVar1 != 4) {
        gp = &DAT_ram_20002000;
        DAT_ram_20002ff8 = param_1;
        return;
      }
      if (*(char *)(param_2 + 2) == '\x05') {
        DAT_ram_20002ff0 = 0;
        if (DAT_ram_20002ffc == -2) {
          DAT_ram_20002ffe = *(undefined2 *)(param_2 + 0xe);
          DAT_ram_20003000 = *(undefined2 *)(param_2 + 0x10);
          DAT_ram_20003002 = *(undefined2 *)(param_2 + 0x12);
          DAT_ram_20002ffc = *(short *)(param_2 + 10);
          (*_DAT_ram_00040058)
                    (DAT_ram_20002f44,8,0x1900,param_4,&DAT_ram_20003284,_DAT_ram_00040058);
        }
        else {
          (*_DAT_ram_0004017c)();
        }
      }
      if (*(char *)(param_2 + 2) != '\x06') {
        gp = &DAT_ram_20002000;
        DAT_ram_20002ff8 = param_1;
        return;
      }
    }
    DAT_ram_20002fb0 = *(undefined1 *)(param_2 + 6);
  }
  DAT_ram_20002ff8 = param_1;
  return;
}

