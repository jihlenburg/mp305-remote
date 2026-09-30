/* Address: ram:0006b7b6; name: GAPRole_TerminateSync; body bytes: 4 */

undefined4 GAPRole_TerminateSync(uint param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar2 = DAT_ram_20001dd8;
  gp = 0x20004000;
  uVar3 = 0xc;
  if (DAT_ram_20001dd8 != 0) {
    uVar3 = 0xc;
    if (-1 < (int)(*(uint *)(DAT_ram_20001dd8 + 0x1c) << 0x11)) {
      uVar3 = 0x42;
      if (*(ushort *)(DAT_ram_20001dd8 + 0xb2) == param_1) {
        cVar1 = *(char *)(DAT_ram_20001dd8 + 0x7d);
        *(uint *)(DAT_ram_20001dd8 + 0x1c) = *(uint *)(DAT_ram_20001dd8 + 0x1c) & 0xfffffff1;
        *(undefined1 *)(iVar2 + 0x7c) = 0;
        if (cVar1 != -1) {
          FUN_ram_00042494();
          *(undefined1 *)(iVar2 + 0x7d) = 0xff;
        }
        if (*(char *)(iVar2 + 0x81) != -1) {
          FUN_ram_00042494();
          *(undefined1 *)(iVar2 + 0x7d) = 0xff;
        }
        iVar4 = 60000;
        do {
          iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
        uVar3 = 0;
        if (*(char *)(iVar2 + 0xb) != '\0') {
          (**(code **)(iVar2 + 0x68))();
        }
      }
    }
  }
  return uVar3;
}

