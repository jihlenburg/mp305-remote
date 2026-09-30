/* Address: ram:0005c572; name: FUN_ram_0005c572; body bytes: 194 */

undefined4 FUN_ram_0005c572(int param_1)

{
  undefined1 uVar1;
  ushort uVar2;
  ushort uVar3;
  int iVar4;
  
  gp = 0x20004000;
  iVar4 = *(int *)(param_1 + 0x110);
  if (iVar4 != 0) {
    *(undefined1 *)(param_1 + 0x15) = 9;
    *(undefined1 *)(iVar4 + 2) = 0x15;
    uVar2 = *(ushort *)(param_1 + 0x1b6);
    uVar3 = *(ushort *)(param_1 + 0x1ba);
    *(undefined1 *)(iVar4 + 3) = *(undefined1 *)(param_1 + 0x1b4);
    uVar1 = *(undefined1 *)(param_1 + 0x1b5);
    *(char *)(iVar4 + 5) = (char)uVar2;
    *(undefined1 *)(iVar4 + 4) = uVar1;
    *(char *)(iVar4 + 6) = (char)(uVar2 >> 8);
    *(undefined1 *)(iVar4 + 7) = *(undefined1 *)(param_1 + 0x1b8);
    uVar1 = *(undefined1 *)(param_1 + 0x1b9);
    *(char *)(iVar4 + 9) = (char)uVar3;
    *(undefined1 *)(iVar4 + 8) = uVar1;
    *(char *)(iVar4 + 10) = (char)(uVar3 >> 8);
    if (*(char *)(param_1 + 0x147) != '\x02') {
      if (0x848 < uVar2) {
        uVar2 = 0x848;
      }
      *(char *)(iVar4 + 5) = (char)uVar2;
      *(char *)(iVar4 + 6) = (char)(uVar2 >> 8);
    }
    if (*(char *)(param_1 + 0x146) != '\x02') {
      if (0x848 < uVar3) {
        uVar3 = 0x848;
      }
      *(char *)(iVar4 + 9) = (char)uVar3;
      *(char *)(iVar4 + 10) = (char)(uVar3 >> 8);
    }
    *(undefined1 *)(param_1 + 0x2a) = 0;
    if (*(char *)(param_1 + 0x7a) != '\0') {
      *(uint *)(param_1 + 0xa0) = *(uint *)(param_1 + 0xa0) | 0x100;
    }
    *(undefined1 *)(param_1 + 0x10) = 1;
    return 0;
  }
  return 1;
}

