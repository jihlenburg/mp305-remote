/* Address: ram:0004dfa2; name: FUN_ram_0004dfa2; body bytes: 134 */

undefined4 FUN_ram_0004dfa2(undefined4 param_1)

{
  uint uVar1;
  int iVar2;
  undefined1 auStack_28 [8];
  
  gp = 0x20004000;
  uVar1 = 0;
  do {
    if (DAT_ram_20001d54 <= uVar1) {
      return 0;
    }
    iVar2 = uVar1 * 0x3c + DAT_ram_20001d00;
    if (*(short *)(iVar2 + 2) != -1) {
      FUN_ram_00069942(*(undefined1 *)(iVar2 + 5),iVar2 + 6,auStack_28);
      iVar2 = tmos_memcmp(auStack_28,param_1,6);
      if (iVar2 == 1) {
        gp = 0x20004000;
        return 1;
      }
    }
    uVar1 = uVar1 + 1 & 0xff;
  } while( true );
}

