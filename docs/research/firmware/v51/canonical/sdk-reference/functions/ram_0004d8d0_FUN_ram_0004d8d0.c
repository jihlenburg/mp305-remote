/* Address: ram:0004d8d0; name: FUN_ram_0004d8d0; body bytes: 204 */

undefined1 FUN_ram_0004d8d0(void)

{
  uint uVar1;
  char *pcVar2;
  int iVar3;
  short *psVar4;
  uint uVar5;
  
  gp = 0x20004000;
  uVar5 = (uint)DAT_ram_20001a65;
  uVar1 = uVar5;
  do {
    pcVar2 = (char *)(uVar1 * 0x10 + DAT_ram_20001a58);
    if (((*pcVar2 == '\x01') && (psVar4 = *(short **)(pcVar2 + 0xc), psVar4 != (short *)0x0)) &&
       (*(int *)(psVar4 + 6) != 0)) {
      if (*psVar4 != 0) {
        if (DAT_ram_20001a62 == '\0') {
          gp = 0x20004000;
          return 1;
        }
        iVar3 = FUN_ram_0004d7c8(pcVar2);
        if (iVar3 != 0) {
          FUN_ram_0004d444(pcVar2,iVar3);
          gp = 0x20004000;
          return 0;
        }
        if ((uint)DAT_ram_20001a61 <= uVar1 + 1) {
          gp = 0x20004000;
          DAT_ram_20001a65 = 0;
          return 1;
        }
        gp = 0x20004000;
        DAT_ram_20001a65 = (char)(uVar1 + 1);
        return 1;
      }
      if (*(char *)((int)psVar4 + 0x1d) == -1) {
        FUN_ram_0004d270(pcVar2,0x62);
        *(undefined1 *)(*(int *)(pcVar2 + 0xc) + 0x1d) = 0;
      }
    }
    uVar1 = uVar1 + 1 & 0xff;
    if (DAT_ram_20001a61 <= uVar1) {
      uVar1 = 0;
    }
    if (uVar1 == uVar5) {
      return 0;
    }
  } while( true );
}

