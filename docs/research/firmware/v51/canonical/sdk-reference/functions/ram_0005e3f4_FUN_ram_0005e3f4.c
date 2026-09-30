/* Address: ram:0005e3f4; name: FUN_ram_0005e3f4; body bytes: 360 */

void FUN_ram_0005e3f4(void)

{
  int iVar1;
  uint *puVar2;
  undefined4 *puVar3;
  byte bVar4;
  int iVar5;
  
  iVar1 = DAT_ram_20001dd8;
  gp = 0x20004000;
  do {
    do {
    } while (DAT_ram_20001eb0[0x19] != 0);
    DAT_ram_20001eb0[3] = 0xd00f;
    puVar3 = DAT_ram_20001eb0;
    fence.i();
    DAT_ram_20001eb0[2] = 0x2000;
    DAT_ram_20001e98 = 0x80;
    puVar3[0x19] = 0x592;
    puVar3[3] = 0xf00f;
    DAT_ram_20001e94 = 0;
    DAT_ram_20001e99 = 0;
    *(byte *)(iVar1 + 0x28) = *(byte *)(iVar1 + 0x28) & 0x9f;
    DAT_ram_20001e95 = 0;
    *puVar3 = 1;
    puVar2 = DAT_ram_20001e88;
    *DAT_ram_20001e88 = *DAT_ram_20001e88 & 0xfffffe7f;
    *puVar2 = *puVar2 & 0xfffffe7f | 0x100;
    iVar5 = DAT_ram_20001efc;
    *(uint *)(DAT_ram_20001efc + 8) = *(uint *)(DAT_ram_20001efc + 8) | 0x330000;
    puVar3[0x14] = 0xd9;
    *(uint *)(iVar5 + 0x2c) = *(uint *)(iVar5 + 0x2c) & 0xfffffffd;
    *puVar2 = *puVar2 & 0xffffff80 | *(byte *)(iVar1 + 0x24) & 0x7f;
    FUN_ram_200010ec();
    FUN_ram_00062262();
    if ((DAT_ram_20001e94 & 1) == 0) {
LAB_ram_0005e4d8:
      *(undefined1 *)(iVar1 + 10) = 0xa0;
      break;
    }
    DAT_ram_20001e94 = 0;
    iVar5 = FUN_ram_0005e1a6(iVar1);
    if (iVar5 != 0) goto LAB_ram_0005e4d8;
    if ((*(byte *)(iVar1 + 0x28) & 0x60) != 0x20) {
      gp = 0x20004000;
      return;
    }
  } while (*(char *)(iVar1 + 10) == -0x5b);
  bVar4 = *(byte *)(iVar1 + 0x28) & 0x9f | 0x40;
  *(byte *)(iVar1 + 0x28) = bVar4;
  FUN_ram_000682c8(bVar4,*(undefined1 *)(iVar1 + 0x55),iVar1 + 0x56,*(char *)(iVar1 + 0x2c) + '\x01'
                   ,*(undefined1 *)(iVar1 + 0x2d),*(undefined1 *)(iVar1 + 0x29),
                   (int)*(char *)(iVar1 + 0x23),(int)*(char *)(iVar1 + 0x15),
                   *(undefined2 *)(iVar1 + 0x3e),0,0,0,0);
  return;
}

