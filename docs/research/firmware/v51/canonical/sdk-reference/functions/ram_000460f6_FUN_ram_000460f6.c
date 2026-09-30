/* Address: ram:000460f6; name: FUN_ram_000460f6; body bytes: 172 */

void FUN_ram_000460f6(uint param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  
  gp = 0x20004000;
  if (DAT_ram_20001a08 != 0) {
    for (uVar1 = 0; uVar1 != param_1; uVar1 = uVar1 + 1) {
      iVar2 = uVar1 * 0x10;
      if (*(int *)(DAT_ram_20001a08 + iVar2 + 8) != 0) {
        FUN_ram_20000104();
        *(undefined4 *)(DAT_ram_20001a08 + iVar2 + 8) = 0;
      }
      if (*(int *)(DAT_ram_20001a08 + iVar2 + 0xc) != 0) {
        FUN_ram_20000104();
        *(undefined4 *)(iVar2 + DAT_ram_20001a08 + 0xc) = 0;
      }
    }
    if (param_2 == 0) {
      if (DAT_ram_20001a08 != 0) {
        tmos_memset(DAT_ram_20001a08,0,param_1 << 4);
        iVar2 = DAT_ram_20001a08;
        for (uVar1 = 0; (uVar1 & 0xff) < param_1; uVar1 = uVar1 + 1) {
          *(undefined1 *)(uVar1 * 0x10 + iVar2) = 0xff;
        }
      }
    }
    else {
      FUN_ram_20000104();
      DAT_ram_20001a08 = 0;
    }
  }
  return;
}

